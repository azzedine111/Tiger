/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <string>
#include <ast/exp.hh>

namespace ast
{
  /// StringExp.
  class StringExp : public Exp
  {
    // FIXME: Some code was deleted here.
      public:

          StringExp(const Location& location, std::string string);
          StringExp(const StringExp&) = delete;
          StringExp& operator=(const StringExp&) = delete;
          /// Destroy an StringExp node.

          void accept(ConstVisitor& v) const override;
          void accept(Visitor& v) override;

          const misc::symbol string_get() const;

     protected:
          misc::symbol string_;
  };
} // namespace ast
#include <ast/string-exp.hxx>
