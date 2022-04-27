/**
 ** \file ast/break-exp.hh
 ** \brief Declaration of ast::BreakExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// BreakExp.
  class BreakExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /// Construct an RecordExp node.
    BreakExp(const Location& location);


    BreakExp(const BreakExp&) = delete;
    BreakExp& operator=(const BreakExp&) = delete;


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

  };
} // namespace ast
#include <ast/break-exp.hxx>
