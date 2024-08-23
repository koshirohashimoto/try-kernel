################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/context.c \
../kernel/inittsk.c \
../kernel/scheduler.c \
../kernel/syslib.c \
../kernel/task_manage.c \
../kernel/task_queue.c 

S_UPPER_SRCS += \
../kernel/dispatch.S 

OBJS += \
./kernel/context.o \
./kernel/dispatch.o \
./kernel/inittsk.o \
./kernel/scheduler.o \
./kernel/syslib.o \
./kernel/task_manage.o \
./kernel/task_queue.o 

S_UPPER_DEPS += \
./kernel/dispatch.d 

C_DEPS += \
./kernel/context.d \
./kernel/inittsk.d \
./kernel/scheduler.d \
./kernel/syslib.d \
./kernel/task_manage.d \
./kernel/task_queue.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/%.o: ../kernel/%.c kernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g3 -I"C:\work\TryKernel\include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernel/%.o: ../kernel/%.S kernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


