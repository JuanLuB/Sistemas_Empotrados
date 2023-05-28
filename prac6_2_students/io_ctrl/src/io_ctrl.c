/*
 * io_ctrl.c
 *
 *  Created on: Apr 26, 2018
 *      Author: user
 */

#include <public/bprint_iface_v1.h>
#include <leon3_uart.h>
#include <rtems.h>


/* global variables */
//Declaración del identificador del identificador del Mutex y el nombre como variable global
//ToDO
rtems_id MutexId;
rtems_name MutexName = rtems_build_name('M', 'T', 'X', ' ');



void io_ctrl_init_Mutex(){

  rtems_attribute mutex_attribute = RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE | RTEMS_INHERIT_PRIORITY;

  rtems_semaphore_create(MutexName,1,mutex_attribute, RTEMS_NO_PRIORITY, &MutexId);


}

void io_ctrl_init(){

  io_ctrl_init_Mutex();

}

void io_ctrl_config_avoid_obstacles_error(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_string("error in Avoid Obstacles System");
  print_char('\n');
  print_char('\r');
  rtems_semaphore_release(MutexId);

}

void io_ctrl_config_path_planner_error(){
  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_string("Error in Planner Config");
  print_char('\n');
  print_char('\r');
  rtems_semaphore_release(MutexId);
}

void io_ctrl_path_tracker_error(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_string("Error in Path Tracker Config");
  print_char('\n');
  print_char('\r');
  rtems_semaphore_release(MutexId);
}

void io_ctrl_recovery(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_string("Power off all subsystems");
  print_char('\n');
  print_char('\r');

  print_string("Restart in 10 seconds");
  print_string("----------------------------------");
  print_char('\n');
  print_char('\r');
  rtems_semaphore_release(MutexId);
}

void io_ctrl_startup(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_string("basic hw checking\n");

  print_string("power on sensors\n");

  print_string("power on actuators\n");
  rtems_semaphore_release(MutexId);
}


void io_ctrl_cal_step(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_char('s');
  rtems_semaphore_release(MutexId);
}





void io_ctrl_max_num_of_step(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_char('\n');
  print_char('\r');
  print_string("\tMAX");
  rtems_semaphore_release(MutexId);


}


void io_ctrl_next_path(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_string("\n\rx");
  rtems_semaphore_release(MutexId);

}


void io_ctrl_go_to_path_step(uint8_t currentpathstep){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_char('\n');
  print_char('\r');
  print_char('+');
  print_uint8(currentpathstep);
  rtems_semaphore_release(MutexId);

}


void io_ctrl_check_obstacles(){

  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_char('.');
  rtems_semaphore_release(MutexId);
}

void io_ctrl_detect_obstacle(char aux){
  rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
  print_char('\n');
  print_char('\r');

  print_string("\tOBST  ");
  print_char(aux);
  print_char('\n');
  print_char('\r');
  rtems_semaphore_release(MutexId);
}

