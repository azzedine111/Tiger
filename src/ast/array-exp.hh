/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /// Construct an RecordExp node.
    ArrayExp(const Location& location, ast::NameTy* type_name, ast::Exp* size, ast::Exp* init);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

    ast::NameTy& type_name_get() const;
    ast::Exp& size_get() const;
    ast::Exp* init_get() const;


  protected:
    ast::NameTy* type_name_;
    ast::Exp* size_;
    ast::Exp* init_;
  };
} // namespace ast
#include <ast/array-exp.hxx>
