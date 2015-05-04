################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/AppDelegate.cpp \
/Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/FishUtils.cpp \
/Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/Sound.cpp \
/Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/pgPlatformFactory.cpp 

OBJS += \
./Classes/Foundation/AppDelegate.o \
./Classes/Foundation/FishUtils.o \
./Classes/Foundation/Sound.o \
./Classes/Foundation/pgPlatformFactory.o 

CPP_DEPS += \
./Classes/Foundation/AppDelegate.d \
./Classes/Foundation/FishUtils.d \
./Classes/Foundation/Sound.d \
./Classes/Foundation/pgPlatformFactory.d 


# Each subdirectory must supply rules for building sources it contributes
Classes/Foundation/AppDelegate.o: /Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/AppDelegate.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -I../../ -I../../../../external -I../../../../extensions -I../../../../cocos2dx -I../../../../cocos2dx/include -I../../../../cocos2dx/kazmath/include -I../../../../cocos2dx/platform/linux -I../../../../cocos2dx/platform/third_party/linux -I../../../../CocosDenshion/include -I../../../../external/chipmunk/include/chipmunk -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/Foundation/FishUtils.o: /Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/FishUtils.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -I../../ -I../../../../external -I../../../../extensions -I../../../../cocos2dx -I../../../../cocos2dx/include -I../../../../cocos2dx/kazmath/include -I../../../../cocos2dx/platform/linux -I../../../../cocos2dx/platform/third_party/linux -I../../../../CocosDenshion/include -I../../../../external/chipmunk/include/chipmunk -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/Foundation/Sound.o: /Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/Sound.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -I../../ -I../../../../external -I../../../../extensions -I../../../../cocos2dx -I../../../../cocos2dx/include -I../../../../cocos2dx/kazmath/include -I../../../../cocos2dx/platform/linux -I../../../../cocos2dx/platform/third_party/linux -I../../../../CocosDenshion/include -I../../../../external/chipmunk/include/chipmunk -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/Foundation/pgPlatformFactory.o: /Users/andy/Documents/cocos2d-x-2.1.4/projects/fishmaster/Classes/Foundation/pgPlatformFactory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -I../../ -I../../../../external -I../../../../extensions -I../../../../cocos2dx -I../../../../cocos2dx/include -I../../../../cocos2dx/kazmath/include -I../../../../cocos2dx/platform/linux -I../../../../cocos2dx/platform/third_party/linux -I../../../../CocosDenshion/include -I../../../../external/chipmunk/include/chipmunk -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


