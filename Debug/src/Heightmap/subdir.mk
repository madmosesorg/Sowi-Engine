################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Heightmap/RandomHeightmap.cpp 

OBJS += \
./src/Heightmap/RandomHeightmap.o 

CPP_DEPS += \
./src/Heightmap/RandomHeightmap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Heightmap/%.o: ../src/Heightmap/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


