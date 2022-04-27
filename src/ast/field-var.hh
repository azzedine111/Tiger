/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// FieldVar.
  class FieldVar : public Var
  {
    // FIXME: Some code was deleted here.
  public:
    FieldVar(const Location& location, ast::Var* var, misc::symbol name);
    FieldVar(const FieldVar&) = delete;
    FieldVar& operator=(const FieldVar&) = delete;


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

    const ast::Var& var_get() const;
    ast::Var& var_get();

    misc::symbol name_get() const;

  protected:
    ast::Var* var_;
    misc::symbol name_;
  };
} // namespace ast
#include <ast/field-var.hxx>
