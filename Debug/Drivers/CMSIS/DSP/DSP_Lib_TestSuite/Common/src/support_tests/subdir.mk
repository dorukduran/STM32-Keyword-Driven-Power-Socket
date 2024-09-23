################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/copy_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/fill_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_common_data.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_group.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/x_to_y_tests.c 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/copy_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/fill_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_common_data.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_group.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/x_to_y_tests.d 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/copy_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/fill_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_common_data.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_group.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/x_to_y_tests.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"C:/Users/ASUS/STM32CubeIDE/workspace_1.13.2/Projektpraktikum Aufgabe 1/Drivers/CMSIS/DSP/Include" -I"C:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-src-2f-support_tests

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-src-2f-support_tests:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/copy_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/copy_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/copy_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/copy_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/fill_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/fill_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/fill_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/fill_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_common_data.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_common_data.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_common_data.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_common_data.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_group.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_group.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_group.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/support_test_group.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/x_to_y_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/x_to_y_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/x_to_y_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/support_tests/x_to_y_tests.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-src-2f-support_tests

