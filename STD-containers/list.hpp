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

#include <initializer_list>
#include <iostream>

using namespace std;

namespace fstd {
template<typename T> struct node
{
  using iterator = node<T> *;
  T value;
  iterator prev{ nullptr };
  iterator next{ nullptr };
  node() {}
  node(const T v) : value{ v } {}
  node(const T v, iterator *n, iterator *p) : value{ v }, next{ n }, prev{ p } {}
  node(const iterator &n) : next{ n->next }, prev{ n->prev }, value{ n->value } {}
  // void operator=(node<T> t_n)
  // {
  // 	next = t_n.next;
  // 	value = t_n.value;
  // }
};

template<typename T> struct list
{
  using size_type = std::size_t;
  using iterator = node<T> *;
  using const_iterator = const node<T> *;

  list(std::initializer_list<T> init) : sz{ init.size() }
  {
    head = new node<T>(*init.begin());
    iterator nav = head;
    for (auto i = init.begin() + 1; i != init.end(); ++i) {
      nav->next = new node<T>(*i);
      nav->next->prev = nav;
      nav = nav->next;
    }
    tail = nav;
  }
  ~list()
  {
    iterator current_n{ begin() };// initialize current node to root
    while (current_n) {
      iterator next_n{ current_n->next };// get next node
      delete current_n;// delete current
      current_n = next_n;// set current to "old" next
    }
  }
  void push_back(T t_value)
  {
    auto temp = new node<T>(t_value);
    if (sz == 0)// empty list
      head = tail = temp;
    temp.prev = tail;
    tail = temp;
    tail->next = temp;
    ++sz;
  }
  size_type size() { return sz; }

  iterator begin() { return head; }
  iterator begin() const { return head; }
  iterator end() { return tail; }
  iterator end() const { return tail; }

  const_iterator cbegin() const { return head; }
  const_iterator cend() const { return tail; }

  T &operator[](size_type t_i)
  {
    iterator nav{ head };
    for (size_type i = 0; i < t_i; ++i) nav = nav->next;
    return nav->value;
  }

private:
  iterator h{ nullptr };
  iterator &head = h;
  iterator t{ nullptr };
  iterator &tail = t;
  size_type sz{ 0 };
};

template<typename T> ostream &operator<<(std::ostream &os, const list<T> &t_list)
{
  for (node<T> *i = t_list.begin(); i != t_list.end(); i = i->next) { os << i->value << ", "; }
  return os;
}
template<typename T> ostream &operator<<(std::ostream &os, const node<T> &t_node) { return os << t_node.value; }
template<typename T> ostream &operator<<(std::ostream &os, const node<T> *t_node) { return os << t_node->value; }
}// namespace fstd
