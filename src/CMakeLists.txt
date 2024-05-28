cmake_minimum_required(VERSION 3.15)
project(Chat_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES 
  "main.cpp" 
  )
add_executable(${PROJECT_NAME} ${SOURCES})

