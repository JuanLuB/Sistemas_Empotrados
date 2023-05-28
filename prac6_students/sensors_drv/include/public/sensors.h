/*
 * sensors.h
 *
 *  Created on: May 4, 2013
 *      Author: user
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <public/cdlocation_iface_v1.h>
#include <public/basic_types.h>

CDLocation sensors_get_current_location();

bool_t sensors_check_obstacles();

#endif /* SENSORS_H_ */
