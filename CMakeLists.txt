cmake_minimum_required(VERSION 3.10)

project("Contacts App")


set(CMAKE_CXX_STANDARD 17)

add_subdirectory(/home/avan/Desktop/Libs/dotenv-cpp ${CMAKE_BINARY_DIR}/dot-env)
add_subdirectory(/home/avan/Desktop/Libs/oatpp ${CMAKE_BINARY_DIR}/oatpp-build)
add_subdirectory(/home/avan/Desktop/Libs/oatpp-postgresql ${CMAKE_BINARY_DIR}/oatpp-postgresql-build)

add_custom_target(copy_env COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/.env" "${CMAKE_BINARY_DIR}/.env" COMMENT "Copying .env into build directory")
add_custom_command(
  OUTPUT "${CMAKE_BINARY_DIR}/sql/001_init.sql"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/sql"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/sql" "${CMAKE_BINARY_DIR}/sql"
  DEPENDS ${SQL_FILES}
  COMMENT "Copying sql/ folder to build directory only if files changed"
)

add_custom_target(copy_migration_sql ALL
  DEPENDS "${CMAKE_BINARY_DIR}/sql/001_init.sql"
)


add_executable(contacts_binary main.cpp ./components/app.cpp ./components/configure.cpp ./services/contact-service.cpp)
add_dependencies(contacts_binary copy_env copy_migration_sql)

target_link_libraries(contacts_binary dotenv oatpp oatpp-postgresql)
