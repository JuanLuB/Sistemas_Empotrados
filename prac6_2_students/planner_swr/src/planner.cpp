/*
 * planner.cpp
 *
 *  Created on: May 5, 2013
 *      Author: user
 */

#define MAX_NUMBER_OF_OBSTACLES  1024

#include <public/planner.h>
#include <public/random.h>

uint16_t   MarkedObstaclesNumber=0;

CDLocation MarkedObstaclesLocations[MAX_NUMBER_OF_OBSTACLES];

CDLocation calNextPathStep(CDLocation prevStep, CDLocation target){

		CDLocation nextStep;

		if(target.latitude>prevStep.latitude)
			nextStep.latitude=prevStep.latitude+0.001;
		else
			nextStep.latitude=prevStep.latitude-0.001;

		if(target.longitude>prevStep.longitude)
			nextStep.longitude=prevStep.longitude+0.001;
		else
			nextStep.longitude=prevStep.longitude-0.001;

		while(!isValid(nextStep)){

			uint32_t aux=get_random_uint32(2);

			if(aux==0)
				nextStep.longitude=prevStep.longitude +0.001;
			else if(aux==1)
				nextStep.longitude=prevStep.longitude;
			else
				nextStep.longitude=prevStep.longitude -0.001;

			aux=get_random_uint32(2);


			if(aux==0)
				nextStep.latitude=prevStep.latitude +0.001;
			else if(aux==1)
				nextStep.latitude=prevStep.latitude;
			else
				nextStep.latitude=prevStep.latitude -0.001;
		}

		return nextStep;
}

void markObstacle(CDLocation obstacle){

		if(MarkedObstaclesNumber<MAX_NUMBER_OF_OBSTACLES){
			MarkedObstaclesLocations[MarkedObstaclesNumber]=obstacle;
			MarkedObstaclesNumber++;
		}

}

bool_t isValid(CDLocation location){

		bool_t valid=true;
		uint16_t i;

		for(i=0; (i< MarkedObstaclesNumber)&&valid; i++){

			if((location.latitude==MarkedObstaclesLocations[i].latitude)
				&&
				(location.longitude==MarkedObstaclesLocations[i].longitude))

				valid=false;
		}
		return valid;

}
