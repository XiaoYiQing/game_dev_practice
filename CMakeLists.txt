cmake_minimum_required(VERSION 3.5)
project(MyFuncs)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


# Create our main executable.
add_executable( myapp src/main.cpp )


# ======================================================================= >>>>>
#   SFML Portable Project Inclusion
# ======================================================================= >>>>>

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add executable.
target_link_libraries(myapp PUBLIC sfml-graphics)
target_compile_features(myapp PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET myapp
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:myapp>
        VERBATIM)
endif()

# ======================================================================= <<<<<




# ======================================================================= >>>>>
#   Present Project Additional Resource Inclusion
# ======================================================================= >>>>>

# Define the source directory and a destination directory as variables.
set(RES_XYQ_DIR_SRC ${CMAKE_SOURCE_DIR}/res)
set(RES_XYQ_DIR_OUT ${CMAKE_BINARY_DIR}/res)
file(GLOB MY_IMG_FILES
    ${RES_XYQ_DIR_SRC}/*.jpg
    ${RES_XYQ_DIR_SRC}/*.png
)
# Copies the file from the source directory to the build directory
configure_file(${RES_XYQ_DIR_SRC}/Arial.ttf ${RES_XYQ_DIR_OUT}/Arial.ttf COPYONLY)
file(COPY ${MY_IMG_FILES} DESTINATION ${RES_XYQ_DIR_OUT})

# Create a variable that you can access directly during runtime as a preprocessor definition.
target_compile_definitions( myapp
    PRIVATE RES_PATH_XYQ="${RES_XYQ_DIR_OUT}"
)

# ======================================================================= <<<<<



# ======================================================================= >>>>>
#   Sub-Directories Inclusion
# ======================================================================= >>>>>

# ----------------------------------------------------------------- >>>>>
#   Present Project SFML Utilities Inclusion
# ----------------------------------------------------------------- >>>>>

# Add a sub directory.
add_subdirectory( SFML_utils )
target_link_libraries( myapp PUBLIC SFML_utils )
target_include_directories(myapp PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/SFML_utils"
)

# ----------------------------------------------------------------- <<<<<

# ----------------------------------------------------------------- >>>>>
#   Game Functions Inclusion
# ----------------------------------------------------------------- >>>>>

add_subdirectory( SFML_games )
target_link_libraries( myapp PUBLIC SFML_games )
target_include_directories(myapp PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML_games"
)

# ----------------------------------------------------------------- <<<<<

# ----------------------------------------------------------------- >>>>>
#   Test Functions Inclusion
# ----------------------------------------------------------------- >>>>>

add_subdirectory( tests )
target_link_libraries( myapp PUBLIC tests )
target_include_directories(myapp PUBLIC
    "${PROJECT_SOURCE_DIR}/tests"
)

# ----------------------------------------------------------------- <<<<<


# ======================================================================= <<<<<




