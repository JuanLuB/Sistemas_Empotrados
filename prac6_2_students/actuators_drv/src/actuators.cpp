/*
 * actuators.cpp
 *
 *  Created on: May 5, 2013
 *      Author: user
 */

#include <public/actuators.h>
#include <public/sensors_iface_v1.h>
#include <leon3_uart.h>
#include <public/io_ctrl_iface_v1.h>

bool IsHalted=true;

extern CDLocation Current_location;
CDLocation Next_location;

uint32_t * LEON3_IFORCE =  (uint32_t *) (0x80000000 + 0x208);

void actuators_go_to_location(CDLocation location){

	if(!IsHalted){

		Next_location=location;

	}
	if(sensors_check_obstacles()){
	        *LEON3_IFORCE = (1 << 2);
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
