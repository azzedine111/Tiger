/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an RecordExp node.
    RecordExp(const Location& location, ast::NameTy* type_name, ast::fieldinits_type* fields);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;
    /** \} */


    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;

    ast::NameTy& type_name_get() const;
    ast::fieldinits_type& fields_get() const;

  protected:
    ast::NameTy* type_name_;
    ast::fieldinits_type* fields_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
