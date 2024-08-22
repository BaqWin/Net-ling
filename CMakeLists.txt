cmake_minimum_required(VERSION 3.23)
project(net-ling)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

execute_process(COMMAND brew --prefix pcapplusplus OUTPUT_VARIABLE PCAPPLUSPLUS_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)

find_library(PCAPPLUSPLUS_LIB NAMES Pcap++ PATHS /usr/local/lib NO_DEFAULT_PATH)
find_library(PACKETPLUSPLUS_LIB NAMES Packet++ PATHS /usr/local/lib NO_DEFAULT_PATH)
find_library(COMMONPLUSPLUS_LIB NAMES Common++ PATHS /usr/local/lib NO_DEFAULT_PATH)
find_library(LIBPCAP_LIB NAMES pcap)
find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
find_library(SYSTEMCONFIGURATION_FRAMEWORK SystemConfiguration)

find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(src/app)
add_subdirectory(src/tests)
