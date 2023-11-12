find_package(benchmark CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    single_number
    code.cpp
)

target_link_libraries(
    single_number
    PUBLIC
    benchmark::benchmark
    Threads::Threads
)

#target_compile_options(single_number PUBLIC
#    -march=armv8.5-a
#)
