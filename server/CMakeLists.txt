cmake_minimum_required(VERSION 3.0)

## Set our project name
project(carbonide-server)

## Use all the *.cpp files we found under this folder for the project
FILE(GLOB SRCS "*.cpp" 
               "database/*.cpp"
               "database/tables/*.cpp"
)
               
find_library(LATTENDER NAMES attender PATHS "../lib/attender/build" STATIC)
find_library(LSIMPLEJSON NAMES SimpleJSON PATHS "../lib/SimpleJSON/build" STATIC)
find_library(LSOCI_CORE NAMES soci_core PATHS "../lib/soci/build/lib" STATIC)
find_library(LBOOST_SYSTEM boost_system)
find_library(LBOOST_FILE_SYSTEM boost_filesystem)
find_library(LATOMIC atomic)
find_library(LSSL ssl)
find_library(LCRYPTO crypto)
find_library(LPTHREAD pthread)

if(LATOMIC STREQUAL "LATOMIC-NOTFOUND")
	set(LATOMIC "")
endif()
if(LPTHREAD STREQUAL "LPTHREAD-NOTFOUND")
	set(LPTHREAD "")
endif()
if(LBOOST_SYSTEM STREQUAL "LBOOST_SYSTEM-NOTFOUND")
	#message(FATAL_ERROR "Atomic library not found")
	find_library(LBOOST_SYSTEM boost_system-mt)
endif()
if(LBOOST_FILE_SYSTEM STREQUAL "LBOOST_FILE_SYSTEM-NOTFOUND")
	#message(FATAL_ERROR "Atomic library not found")
	find_library(LBOOST_FILE_SYSTEM boost_filesystem-mt)
endif()

message("-- External libraries")
message("	${LATTENDER}")
message("	${LSOCI_CORE}")
message("	${LSIMPLEJSON}")

## Define the executable
add_executable(carbonide-server ${SRCS})

target_include_directories(carbonide-server PUBLIC "../lib" "../lib/soci/build/include" "../lib/soci/include")
target_link_libraries(carbonide-server PRIVATE ${LSOCI_CORE} ${LATTENDER} ${LSIMPLEJSON} ${LBOOST_SYSTEM} ${LBOOST_FILE_SYSTEM} ${LSSL} ${LCRYPTO} ${LWS2_32} ${LMSWSOCK} atomic ${LPTHREAD})
