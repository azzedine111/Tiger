/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    LetExp(const Location& location, ast::ChunkList* decs, ast::Exp* body);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

    ast::ChunkList& decs_get() const;
    ast::Exp& body_get() const;

  protected:
    ast::ChunkList* decs_;
    ast::Exp* body_;
  };
} // namespace ast
#include <ast/let-exp.hxx>
