/*
 * planner.h
 *
 *  Created on: May 5, 2013
 *      Author: user
 */


#ifndef PLANNER_H_
#define PLANNER_H_

#include <public/cdpath_iface_v1.h>
#include <public/cdlocation_iface_v1.h>
#include <public/basic_types.h>


	CDLocation calNextPathStep(CDLocation prevStep,CDLocation target);

	void markObstacle(CDLocation obstacle);

	bool_t isValid(CDLocation location);

#endif /* PLANNER_H_ */
