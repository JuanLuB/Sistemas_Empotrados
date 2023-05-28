/*
 * sensors.cpp
 *
 *  Created on: May 5, 2013
 *      Author: user
 */

#include <public/cdlocation_iface_v1.h>
#include <public/sensors.h>
#include <public/random.h>
#include <public/basic_types.h>

CDLocation Current_location;
extern CDLocation Next_location;

bool_t	   First_location=true;


CDLocation sensors_get_current_location(){

	First_location=true;

	if(First_location){

		Current_location.latitude=get_random_float(180);
		Current_location.longitude=get_random_float(180);
		First_location=false;

	}else{

		Current_location=Next_location;
	}

	return Current_location;

}

bool_t sensors_check_obstacles(){

	//random obstacles
	uint32_t aux=get_random_uint32(40);

	return(aux==1);

}
