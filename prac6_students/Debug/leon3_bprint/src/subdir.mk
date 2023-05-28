################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../leon3_bprint/src/leon3_bprint.c \
../leon3_bprint/src/leon3_uart.c 

OBJS += \
./leon3_bprint/src/leon3_bprint.o \
./leon3_bprint/src/leon3_uart.o 

C_DEPS += \
./leon3_bprint/src/leon3_bprint.d \
./leon3_bprint/src/leon3_uart.d 


# Each subdirectory must supply rules for building sources it contributes
leon3_bprint/src/%.o: ../leon3_bprint/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C Compiler'
	sparc-rtems-gcc -I"/home/espectro90/Documents/EclipseWorkspace/prac6_students/rtems_osswr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_students/leon3_bprint/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_students/bprint_swr/include" -I"/home/espectro90/Documents/EclipseWorkspace/prac6_students/edroomsl_types_swr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


