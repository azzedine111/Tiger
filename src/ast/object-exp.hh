/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp
  {
    // FIXME: Some code was deleted here.
    public:
        ObjectExp(const Location& location, ast::NameTy* type_name);
        ObjectExp(const ast::ObjectExp&) = delete;
        ObjectExp& operator=(const ObjectExp&) = delete;
        /// Destroy an StringExp node.

        void accept(ConstVisitor& v) const override;
        void accept(Visitor& v) override;

        ast::NameTy& type_name_get() const;

     protected:
        ast::NameTy *type_name_;

  };
} // namespace ast
#include <ast/object-exp.hxx>
