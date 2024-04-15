/**
 * Файл со Объектом "Задача"
 */
#ifndef TodoDto_hpp
#define TodoDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Стуктура отображающая объект "Задача", повторяет поля в БД
 */
class TodoDto : public oatpp::DTO {
  
  DTO_INIT(TodoDto, DTO)

  DTO_FIELD(Int32, todo_id, "todo_id");
  DTO_FIELD(String, title, "title");
  DTO_FIELD(Boolean , done, "done");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TodoDto_hpp */
