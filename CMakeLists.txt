cmake_minimum_required(VERSION 3.10)

project("Contacts App")


set(CMAKE_CXX_STANDARD 17)

add_subdirectory(/home/avan/Desktop/Libs/dotenv-cpp ${CMAKE_BINARY_DIR}/dot-env)
add_subdirectory(/home/avan/Desktop/Libs/oatpp ${CMAKE_BINARY_DIR}/oatpp-build)
add_subdirectory(/home/avan/Desktop/Libs/oatpp-postgresql ${CMAKE_BINARY_DIR}/oatpp-postgresql-build)

add_executable(contacts main.cpp)

target_link_libraries(contacts dotenv oatpp oatpp-postgresql)
