# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = Windows-gnu-native-3.x-4.x
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
PRJ_ROOT_DIR := C:/Team537Code/RobotCode/CodyCliffordDemoCode
WS_ROOT_DIR := C:/Team537Code/RobotCode



#Global Build Macros
PROJECT_TYPE = APP
DEFINES = 


#BuildSpec specific Build Macros
TOOL_PATH = 
LIBPATH = 
LIBS = 
ADAPT_DEPS = 

IDE_INCLUDES = 

IDE_LIBRARIES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_C-Linker = 
DEBUGFLAGS_C++-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = 
DEBUGFLAGS_C++-Compiler = 
DEBUGFLAGS_C-Linker = 
DEBUGFLAGS_C++-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = 
endif


#Project Targets
PROJECT_TARGETS = CodyCliffordDemoCode/$(MODE_DIR)/CodyCliffordDemoCode.exe


#Rules

# CodyCliffordDemoCode
ifeq ($(DEBUG_MODE),1)
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Linker = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Linker = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Linker = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Linker = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CodyCliffordDemoCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = 
endif
CodyCliffordDemoCode/$(MODE_DIR)/% : IDE_INCLUDES = 
CodyCliffordDemoCode/$(MODE_DIR)/% : IDE_LIBRARIES = 
CodyCliffordDemoCode/$(MODE_DIR)/% : PROJECT_TYPE = APP
CodyCliffordDemoCode/$(MODE_DIR)/% : DEFINES = 
CodyCliffordDemoCode/$(MODE_DIR)/% : TOOL_PATH = 
CodyCliffordDemoCode/$(MODE_DIR)/% : LIBPATH = 
CodyCliffordDemoCode/$(MODE_DIR)/% : LIBS = 
CodyCliffordDemoCode/$(MODE_DIR)/% : ADAPT_DEPS = 
CodyCliffordDemoCode/$(MODE_DIR)/% : OBJ_DIR := CodyCliffordDemoCode/$(MODE_DIR)

CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/AutonomousSide.o : C:/Team537Code/RobotCode/CodyCliffordDemoCode/AutonomousSide.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Compiler) -ansi -fno-builtin -Wall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) $(DEFINES) -MD -MP -c -o "$@" "$<"


CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CameraManager.o : C:/Team537Code/RobotCode/CodyCliffordDemoCode/CameraManager.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Compiler) -ansi -fno-builtin -Wall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) $(DEFINES) -MD -MP -c -o "$@" "$<"


CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CollectorManager.o : C:/Team537Code/RobotCode/CodyCliffordDemoCode/CollectorManager.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Compiler) -ansi -fno-builtin -Wall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) $(DEFINES) -MD -MP -c -o "$@" "$<"


CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CompressorManager.o : C:/Team537Code/RobotCode/CodyCliffordDemoCode/CompressorManager.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Compiler) -ansi -fno-builtin -Wall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) $(DEFINES) -MD -MP -c -o "$@" "$<"


CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/DriveTrainManager.o : C:/Team537Code/RobotCode/CodyCliffordDemoCode/DriveTrainManager.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Compiler) -ansi -fno-builtin -Wall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) $(DEFINES) -MD -MP -c -o "$@" "$<"


CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/MyRobot.o : C:/Team537Code/RobotCode/CodyCliffordDemoCode/MyRobot.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Compiler) -ansi -fno-builtin -Wall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) $(DEFINES) -MD -MP -c -o "$@" "$<"


CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/ShooterManager.o : C:/Team537Code/RobotCode/CodyCliffordDemoCode/ShooterManager.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Compiler) -ansi -fno-builtin -Wall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) $(DEFINES) -MD -MP -c -o "$@" "$<"


OBJECTS_CodyCliffordDemoCode = CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/AutonomousSide.o \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CameraManager.o \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CollectorManager.o \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CompressorManager.o \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/DriveTrainManager.o \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/MyRobot.o \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/ShooterManager.o

CodyCliffordDemoCode/$(MODE_DIR)/CodyCliffordDemoCode.exe : $(OBJECTS_CodyCliffordDemoCode)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)g++ $(DEBUGFLAGS_C++-Linker)  -o "$@" $(OBJECTS_CodyCliffordDemoCode) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)

CodyCliffordDemoCode/$(MODE_DIR)/CodyCliffordDemoCode_compile_file : $(FILE) ;

_clean :: CodyCliffordDemoCode/$(MODE_DIR)/CodyCliffordDemoCode_clean

CodyCliffordDemoCode/$(MODE_DIR)/CodyCliffordDemoCode_clean : 
	$(TRACE_FLAG)if [ -d "CodyCliffordDemoCode" ]; then cd "CodyCliffordDemoCode"; rm -rf $(MODE_DIR); fi

DEP_FILES := CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/AutonomousSide.d CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CameraManager.d CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CollectorManager.d \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/CompressorManager.d CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/DriveTrainManager.d CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/MyRobot.d \
	 CodyCliffordDemoCode/$(MODE_DIR)/Objects/CodyCliffordDemoCode/ShooterManager.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
