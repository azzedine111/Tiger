/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// SeqExp.
  class SeqExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /// Construct an RecordExp node.
    SeqExp(const Location& location, ast::exps_type* exps);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp&) = delete;


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

    ast::exps_type& exps_get() const;

  protected:
    ast::exps_type* exps_;
  };
} // namespace ast
#include <ast/seq-exp.hxx>
