#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=avr-gcc
CCC=avr-g++
CXX=avr-g++
FC=gfortran
AS=avr-as

# Macros
CND_PLATFORM=Arduino-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/IRSensor.o \
	${OBJECTDIR}/Motor.o \
	${OBJECTDIR}/RangeFinder.o \
	${OBJECTDIR}/Turtle.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/third-party/Button/Button.o \
	${OBJECTDIR}/third-party/LED/LED.o \
	${OBJECTDIR}/third-party/Potentiometer/Potentiometer.o \
	${OBJECTDIR}/third-party/TimerOne/TimerOne.o


# C Compiler Flags
CFLAGS=${FLAGS_GCC}

# CC Compiler Flags
CCFLAGS=${FLAGS_GPP}
CXXFLAGS=${FLAGS_GPP}

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Lthird-party

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/turtle

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/turtle: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	avr-gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/turtle ${OBJECTFILES} ${LDLIBSOPTIONS} ${FLAGS_LINKER}

${OBJECTDIR}/IRSensor.o: IRSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button -I../libraries/PID_v1 ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/IRSensor.o IRSensor.cpp

${OBJECTDIR}/Motor.o: Motor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button -I../libraries/PID_v1 ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/Motor.o Motor.cpp

${OBJECTDIR}/RangeFinder.o: RangeFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button -I../libraries/PID_v1 ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/RangeFinder.o RangeFinder.cpp

${OBJECTDIR}/Turtle.o: Turtle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button -I../libraries/PID_v1 ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/Turtle.o Turtle.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button -I../libraries/PID_v1 ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/third-party/Button/Button.o: third-party/Button/Button.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/Button
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/Button/Button.o third-party/Button/Button.cpp

${OBJECTDIR}/third-party/LED/LED.o: third-party/LED/LED.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/LED
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/LED/LED.o third-party/LED/LED.cpp

${OBJECTDIR}/third-party/Potentiometer/Potentiometer.o: third-party/Potentiometer/Potentiometer.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/Potentiometer
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/Potentiometer/Potentiometer.o third-party/Potentiometer/Potentiometer.cpp

${OBJECTDIR}/third-party/TimerOne/TimerOne.o: third-party/TimerOne/TimerOne.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/TimerOne
	${RM} $@.d
	$(COMPILE.cc) -g -I${INCLUDE} -Ithird-party/LED -Ithird-party/PinChangeInt -Ithird-party/Potentiometer -Ithird-party/TimerOne -Ithird-party/Button ${FLAGS_GPP} -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/TimerOne/TimerOne.o third-party/TimerOne/TimerOne.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/turtle

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
