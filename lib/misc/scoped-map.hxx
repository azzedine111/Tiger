/** \file misc/scoped-map.hxx
** \brief Implementation of misc::scoped_map.
*/

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>
#include <range/v3/view/reverse.hpp>

namespace misc
{
 // FIXME: Some code was deleted here.

 template <typename Key, typename Data>
 void scoped_map<Key, Data>::put(const Key& key, const Data& value)
 {
   data_.push_back(std::make_pair(key, value));
 }

 template <typename Key, typename Data>
 Data scoped_map<Key, Data>::get(const Key& key) const
 {
   for (auto p : data_)
     {
       if (p.first == key)
         return p.second;
     }
   return nullptr;
 }

 template <typename Key, typename Data>
 std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
 {
   for (auto p : data_)
     {
       ostr << "key: " << p.first << " | value: " << p.second << "\n";
     }
   return ostr;
 }

 template <typename Key, typename Data>
 void scoped_map<Key, Data>::scoped_begin()
 {
 }

 template <typename Key, typename Data>
 inline std::ostream& operator<<(std::ostream& ostr,
                                 const scoped_map<Key, Data>& tbl)
 {
   return tbl.dump(ostr);
 }

} // namespace misc