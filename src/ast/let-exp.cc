/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/let-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.

  LetExp::LetExp(const Location& location, ast::ChunkList* decs, ast::Exp* body)
    : Exp(location)
    , decs_(decs)
    , body_(body)
  {}

  void LetExp::accept(ConstVisitor& v) const { v(*this); }

  void LetExp::accept(Visitor& v) { v(*this); }
} // namespace ast
