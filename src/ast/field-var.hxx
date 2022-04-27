/**
 ** \file ast/field-var.hxx
 ** \brief Inline methods of ast::FieldVar.
 */

#pragma once

#include <ast/field-var.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const ast::Var& FieldVar::var_get() const { return *var_; }
  inline ast::Var& FieldVar::var_get()  { return *var_; }

  inline misc::symbol FieldVar::name_get() const { return name_; }
} // namespace ast
