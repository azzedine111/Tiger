/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{
  /// AssignExp.
  class AssignExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /// Construct an RecordExp node.
    AssignExp(const Location& location, ast::Var* var, ast::Exp* exp);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

    ast::Var& var_get() const;
    ast::Exp& exp_get() const;

  protected:
    ast::Var* var_;
    ast::Exp* exp_;
  };
} // namespace ast
#include <ast/assign-exp.hxx>
