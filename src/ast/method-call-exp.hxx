/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline misc::symbol& MethodCallExp::symbol_get() const { return *name_;}
  inline ast::exps_type& MethodCallExp::exps_get() const { return *args_;}
  inline ast::Var& MethodCallExp::object_get() const { return *object_;}
} // namespace ast
