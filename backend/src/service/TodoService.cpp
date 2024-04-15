/**
 * \file Файл сервиса "Задачи"
 */
#include "TodoService.hpp"
/**
 * \brief Метод, делающий запрос в БД и создающий объект ответа на запрос
 * \return Структура ответа с вложенной структурой расписания
 */
oatpp::Object<PageDto<oatpp::Object<TodoDto>>> TodoService::getAllTodo() {

  auto dbResult = m_database->getAllTodo();
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<TodoDto>>>();

  auto rsp = PageDto<oatpp::Object<TodoDto>>::createShared();
//  rsp->offset = 1;
//  rsp->limit = 1;
  rsp->count = items->size();
  rsp->items = items;

  return rsp;
}

oatpp::Object<TodoDto> TodoService::createTodo(const oatpp::Object<TodoDto>& dto) {
  auto dbResult = m_database->createTodo(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto todoId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

  return getTodoById((v_int32) todoId);
}

oatpp::Object<TodoDto> TodoService::getTodoById(const oatpp::Int32& id) {

  auto dbResult = m_database->getTodoById(id);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Task not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<TodoDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<TodoDto> TodoService::updateTodo(const oatpp::Object<TodoDto>& dto) {
  auto dbResult = m_database->updateTodo(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getTodoById(dto->todo_id);
}
