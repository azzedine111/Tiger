/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline ast::NameTy& ArrayExp::type_name_get() const { return *type_name_;}
  inline ast::Exp& ArrayExp::size_get() const { return *size_;}
  inline ast::Exp* ArrayExp::init_get() const { return init_;}
} // namespace ast
