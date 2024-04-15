/**
 * \file Файл описания взаимодействия с БД
 */
#ifndef CRUD_USERDB_HPP
#define CRUD_USERDB_HPP

#include "dto/UserDto.hpp"
#include "dto/TodoDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * \brief В классе содержатся методы, выполняющие SQL запросы. По своей сути является моделью
 */
class UserDb : public oatpp::orm::DbClient {
public:

  UserDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
      : oatpp::orm::DbClient(executor) {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("UserDb", "Migration - OK. Version=%lld.", version);

  }

  QUERY(createUser,
        "INSERT INTO AppUser"
        "(username, email, password, role) VALUES "
        "(:user.username, :user.email, :user.password, :user.role);",
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(updateUser,
        "UPDATE AppUser "
        "SET "
        " username=:user.username, "
        " email=:user.email, "
        " password=:user.password, "
        " role=:user.role "
        "WHERE "
        " id=:user.id;",
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(getUserById,
        "SELECT * FROM AppUser WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllUsers,
        "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteUserById,
        "DELETE FROM AppUser WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllTodo, "SELECT * FROM Todo")

  QUERY(getTodoById,
        "SELECT * FROM Todo WHERE todo_id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(updateTodo,
        "UPDATE Todo "
        "SET "
        " title=:todo.title, "
        " done=:todo.done "
        "WHERE "
        " todo_id=:todo.todo_id;",
        PARAM(oatpp::Object<TodoDto>, todo))

  QUERY(createTodo,
        " INSERT INTO Todo "
        " (title, done) VALUES  "
        " (:todo.title, :todo.done); ",
        PARAM(oatpp::Object<TodoDto>, todo))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_USERDB_HPP
