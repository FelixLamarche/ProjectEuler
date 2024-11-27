# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ProjectEuler")

# Include sub-projects.
file(GLOB subdirs RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*)
set(PATTERN "Problem")

# Loop over each subdirectory
foreach(subdir ${subdirs})
    # Get the name of the folder (last component of the path)
    get_filename_component(dir_name ${subdir} NAME)
    # Check if the folder name starts with the specified pattern
    string(FIND ${dir_name} ${PATTERN} match_position)
    
    # Check if the subdirectory contains a CMakeLists.txt file
    if(EXISTS ${CMAKE_SOURCE_DIR}/${subdir}/CMakeLists.txt)
        # Add the subdirectory
        add_subdirectory(${subdir})
    # If the match position is 0, the folder name starts with the pattern
    elseif(match_position EQUAL 0)
        # Create and configure executable

        # Collect all .cpp and .h files in the current directory
        file(GLOB SOURCE_FILES "${subdir}/*.cpp" "${subdir}/*.h")

        # Create an executable with the name of the current directory
        add_executable(${dir_name} ${SOURCE_FILES})

        # Set the output directory for the executable
        set_target_properties(${dir_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${dir_name}
        )

        # Optional: Set include directories if needed (helps with IDE support)
        target_include_directories(${dir_name} PRIVATE ${dir_name})

        if (CMAKE_VERSION VERSION_GREATER 3.12)
          set_property(TARGET ${dir_name} PROPERTY CXX_STANDARD 20)
        endif()
    endif()
endforeach()
