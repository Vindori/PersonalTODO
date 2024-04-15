
#ifndef CRUD_TODOSERVICE_HPP
#define CRUD_TODOSERVICE_HPP

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class TodoService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:
  oatpp::Object<PageDto<oatpp::Object<TodoDto>>> getAllTodo();
  oatpp::Object<TodoDto> createTodo(const oatpp::Object<TodoDto>& dto);
  oatpp::Object<TodoDto> getTodoById(const oatpp::Int32& id);
  oatpp::Object<TodoDto> updateTodo(const oatpp::Object<TodoDto>& dto);

};

#endif //CRUD_TODOSERVICE_HPP
