################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cJSON.c 

CPP_SRCS += \
../cTcpsock.cpp \
../cTest4G.cpp \
../cTestAD.cpp \
../cTestBase.cpp \
../cTestBlueTooth.cpp \
../cTestDI.cpp \
../cTestDo.cpp \
../cTestNetworkInterface.cpp \
../cTestProcessing.cpp \
../cTestSDCard.cpp \
../main.cpp 

OBJS += \
./cJSON.o \
./cTcpsock.o \
./cTest4G.o \
./cTestAD.o \
./cTestBase.o \
./cTestBlueTooth.o \
./cTestDI.o \
./cTestDo.o \
./cTestNetworkInterface.o \
./cTestProcessing.o \
./cTestSDCard.o \
./main.o 

C_DEPS += \
./cJSON.d 

CPP_DEPS += \
./cTcpsock.d \
./cTest4G.d \
./cTestAD.d \
./cTestBase.d \
./cTestBlueTooth.d \
./cTestDI.d \
./cTestDo.d \
./cTestNetworkInterface.d \
./cTestProcessing.d \
./cTestSDCard.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-linux-gnueabi-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-none-linux-gnueabi-g++ -I/home/tarena/workspace/TCP_servrce2/lib -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


