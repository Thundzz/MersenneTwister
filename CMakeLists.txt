cmake_minimum_required(VERSION 2.6)
project(MersenneTwister)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

find_package( PkgConfig REQUIRED)
pkg_check_modules( gsl REQUIRED gsl )




set(PROJECT_INCLUDE_DIR "include")

include_directories("${PROJECT_INCLUDE_DIR}")

file(GLOB_RECURSE source_files
       "src/*.c"
       "src/*.cpp"
       "src/*.h")   

add_executable(main ${source_files})
target_link_libraries( main ${gsl_LIBRARIES} )
