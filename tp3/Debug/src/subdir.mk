################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ABB.cpp \
../src/Almacen.cpp \
../src/Destinos.cpp \
../src/EasyBMP.cpp \
../src/Juego.cpp \
../src/Jugador.cpp \
../src/Semilla.cpp \
../src/Terreno.cpp \
../src/main.cpp \
../src/tablero.cpp 

OBJS += \
./src/ABB.o \
./src/Almacen.o \
./src/Destinos.o \
./src/EasyBMP.o \
./src/Juego.o \
./src/Jugador.o \
./src/Semilla.o \
./src/Terreno.o \
./src/main.o \
./src/tablero.o 

CPP_DEPS += \
./src/ABB.d \
./src/Almacen.d \
./src/Destinos.d \
./src/EasyBMP.d \
./src/Juego.d \
./src/Jugador.d \
./src/Semilla.d \
./src/Terreno.d \
./src/main.d \
./src/tablero.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


