set(target_name_Mans testMans)

include(GoogleTest)
include(CompileOptions)

add_executable(${target_name_Mans})
set_compile_options(${target_name_Mans})

target_sources(
  ${target_name_Mans}
  PRIVATE
    test_managers.cpp
)

target_link_libraries(
  ${target_name_Mans}
  PUBLIC
    managers
    GTest::gtest_main
)

target_include_directories(
  ${target_name_Mans}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
)
