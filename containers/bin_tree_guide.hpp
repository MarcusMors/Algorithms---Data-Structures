// Copyright (C) 2022 José Enrique Vilca Campana
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct bin_node
{
  T value{};
  bin_node<T> *nodes[2]{ nullptr, nullptr };// NOLINT C-style array
  bin_node<T> *&left{ nodes[0] };
  bin_node<T> *&right{ nodes[1] };

  bin_node() = default;
  ~bin_node() = default;
  explicit bin_node(const T t_value) : value{ t_value } {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T> class CBinTree
{
public:
  CBinTree();
  ~CBinTree();
  bool insert(T t_value);
  bool Remove(T t_value);
  void Print();

private:
  bool find(T t_value, bin_node<T> **&t_ptr);
  bin_node<T> **Rep(bin_node<T> **t_ptr);
  void InOrder(bin_node<T> *n);
  bin_node<T> *m_root{ nullptr };
  bool m_b{ true };
};

template<class T> CBinTree<T>::~CBinTree()
{
  // ?
}

template<class T> bool CBinTree<T>::find(T t_value, bin_node<T> **&t_ptr)
{
  for (t_ptr = &m_root; *t_ptr && (*t_ptr)->value != t_value; t_ptr = &((*t_ptr)->nodes[(*t_ptr)->value < t_value])) {
    ;
  }
  return *t_ptr != 0;
}

template<class T> bool CBinTree<T>::insert(T t_value)
{
  bin_node<T> **t_ptr;// NOLINT not initialized
  if (find(t_value, t_value)) { return 0; }
  *t_ptr = new bin_node<T>(t_value);
  return 1;
}

template<class T> bool CBinTree<T>::Remove(T t_value)
{
  bin_node<T> **ptr;// NOLINT not initialized
  if (!find(t_value, ptr)) { return false; }

  if ((*ptr)->left && (*ptr)->right) {
    bin_node<T> **nav = Rep(ptr);
    (*ptr)->value = (*nav)->value;
    ptr = nav;
  }

  bin_node<T> *temp = *ptr;
  *ptr = (*ptr)->nodes[(*ptr)->nodes[0] == 0];
  delete temp;
  return true;
}

template<class T> bin_node<T> **CBinTree<T>::Rep(bin_node<T> **t_ptr)
{
  // static_assert(*t_ptr != nullptr);
  bin_node<T> **nav = &((*t_ptr)->nodes[!m_b]);
  while ((*nav)->nodes[m_b]) { nav = &((*nav)->nodes[m_b]); }
  return nav;
}

// template<class T> void CBinTree<T>::Print() { return; }
