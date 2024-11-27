# CMakeList.txt : CMake project for ProjectEuler, include source and define
# project specific logic here.
#

# Add source to this project's executable.

get_filename_component(dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(exec_name ${dir_name})
add_executable (${exec_name} "ProjectEuler.cpp" "Problem10.h" "Problem10.cpp" "../ProjectEuler/Sieve.h" "../ProjectEuler/Sieve.cpp")

set_target_properties(${exec_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${exec_name}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${exec_name} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
