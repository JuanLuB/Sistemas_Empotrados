################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/vehicle/src/VehicleB.cpp \
../components/vehicle/src/VehicleS.cpp 

OBJS += \
./components/vehicle/src/VehicleB.o \
./components/vehicle/src/VehicleS.o 

CPP_DEPS += \
./components/vehicle/src/VehicleB.d \
./components/vehicle/src/VehicleS.d 


# Each subdirectory must supply rules for building sources it contributes
components/vehicle/src/%.o: ../components/vehicle/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/components/ccavoidobstaclesirq/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/leon3_bprint/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/io_ctrl/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/bprint_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/dataclasses/CDLocation/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/dataclasses/CDPath/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/actuators_drv/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/components/capathplanner/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/components/vehicle/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/planner_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/random_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/components/capathtracker/include" -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/config/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/sensors_drv/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/edroom_glue/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/edroombp_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/edroomsl_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/edroomsl_types_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


