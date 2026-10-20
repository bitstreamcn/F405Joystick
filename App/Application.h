/*
 * Application.h
 *
 *  Created on: Jun 13, 2025
 *      Author: bitstream
 */
#ifndef APPLICATION_H_
#define APPLICATION_H_

typedef struct{
	void ( *Init )();
	void ( *Loop )();
}Application_s;

extern Application_s Application;




#endif /* APPLICATION_H_ */
