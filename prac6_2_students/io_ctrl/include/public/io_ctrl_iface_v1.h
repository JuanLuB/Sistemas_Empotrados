/*
 * io_ctrl_iface_v1.h
 *
 *  Created on: Apr 26, 2018
 *      Author: user
 */

#ifndef IO_CTRL_IFACE_V1_H_
#define IO_CTRL_IFACE_V1_H_


#ifdef __cplusplus

extern "C" {

#endif

void io_ctrl_init();

void io_ctrl_config_avoid_obstacles_error();

void io_ctrl_config_path_planner_error();

void io_ctrl_path_tracker_error();

void io_ctrl_recovery();

void io_ctrl_startup();

void io_ctrl_cal_step();

void io_ctrl_max_num_of_step();

void io_ctrl_next_path();

void io_ctrl_go_to_path_step(uint8_t currentpathstep);

void io_ctrl_obst_detection_start_up();

void io_ctrl_check_obstacles();

void io_ctrl_detect_obstacle(char aux);

char io_ctrl_get_obstacle_info();

void io_ctrl_emu_set_obstacle_info(char aux);


#ifdef __cplusplus

}

#endif

#endif /* IO_CTRL_IFACE_V1_H_ */
