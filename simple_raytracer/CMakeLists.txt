# https://stackoverflow.com/questions/51380520/how-to-write-cmake-for-multiple-cpp-files-and-headers-in-different-folders

message(STATUS "The CMake SOURCE directory is ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "The CMake SOURCE directory is ${CMAKE_SOURCE_DIR}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB 
	SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(app ${SOURCES})