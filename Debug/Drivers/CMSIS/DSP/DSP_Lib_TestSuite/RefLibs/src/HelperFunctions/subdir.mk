################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.c 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.d 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"C:/Users/ASUS/STM32CubeIDE/workspace_1.13.2/Projektpraktikum Aufgabe 1/Drivers/CMSIS/DSP/Include" -I"C:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-HelperFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-HelperFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-HelperFunctions

