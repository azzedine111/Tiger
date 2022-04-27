/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /// Construct an IfExp node.
    IfExp(const Location& location, ast::Exp* test, ast::Exp* thenclause,
          ast::Exp* elseclause);
    IfExp(const Location& location, ast::Exp* test, ast::Exp* thenclause);

    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IfExp&) = delete;


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

    ast::Exp& test_get() const;
    ast::Exp& thenclause_get() const;
    ast::Exp* elseclause_get() const;

  protected:
    ast::Exp* test_;
    ast::Exp* thenclause_;
    ast::Exp* elseclause_;
  };
} // namespace ast
#include <ast/if-exp.hxx>
