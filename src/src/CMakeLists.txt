set(target_name cameo)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
    ${target_name}
    PRIVATE
        src/main.cpp
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ${target_name}
    PRIVATE
        ${OpenCV_LIBS}
        managers
        cameowrapper
)
