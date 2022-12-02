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


#include "node/bin_node.hpp"
#include <iostream>

namespace fstd {
using std::cout;

template<class T> class bin_search_tree
{
private:
  using init_it_type = typename std::initializer_list<T>::iterator;

public:
  using value_type = T;
  using node_type = bin_node<T>;

  bool empty() { return root != nullptr; }

  node_type *constructor(init_it_type t_begin, init_it_type t_end);
  bin_search_tree(std::initializer_list<T> init) : root{ constructor(init.begin(), init.end()) } {}

  void destructor(node_type *t_node);
  ~bin_search_tree() { destructor(root); }

  bool insert(int x);
  bool remove(int x);

  template<class Functor = bool(node_type *), class Do_mid = void(node_type *)>
  void in_level_traversal(
    Functor t_funct = [](node_type *node_parameter) { return node_parameter != nullptr; },
    Do_mid do_mid = [](node_type *node_mid) { cout << node_mid->value << ", "; })
  {
    in_level_traversal(root, t_funct, do_mid);
  }

  template<class Functor = bool(node_type *), class Do_mid = void(node_type *)>
  void in_order_traversal(
    node_type *t_start,
    Functor t_funct = [](node_type *node_parameter) { return node_parameter != nullptr; },
    Do_mid do_mid = [](node_type *node_mid) { cout << node_mid->value << ", "; })
  {
    if (t_funct(t_start->nodes[0])) { in_order_traversal(t_start->nodes[0], t_funct, do_mid); }
    do_mid(t_start);
    if (t_funct(t_start->nodes[1])) { in_order_traversal(t_start->nodes[1], t_funct, do_mid); }
  }

  template<class Functor = bool(node_type *), class Do_mid = void(node_type *)>
  void in_order_traversal(
    Functor t_funct = [](node_type *node_parameter) { return node_parameter != nullptr; },
    Do_mid do_mid = [](node_type *node_mid) { cout << node_mid->value << ", "; })
  {
    in_order_traversal(root, t_funct, do_mid);
  }

  void Print();

private:
  node_type *root{};
  bool find(int x, node_type **&p);
  node_type **Rep(node_type **p);
  void InOrder(node_type *x);
  bool brep{};
};

}// namespace fstd

// template<class T> std::ostream &operator<<(std::ostream &) { in_order_traversal(); }

template<class T> void fstd::bin_search_tree<T>::destructor(node_type *t_node)
{
  if (t_node == nullptr) { return; }
  destructor(t_node->nodes[0]);
  destructor(t_node->nodes[1]);
  delete t_node;
}

template<class T>
typename fstd::bin_search_tree<T>::node_type *fstd::bin_search_tree<T>::constructor(init_it_type t_begin,
  init_it_type t_end)
{
  if (t_end <= t_begin) { return nullptr; }
  auto mid_ptr = t_begin + (t_end - t_begin) / 2;
  auto *new_ptr = new node_type(*mid_ptr);
  new_ptr->nodes[0] = constructor(t_begin, mid_ptr);
  new_ptr->nodes[1] = constructor(mid_ptr + 1, t_end);
  return new_ptr;
}

template<class T> bool fstd::bin_search_tree<T>::find(int x, node_type **&p)
{
  for (p = &root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x])) { ; }
  return *p != 0;
}

template<class T> bool fstd::bin_search_tree<T>::insert(int x)
{
  node_type **p{};
  if (find(x, p)) { return false; }
  *p = new node_type(x);
  return true;
}

template<class T> bool fstd::bin_search_tree<T>::remove(int x)
{
  node_type **p{};
  if (!find(x, p)) { return false; }

  if ((*p)->nodes[0] && (*p)->nodes[1])// case 2
  {
    node_type **q = Rep(p);
    (*p)->value = (*q)->value;
    p = q;
  }
  // case 0 or case 1
  node_type *t = *p;
  *p = (*p)->nodes[(*p)->nodes[1] != 0];
  delete t;
  return true;
}

template<class T> fstd::bin_node<T> **fstd::bin_search_tree<T>::Rep(node_type **p)
{
  node_type **q = p;
  for (q = &((*q)->nodes[!brep]); *q; q = &((*q)->nodes[brep])) { ; }
  brep = !brep;
  return q;
}
