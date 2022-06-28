add_library(hw src/hw.cpp)
target_include_directories(hw PUBLIC include)
target_link_libraries(hw PUBLIC pico_stdlib)