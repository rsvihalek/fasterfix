# CMakeList.txt : CMake project for fasterfix, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (test_ff "test_ff.cpp" "test_ff.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_ff PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
