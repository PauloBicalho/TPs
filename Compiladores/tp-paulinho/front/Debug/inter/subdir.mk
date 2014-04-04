################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../inter/Constant.o \
../inter/Node.o \
../inter/Stmt.o \
../inter/Temp.o 

CPP_SRCS += \
../inter/Constant.cpp \
../inter/Node.cpp \
../inter/Stmt.cpp \
../inter/Temp.cpp 

OBJS += \
./inter/Constant.o \
./inter/Node.o \
./inter/Stmt.o \
./inter/Temp.o 

CPP_DEPS += \
./inter/Constant.d \
./inter/Node.d \
./inter/Stmt.d \
./inter/Temp.d 


# Each subdirectory must supply rules for building sources it contributes
inter/%.o: ../inter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


