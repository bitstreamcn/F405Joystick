/*
 * Application.c
 *
 *  Created on: Jun 13, 2025
 *      Author: bitstream
 */
#include "Application.h"
#include "CRSFRadio.h"
//#include "CRSF.h"
#include "crsf2.h"

#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "adc.h"
#include "AdcToChannel.h"
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "../Drivers/Board/Board.h"

void Init();
void Loop();

Application_s Application = {
		Init,
		Loop
};

bool FirstPowerKeyUp = false;
enum eFlightMode run_mode = MODE_CAR;

void Init()
{

    //处理开机
  if (HAL_GPIO_ReadPin(POWER_KEY_GPIO_Port, POWER_KEY_Pin) == GPIO_PIN_RESET)
  {
	  for (int i=0;i<100;i++)
	  {
		  DelayMs(5);
		  if (HAL_GPIO_ReadPin(POWER_KEY_GPIO_Port, POWER_KEY_Pin) == GPIO_PIN_SET)
		  {
			  break;
		  }
	  }
	  if (HAL_GPIO_ReadPin(POWER_KEY_GPIO_Port, POWER_KEY_Pin) == GPIO_PIN_SET)
	  {
		  return;
	  }
  }

    HAL_GPIO_WritePin(TURN_ON_GPIO_Port, TURN_ON_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_SET);

    board_init();

    osDelay(100);

	CRSFRadio.Init();

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_dma_buffer, ADC_CHANNEL_COUNT);

	HAL_GPIO_WritePin(LED_CAR_GPIO_Port, LED_CAR_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_DRONE_GPIO_Port, LED_DRONE_Pin, GPIO_PIN_RESET);
}

