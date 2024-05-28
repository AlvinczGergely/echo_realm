cmake_minimum_required(VERSION 3.15)
project(Chat_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  Pistache
  GIT_REPOSITORY https://github.com/pistacheio/pistache.git
)
FetchContent_MakeAvailable(Pistache)


set(SOURCES 
  "main.cpp" 
  "services.cpp" 
  "logs.cpp" 
  )
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    pistache
  )
target_include_directories(${PROJECT_NAME} PRIVATE 
  ${Pistache_SOURCE_DIR}/include
  )

