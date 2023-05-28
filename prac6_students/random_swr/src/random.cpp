/*
 * random.cpp
 *
 *  Created on: May 4, 2013
 *      Author: user
 */
#include <public/edroombp.h>

static uint32_t seed=0x91D7AF34;

uint32_t get_random_uint32(uint32_t max){


	seed=seed*1103515245 + 12345;
	return ((seed/65536)%(max+1));


}

float get_random_float(float max_module){

	uint32_t aux=(uint32_t)max_module;
	float random=get_random_uint32(aux);
	aux=(uint32_t)(max_module-random)*1000;
	random+=get_random_uint32(aux)/1000.0;
	if(get_random_uint32(5)>2)
		random=-random;

	return random;
}


