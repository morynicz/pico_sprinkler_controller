add_library(utils src/io_testing.cpp)
target_include_directories(utils PUBLIC include)

if(TESTING_ENVIRONMENT)
add_subdirectory(tests)
endif()