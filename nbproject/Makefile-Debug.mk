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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/calendarsheetwindow.o \
	${OBJECTDIR}/gregorian.o \
	${OBJECTDIR}/holiday.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/month.o \
	${OBJECTDIR}/printformoperation.o


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
LDLIBSOPTIONS=`pkg-config --libs gtkmm-3.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gtkcalendarsheet

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gtkcalendarsheet: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gtkcalendarsheet ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/calendarsheetwindow.o: calendarsheetwindow.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calendarsheetwindow.o calendarsheetwindow.cpp

${OBJECTDIR}/gregorian.o: gregorian.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gregorian.o gregorian.cpp

${OBJECTDIR}/holiday.o: holiday.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/holiday.o holiday.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/month.o: month.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/month.o month.cpp

${OBJECTDIR}/printformoperation.o: printformoperation.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/printformoperation.o printformoperation.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
