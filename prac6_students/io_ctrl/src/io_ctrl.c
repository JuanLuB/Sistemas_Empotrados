/*
 * io_ctrl.c
 *
 *  Created on: Apr 26, 2018
 *      Author: user
 */

#include <public/bprint_iface_v1.h>

void io_ctrl_config_avoid_obstacles_error(){

  print_string("error in Avoid Obstacles System");
  print_char('\n');
  print_char('\r');

}

void io_ctrl_config_path_planner_error(){
  print_string("Error in Planner Config");
  print_char('\n');
  print_char('\r');
}

void io_ctrl_path_tracker_error(){


  print_string("Error in Path Tracker Config");
  print_char('\n');
  print_char('\r');

}

void io_ctrl_recovery(){

  print_string("Power off all subsystems");
  print_char('\n');
  print_char('\r');

  print_string("Restart in 10 seconds");
  print_string("----------------------------------");
  print_char('\n');
  print_char('\r');

}

void io_ctrl_startup(){

  print_string("basic hw checking\n");

  print_string("power on sensors\n");

  print_string("power on actuators\n");

}


void io_ctrl_cal_step(){

  print_char('s');
}


void io_ctrl_max_num_of_step(){

  print_char('\n');
  print_char('\r');
  print_string("\tMAX");

}


void io_ctrl_next_path(){

  print_string("\n\rx");


}


void io_ctrl_go_to_path_step(uint8_t currentpathstep){

  print_char('\n');
  print_char('\r');
  print_char('+');
  print_uint8(currentpathstep);

}

void io_ctrl_check_obstacles(){

  print_char('.');

}

void io_ctrl_detect_obstacle(){
  print_char('\n');
  print_char('\r');
  print_string("\tOBST");
}

