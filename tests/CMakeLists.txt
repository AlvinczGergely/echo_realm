cmake_minimum_required(VERSION 3.14)
project(Chat_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  #GIT_REPOSITORY https://github.com/google/googletest.git
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  #GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(sail_tests
  user_tests.cpp
  ../src/pugixml/src/pugixml.cpp
  ../src/services.cpp
  ../src/generator.cpp
  ../src/logs.cpp
  ../src/user.cpp
  )
target_link_libraries(sail_tests
  PUBLIC
    GTest::gtest_main
    SQLiteCpp
    sqlite3
    pistache
    yaml-cpp::yaml-cpp

  )
target_include_directories(sail_tests PRIVATE 
  ${SQLiteCpp_SOURCE_DIR}/include
  ${Pistache_SOURCE_DIR}/include
  ${yaml-cpp_SOURCE_DIR}/include
  ${googletest_SOURCE_DIR}/googletest/include
  )


include(GoogleTest)
gtest_discover_tests(sail_tests)