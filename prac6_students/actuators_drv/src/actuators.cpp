/*
 * actuators.cpp
 *
 *  Created on: May 5, 2013
 *      Author: user
 */

#include <public/actuators.h>


bool IsHalted=true;

extern CDLocation Current_location;
CDLocation Next_location;

void actuators_go_to_location(CDLocation location){

	if(!IsHalted){

		Next_location=location;

	}

}

void actuators_halt(){

	IsHalted=true;

	Next_location=Current_location;

}

void actuators_start(){

	IsHalted=false;

	Next_location=Current_location;
}
