/**
 * \file Стрктуры ответа, с вложенностью для списков объектов
 */
#ifndef CRUD_PAGEDTO_HPP
#define CRUD_PAGEDTO_HPP

#include "UserDto.hpp"
#include "TodoDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * \brief Общая структура ответа для списка объектов
 */

template<class T>
class PageDto : public oatpp::DTO {

  DTO_INIT(PageDto, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD(UInt32, limit);
  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class UsersPageDto : public PageDto<oatpp::Object<UserDto>> {

  DTO_INIT(UsersPageDto, PageDto<oatpp::Object<UserDto>>)

};

class TodoPageDto : public PageDto<oatpp::Object<TodoDto>> {

  DTO_INIT(TodoPageDto, PageDto<oatpp::Object<TodoDto>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif //CRUD_PAGEDTO_HPP
