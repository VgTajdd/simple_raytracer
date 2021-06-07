# https://stackoverflow.com/questions/51380520/how-to-write-cmake-for-multiple-cpp-files-and-headers-in-different-folders

file(GLOB SOURCES "*.cpp")
add_executable(app ${SOURCES})