/*
 * actuators.h
 *
 *  Created on: May 4, 2013
 *      Author: user
 */

#ifndef ACTUATORS_H_
#define ACTUATORS_H_

#include <public/cdlocation_iface_v1.h>
#include <public/basic_types.h>

void actuators_go_to_location(CDLocation location);

void actuators_halt();

void actuators_start();

#endif /* ACTUATORS_H_ */
