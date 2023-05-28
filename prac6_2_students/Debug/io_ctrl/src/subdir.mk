################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../io_ctrl/src/io_ctrl.c 

OBJS += \
./io_ctrl/src/io_ctrl.o 

C_DEPS += \
./io_ctrl/src/io_ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
io_ctrl/src/%.o: ../io_ctrl/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C Compiler'
	sparc-rtems-gcc -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/rtems_osswr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/leon3_bprint/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/bprint_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_2_students/edroomsl_types_swr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


