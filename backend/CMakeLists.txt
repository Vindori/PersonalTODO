cmake_minimum_required(VERSION 3.15)
set(project_name PersonalTodo)
project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/controller/StaticController.hpp
        src/controller/UserController.hpp

        src/controller/TodoController.hpp

        src/db/UserDb.hpp

        src/dto/PageDto.hpp
        src/dto/StatusDto.hpp
        src/dto/UserDto.hpp
        src/dto/TodoDto.hpp

        src/service/UserService.cpp
        src/service/UserService.hpp

        src/service/TodoService.hpp
        src/service/TodoService.cpp

        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp)

## include directories
target_include_directories(${project_name}-lib PUBLIC src)
#--------------------------------------------------------------------------------------------------
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
#conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE ..
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
target_link_libraries(${project_name}-lib ${CONAN_LIBS})

#--------------------------------------------------------------------------------------------------

add_definitions(
        ## define path to swagger-ui static resources folder
        #        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"
        -DOATPP_SWAGGER_RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/swagger"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(${project_name}-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## add executables

add_executable(${project_name}-exe src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)

install(TARGETS ${project_name}-exe DESTINATION ${project_name})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/../frontend/dist/ DESTINATION ${project_name}/view)
