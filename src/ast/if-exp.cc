/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/if-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  IfExp::IfExp(const Location& location, ast::Exp* test, ast::Exp* thenclause, ast::Exp* elseclause)
    : Exp(location)
    , test_(test)
    , thenclause_(thenclause)
    , elseclause_(elseclause)
  {}

  IfExp::IfExp(const Location& location, ast::Exp* test, ast::Exp* thenclause)
    : Exp(location)
    , test_(test)
    , thenclause_(thenclause)
    , elseclause_(0)
  {}

void IfExp::accept(ConstVisitor& v) const { v(*this); }

void IfExp::accept(Visitor& v) { v(*this); }
} // namespace ast
