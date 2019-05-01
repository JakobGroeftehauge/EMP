#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM

TARGET=main

#
# The base directory for TivaWare.  
# -- On a PC I had to add the drive letter of my USB drive or the ARM
#    linker would insert a %HOMEDRIVE%/%HOMEPATH% infront of the /Tiva
#
#ROOT=j:/Tiva/TivaWare_C_Series-2.0.1.11577
JESTER=/Users/Miller/Jester_Tiva
ROOT=${JESTER}/Tiva/TivaWare_C_Series-2.0.1.11577
FREERTOS=./FreeRTOS_Source

# Echo full command lines.. Comment out for terse
VERBOSE=1
DEBUG=1

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

CFLAGS += -Wno-unused-value -g
CFLAGS += -DmainCREATE_SIMPLE_BLINKY_DEMO_ONLY=0

#
# Where to find source files that do not live in this directory.
#
VPATH=${FREERTOS}/portable/GCC/ARM_CM4F
VPATH+=${FREERTOS}/portable/MemMang/
VPATH+=${FREERTOS}
VPATH+=${ROOT}/examples/boards/ek-tm4c123gxl/drivers
VPATH+=${ROOT}/utils
VPATH+=./Common_Demo_Source

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=${ROOT}
IPATH+=${FREERTOS}
IPATH+=${FREERTOS}/portable/GCC/ARM_CM4F
IPATH+=${FREERTOS}/include
IPATH+=${ROOT}/examples/boards/ek-tm4c123gxl
IPATH+=${ROOT}/third_party
IPATH+=./Common_Demo_Source/include

# for FreeRTOS demo code
IPATH+=../../common/include

LDFLAGS+= -L ${ROOT}/driverlib/${COMPILER}
#
# The default rule, which causes the FreeRTOS example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/${TARGET}.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the FreeRTOS example.
#
${COMPILER}/${TARGET}.axf: ${COMPILER}/heap_2.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/port.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/list.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/queue.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/tasks.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/timers.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/assert.o

${COMPILER}/${TARGET}.axf: ${COMPILER}/${TARGET}.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/main_blinky.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/main_full.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/hardware_tm4c123g.o
${COMPILER}/${TARGET}.axf: libdriver.a

${COMPILER}/${TARGET}.axf: ${COMPILER}/dynamic.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/BlockQ.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/GenQTest.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/PollQ.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/blocktim.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/countsem.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/death.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/integer.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/recmutex.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/semtest.o
${COMPILER}/${TARGET}.axf: ${COMPILER}/sp_flop.o

${COMPILER}/${TARGET}.axf: ti_tm4c123g.ld

SCATTERgcc_${TARGET}=ti_tm4c123g.ld
ENTRY_${TARGET}=ResetISR
CFLAGSgcc=-DTARGET_IS_BLIZZARD_RB1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

#
# A rule to flash and restarrt the program
#
flash: ${COMPILER}/${TARGET}.axf
	${JESTER}/lmflash --erase=all
	${JESTER}/lmflash --verify --reset --erase=all --frequency=8 ${COMPILER}/${TARGET}.bin
