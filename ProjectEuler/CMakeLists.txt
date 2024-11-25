# CMakeList.txt : CMake project for ProjectEuler, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ProjectEuler "ProjectEuler.cpp" "ProjectEuler.h" "Problem1.h" "Problem1.cpp" "Timer.h" "Timer.cpp" "Problem2.h" "Problem2.cpp" "Problem3.h" "Problem3.cpp" "Problem4.cpp" "Problem4.h" "Problem5.h" "Problem5.cpp" "Problem6.h" "Problem6.cpp" "Problem7.h" "Problem7.cpp" "Problem8.h" "Problem8.cpp" "Problem9.h" "Problem9.cpp" "Problem10.h" "Problem10.cpp" "Sieve.h" "Sieve.cpp" "Problem11.h" "Problem11.cpp" "Problem12.h" "Problem12.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProjectEuler PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