void Loop()
{
	  //处理关机
	  if (HAL_GPIO_ReadPin(POWER_KEY_GPIO_Port, POWER_KEY_Pin) == GPIO_PIN_RESET)
	  {
		  //printf("POWER_KEY_Pin down\r\n");
		  if (FirstPowerKeyUp)
		  {
			  for (int i=0;i<100;i++)
			  {
				  DelayMs(10);
				  if (HAL_GPIO_ReadPin(POWER_KEY_GPIO_Port, POWER_KEY_Pin) == GPIO_PIN_SET)
				  {
					  break;
				  }
			  }
			  if (HAL_GPIO_ReadPin(POWER_KEY_GPIO_Port, POWER_KEY_Pin) == GPIO_PIN_RESET)
			  {
				  HAL_GPIO_WritePin(TURN_ON_GPIO_Port, TURN_ON_Pin, GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_RESET);
			  }
		  }
	  }
	  else{
		  FirstPowerKeyUp = true;
	  }

	  static uint16_t adc_values[ADC_CHANNEL_COUNT] = {0, 0, 0, 0, 0, 0};
	  if (adc_value_flag == 1)
	  {
		  memcpy(adc_values, adc_values_new, sizeof(adc_values_new));
		  adc_value_flag = 0;
	  }

		static uint32_t lastSend;
		uint32_t now = TimerGetCurrentTime();
		if (now - lastSend > 1000)
		{
			//输出遥杆数据
			for (int i=1; i<5; i++)
			{
				//uint16_t channel = adc_values[i]; //process_adc_input(i - 1, adc_values[i]);
				//printf("adc[%d] = %d [%d]\r\n", i, adc_values[i], channel);
			}
			lastSend = now;
		}

		/*
左手 左右 = adc[2]   左小  右大
左手 上下 = adc[1]   下小  上大

右手 左右 = adc[4]   左小  右大
右手 上下 = adc[3]   下小  上大
		 */
		uint16_t validate_channel = 0;
		{
			uint8_t  channel_no = 4;
			uint16_t channel = process_adc_input(channel_no - 1, adc_values[channel_no]);
			//CrsfSerial_setChannel(1, channel); //Roll横滚
			crsf2_setChannel(1, channel);
			//printf("roll = %d\r\n", channel);
			//CrsfSerial_setChannel(11, channel); //对照验证
			crsf2_setChannel(11, channel);
			validate_channel += channel;
		}
		{
			uint8_t  channel_no = 3;
			uint16_t channel = process_adc_input(channel_no - 1, adc_values[channel_no]);
			//CrsfSerial_setChannel(2, channel); //俯仰（Pitch）
			crsf2_setChannel(2, channel);
			//printf("pitch = %d\r\n", channel);
			//CrsfSerial_setChannel(12, channel); //对照验证
			crsf2_setChannel(12, channel);

			validate_channel += channel;
		}
		{
			static uint16_t prev_value = 0;
			uint8_t  channel_no = 1;
			uint16_t channel = process_adc_input(channel_no - 1, adc_values[channel_no]);
			//CrsfSerial_setChannel(3, channel); //油门（Throttle）
			crsf2_setChannel(3, channel);
			if (channel < CRSF_CHANNEL_VALUE_MID && prev_value > (CRSF_CHANNEL_VALUE_MID + 20))
			{
				printf("throttle: %d => %d\r\n", prev_value, channel);
			}
			prev_value = channel;
			//CrsfSerial_setChannel(13, channel); //对照验证
			crsf2_setChannel(13, channel);
			validate_channel += channel;
		}
		{
			uint8_t  channel_no = 2;
			uint16_t channel = process_adc_input(channel_no - 1, adc_values[channel_no]);
			//CrsfSerial_setChannel(4, channel); //偏航（Yaw）
			crsf2_setChannel(4, channel);
			//printf("yaw = %d\r\n", channel);
			//CrsfSerial_setChannel(14, channel); //对照验证
			crsf2_setChannel(14, channel);

			validate_channel += channel;
		}

		//验证通道
		validate_channel = CRSF_CHANNEL_VALUE_1000 + validate_channel % (CRSF_CHANNEL_VALUE_2000 - CRSF_CHANNEL_VALUE_1000);
		//CrsfSerial_setChannel(15, validate_channel);
		crsf2_setChannel(15, validate_channel);

#if 1
		static uint32_t ModeTapTime = 0;
		static enum eFlightMode prev_mode = MODE_NONE;
		static bool btn_change_mode_down = false;
		if (HAL_GPIO_ReadPin(BTN_CHANG_MODE_GPIO_Port, BTN_CHANG_MODE_Pin) == GPIO_PIN_RESET)
		{
			if (ModeTapTime == 0)
			{
				ModeTapTime = now;
			}
			if ((now - ModeTapTime) > 200)
			{
				if (!btn_change_mode_down)
				{
					prev_mode = run_mode;
				}
				if (btn_change_mode_down && prev_mode != run_mode)
				{
					//遥测已经返回切换结果
					//CrsfSerial_setChannel(5, 1000);
					crsf2_setChannel(5, CRSF_CHANNEL_VALUE_1000);
				}
				else
				{
					//CrsfSerial_setChannel(5, 2000); //车/无人机 模式
					crsf2_setChannel(5, CRSF_CHANNEL_VALUE_2000);
				}
				btn_change_mode_down = true;
			}
		}
		else
		{
			btn_change_mode_down = false;
			ModeTapTime = 0;
			//CrsfSerial_setChannel(5, 1000);
			crsf2_setChannel(5, CRSF_CHANNEL_VALUE_1000);
		}

		if (HAL_GPIO_ReadPin(LIGHTING_GPIO_Port, LIGHTING_Pin) == GPIO_PIN_RESET)
		{
			//CrsfSerial_setChannel(6, 2000);  // 车灯
			crsf2_setChannel(6, CRSF_CHANNEL_VALUE_2000);
		}
		else
		{
			//CrsfSerial_setChannel(6, 1000);
			crsf2_setChannel(6, CRSF_CHANNEL_VALUE_1000);
		}

		static uint32_t HomeTapTime = 0;
		static bool btn_home_down = false;
		if (HAL_GPIO_ReadPin(BTN_HOME_GPIO_Port, BTN_HOME_Pin) == GPIO_PIN_RESET)
		{
			if (HomeTapTime == 0)
			{
				HomeTapTime = now;
			}
			if ((now - HomeTapTime) > 200)
			{
				if (!btn_home_down)
				{
					prev_mode = run_mode;
				}
				if (btn_home_down && prev_mode != run_mode)
				{
					//遥测已经返回切换结果
					//CrsfSerial_setChannel(7, 1000);
					crsf2_setChannel(7, CRSF_CHANNEL_VALUE_1000);
				}
				else
				{
					//CrsfSerial_setChannel(7, 2000); //返航
					crsf2_setChannel(7, CRSF_CHANNEL_VALUE_2000);
				}
				btn_home_down = true;
			}
		}
		else
		{
			btn_home_down = false;
			HomeTapTime = 0;
			//CrsfSerial_setChannel(7, 1000);
			crsf2_setChannel(7, CRSF_CHANNEL_VALUE_1000);
		}

#endif

	CRSFRadio.Loop();





}


