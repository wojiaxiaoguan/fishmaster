################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/config/CConfig.cpp 

OBJS += \
./Classes/config/CConfig.o 

CPP_DEPS += \
./Classes/config/CConfig.d 


# Each subdirectory must supply rules for building sources it contributes
Classes/config/CConfig.o: /Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/config/CConfig.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -I../../ -I../../../../external -I../../../../extensions -I../../../../cocos2dx -I../../../../cocos2dx/include -I../../../../cocos2dx/kazmath/include -I../../../../cocos2dx/platform/linux -I../../../../cocos2dx/platform/third_party/linux -I../../../../CocosDenshion/include -I../../../../external/chipmunk/include/chipmunk -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


