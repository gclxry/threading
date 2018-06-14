cmake_minimum_required (VERSION 3.0)
project (threading)


set(threading_sources
"message_loop.cc"
"message_loop.h"
)
add_library(threading ${threading_sources})

set(threading_sample_sources
"threading_sample_main.cc"
)
add_executable(threading_sample ${threading_sample_sources})
target_link_libraries(threading_sample threading)