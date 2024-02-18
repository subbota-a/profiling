find_package(benchmark CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
    single_number
    code.cpp
    main.cpp
    code.h
)

target_link_libraries(
    single_number
    PUBLIC
    benchmark::benchmark
    Threads::Threads
)

target_compile_options(single_number PUBLIC
    $<IF:$<CXX_COMPILER_ID:MSVC>,/arch:AVX512 /favor:INTEL64,-march=x86-64-v4>
)
