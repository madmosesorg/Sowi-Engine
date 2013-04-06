################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AllRoundObject.cpp \
../src/DrawManager.cpp \
../src/SampleTexture.cpp \
../src/Sowi\ Engine.cpp \
../src/Vec.cpp \
../src/imageloader.cpp 

OBJS += \
./src/AllRoundObject.o \
./src/DrawManager.o \
./src/SampleTexture.o \
./src/Sowi\ Engine.o \
./src/Vec.o \
./src/imageloader.o 

CPP_DEPS += \
./src/AllRoundObject.d \
./src/DrawManager.d \
./src/SampleTexture.d \
./src/Sowi\ Engine.d \
./src/Vec.d \
./src/imageloader.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Sowi\ Engine.o: ../src/Sowi\ Engine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Sowi Engine.d" -MT"src/Sowi\ Engine.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


