include(GoogleTest)

add_executable(
  test
  test.cpp
)

target_link_libraries(
  test
  managers
  GTest::gtest_main
)

target_include_directories(
    test
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
