find_package(benchmark CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(compare_benchmark
    main.cpp
    compare.cpp
    compare.h
)

target_link_libraries(
    compare_benchmark
    PUBLIC
    benchmark::benchmark
    Threads::Threads
)
