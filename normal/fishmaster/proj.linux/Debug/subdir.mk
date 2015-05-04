################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp 

OBJS += \
./main.o 

CPP_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -I../../ -I../../../../external -I../../../../extensions -I../../../../cocos2dx -I../../../../cocos2dx/include -I../../../../cocos2dx/kazmath/include -I../../../../cocos2dx/platform/linux -I../../../../cocos2dx/platform/third_party/linux -I../../../../CocosDenshion/include -I../../../../external/chipmunk/include/chipmunk -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


