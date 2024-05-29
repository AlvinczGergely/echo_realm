cmake_minimum_required(VERSION 3.15)
project(Chat_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(SQLITECPP_RUN_CPPLINT OFF CACHE INTERNAL "") 
FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG        3.3.1
)
FetchContent_MakeAvailable(SQLiteCpp)

FetchContent_Declare(
  Pistache
  GIT_REPOSITORY https://github.com/pistacheio/pistache.git
)
FetchContent_MakeAvailable(Pistache)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_GetProperties(yaml-cpp)


set(SOURCES 
  "main.cpp" 
  "generator.cpp" 
  "user.cpp" 
  "services.cpp" 
  "logs.cpp" 
  "pugixml/src/pugixml.cpp"
  )
add_executable(${PROJECT_NAME} ${SOURCES})

set(USER_GENERATOR_SOURCES "user_generator.cpp" "user.cpp" "generator.cpp" "pugixml/src/pugixml.cpp" "logs.cpp")
set(USER_GENERATOR "User_Generator")
add_executable(${USER_GENERATOR} ${USER_GENERATOR_SOURCES})

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    SQLiteCpp
    sqlite3
    pistache
    yaml-cpp::yaml-cpp
  )

target_link_libraries(${USER_GENERATOR}
  PUBLIC
    yaml-cpp::yaml-cpp
    SQLiteCpp
    sqlite3
  )

target_include_directories(${PROJECT_NAME} PRIVATE 
  ${SQLiteCpp_SOURCE_DIR}/include
  ${Pistache_SOURCE_DIR}/include
  ${yaml-cpp_SOURCE_DIR}/include
  )


target_include_directories(${USER_GENERATOR} PRIVATE 
  ${yaml-cpp_SOURCE_DIR}/include
  ${SQLiteCpp_SOURCE_DIR}/include
  )


