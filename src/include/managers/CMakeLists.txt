set(target_name managers)

add_library(
    ${target_name}
    STATIC
        managers/managers.cpp
        managers/managers.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    ${target_name}
    PRIVATE
        ${OpenCV_LIBS}
)
