################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Display/CalcFPS.cpp \
../src/Display/CameraView.cpp 

OBJS += \
./src/Display/CalcFPS.o \
./src/Display/CameraView.o 

CPP_DEPS += \
./src/Display/CalcFPS.d \
./src/Display/CameraView.d 


# Each subdirectory must supply rules for building sources it contributes
src/Display/%.o: ../src/Display/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


