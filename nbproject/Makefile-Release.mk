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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1215421894/Wire.o \
	${OBJECTDIR}/_ext/55187095/twi.o \
	${OBJECTDIR}/Compass.o \
	${OBJECTDIR}/IRSensor.o \
	${OBJECTDIR}/Motor.o \
	${OBJECTDIR}/RangeFinder.o \
	${OBJECTDIR}/Turtle.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/third-party/Button/Button.o \
	${OBJECTDIR}/third-party/HMC5883L/HMC5883L.o \
	${OBJECTDIR}/third-party/LED/LED.o \
	${OBJECTDIR}/third-party/Potentiometer/Potentiometer.o \
	${OBJECTDIR}/third-party/TimerOne/TimerOne.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/turtle

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/turtle: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/turtle ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1215421894/Wire.o: /Applications/Arduino.app/Contents/Resources/Java/libraries/Wire/Wire.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1215421894
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1215421894/Wire.o /Applications/Arduino.app/Contents/Resources/Java/libraries/Wire/Wire.cpp

${OBJECTDIR}/_ext/55187095/twi.o: /Applications/Arduino.app/Contents/Resources/Java/libraries/Wire/utility/twi.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/55187095
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/55187095/twi.o /Applications/Arduino.app/Contents/Resources/Java/libraries/Wire/utility/twi.c

${OBJECTDIR}/Compass.o: Compass.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Compass.o Compass.cpp

${OBJECTDIR}/IRSensor.o: IRSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/IRSensor.o IRSensor.cpp

${OBJECTDIR}/Motor.o: Motor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Motor.o Motor.cpp

${OBJECTDIR}/RangeFinder.o: RangeFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/RangeFinder.o RangeFinder.cpp

${OBJECTDIR}/Turtle.o: Turtle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Turtle.o Turtle.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/third-party/Button/Button.o: third-party/Button/Button.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/Button
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/Button/Button.o third-party/Button/Button.cpp

${OBJECTDIR}/third-party/HMC5883L/HMC5883L.o: third-party/HMC5883L/HMC5883L.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/HMC5883L
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/HMC5883L/HMC5883L.o third-party/HMC5883L/HMC5883L.cpp

${OBJECTDIR}/third-party/LED/LED.o: third-party/LED/LED.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/LED
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/LED/LED.o third-party/LED/LED.cpp

${OBJECTDIR}/third-party/Potentiometer/Potentiometer.o: third-party/Potentiometer/Potentiometer.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/Potentiometer
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/Potentiometer/Potentiometer.o third-party/Potentiometer/Potentiometer.cpp

${OBJECTDIR}/third-party/TimerOne/TimerOne.o: third-party/TimerOne/TimerOne.cpp 
	${MKDIR} -p ${OBJECTDIR}/third-party/TimerOne
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/third-party/TimerOne/TimerOne.o third-party/TimerOne/TimerOne.cpp

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
