# https://stackoverflow.com/questions/51380520/how-to-write-cmake-for-multiple-cpp-files-and-headers-in-different-folders
# https://stackoverflow.com/questions/24395517/cmake-executable-name/45663205

message(STATUS "The CMake current SOURCE directory is ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "The CMake SOURCE directory is ${CMAKE_SOURCE_DIR}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB
	SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "app")
#target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/)
