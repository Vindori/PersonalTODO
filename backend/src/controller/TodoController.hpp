
/**
 * \file Файл контроллера расписаний
 */
#ifndef TodoController_hpp
#define TodoController_hpp

#include "service/TodoService.hpp"
#include "dto/PageDto.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * \brief Todo REST controller.
 * \details REST контроллер расписаний. Задает эндпоинты сервера, задает CORS политику и документирует себя через Swagger
 */
class TodoController : public oatpp::web::server::api::ApiController {
public:
  TodoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:

  TodoService m_todoService;
public:

  static std::shared_ptr<TodoController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
  ){
    return std::make_shared<TodoController>(objectMapper);
  }

  ADD_CORS(getTodo)
  ENDPOINT_INFO(getTodo) {
    info->summary = "get all stored todo";

    info->addResponse<oatpp::Object<TodoPageDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "todo/", getTodo)
  {
    auto response = createDtoResponse(Status::CODE_200, m_todoService.getAllTodo());
    response->putHeaderIfNotExists("Access-Control-Allow-Methods", "GET, POST, PUT, OPTIONS, DELETE");
    response->putHeaderIfNotExists("Access-Control-Allow-Origin", "*");
    return response;
  }

  ADD_CORS(getTodoById)
  ENDPOINT_INFO(getTodoById) {
    info->summary = "Get one Todo by todoId";

    info->addResponse<Object<TodoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["todoId"].description = "Todo Identifier";
  }

  ENDPOINT("GET", "todo/{todoId}", getTodoById,
           PATH(Int32, todoId))
  {
    return createDtoResponse(Status::CODE_200, m_todoService.getTodoById(todoId));
  }

  ENDPOINT_INFO(putTodo) {
    info->summary = "Update Todo by todoId";

    info->addConsumes<Object<TodoDto>>("application/json");

    info->addResponse<Object<TodoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["todoId"].description = "Todo Identifier";
  }
  ADD_CORS(putTodo)
  ENDPOINT("PUT", "todo/{todoId}", putTodo,
           PATH(Int32, todoId),
           BODY_DTO(Object<TodoDto>, todoDto))
  {
    todoDto->todo_id = todoId;

    auto response = createDtoResponse(Status::CODE_200, m_todoService.updateTodo(todoDto));
    response->putHeaderIfNotExists("Access-Control-Allow-Methods", "GET, POST, PUT, OPTIONS, DELETE");
    response->putHeaderIfNotExists("Access-Control-Allow-Origin", "*");
    return response;
  }


  ENDPOINT_INFO(createTodo) {
    info->summary = "Create new Todo";

    info->addConsumes<Object<TodoDto>>("application/json");

    info->addResponse<Object<TodoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ADD_CORS(createTodo)
  ENDPOINT("POST", "todo", createTodo,
           BODY_DTO(Object<TodoDto>, todoDto))
  {
    return createDtoResponse(Status::CODE_200, m_todoService.createTodo(todoDto));
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* TodoController_hpp */
