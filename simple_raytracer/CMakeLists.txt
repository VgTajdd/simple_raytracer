# https://stackoverflow.com/questions/51380520/how-to-write-cmake-for-multiple-cpp-files-and-headers-in-different-folders

message(STATUS "The CMake current SOURCE directory is ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "The CMake SOURCE directory is ${CMAKE_SOURCE_DIR}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(PROJECT_NAME app)

file(GLOB 
	SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable( ${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/)