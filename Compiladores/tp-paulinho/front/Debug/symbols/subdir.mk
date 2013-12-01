################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../symbols/Type.o 

CPP_SRCS += \
../symbols/Type.cpp 

OBJS += \
./symbols/Type.o 

CPP_DEPS += \
./symbols/Type.d 


# Each subdirectory must supply rules for building sources it contributes
symbols/%.o: ../symbols/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


