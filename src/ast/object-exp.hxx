/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline ast::NameTy &ObjectExp::type_name_get() const { return *type_name_; }
} // namespace ast
