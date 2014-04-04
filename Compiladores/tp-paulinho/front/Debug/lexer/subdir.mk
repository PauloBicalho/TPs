################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lexer/Lexer.o \
../lexer/Word.o 

CPP_SRCS += \
../lexer/Lexer.cpp \
../lexer/Word.cpp 

OBJS += \
./lexer/Lexer.o \
./lexer/Word.o 

CPP_DEPS += \
./lexer/Lexer.d \
./lexer/Word.d 


# Each subdirectory must supply rules for building sources it contributes
lexer/%.o: ../lexer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


