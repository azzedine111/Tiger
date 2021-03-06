/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#pragma once

#include <misc/symbol.hh>

namespace misc
{
  inline symbol& symbol::operator=(const symbol& rhs)
  {
    // FIXME: Some code was deleted here.
    this->obj_ = rhs.obj_;
    return *this;

  }

  inline bool symbol::operator==(const symbol& rhs) const
  {
    // FIXME: Some code was deleted here.
    return (this->obj_ == rhs.obj_);
  }

  inline bool symbol::operator!=(const symbol& rhs) const
  {
    // FIXME: Some code was deleted here.
    return !(*this == rhs);
  }

  inline std::ostream& operator<<(std::ostream& ostr, const symbol& the)
  {
    // FIXME: Some code was deleted here.
    ostr << the.get();
    return ostr;
  }

} // namespace misc
