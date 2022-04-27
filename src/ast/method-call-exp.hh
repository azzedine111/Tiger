/**
 ** \file ast/method-call-exp.hh
 ** \brief Declaration of ast::MethodCallExp.
 */

#pragma once

#include <ast/call-exp.hh>
#include <ast/method-dec.hh>
#include <ast/var.hh>

namespace ast
{
  /** \class ast::MethodCallExp
   ** \brief Method call.
   **
   ** A method call is \em not a function call in the strict sense
   ** of object-oriented programming.  Inheritance is used as a
   ** factoring tool here.
   */

  class MethodCallExp : public CallExp
  {
    // FIXME: Some code was deleted here.
    public:
    /// Construct an MethodCallExp node.
    MethodCallExp(const Location& location, misc::symbol name, ast::exps_type* args, ast::Var* object);
    MethodCallExp(const MethodCallExp&) = delete;
    MethodCallExp& operator=(const MethodCallExp&) = delete;
    /// Destroy an IntExp node
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return stored integer value.
    misc::symbol &symbol_get() const;
    ast::exps_type& exps_get() const;
    ast::Var& object_get() const;
    /** \} */

  protected:
    misc::symbol* name_;
    ast::exps_type* args_;
    ast::Var* object_;
  };
} // namespace ast
#include <ast/method-call-exp.hxx>
