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

template<class T> struct f_node
{
  // cppcheck-suppress noExplicitConstructor ; allowing f_node A = {1} and A{1}
  f_node(T t_value) : value{ t_value } {}
  T value;
  f_node<T> *next{ nullptr };
};

template<class T> class forward_sort_list// NOLINT
{
public:
  forward_sort_list();
  ~forward_sort_list();
  bool Find(T val, f_node<T> **&ptr);
  bool Ins(T val);
  bool Rem(T val);
  void Print();

private:
  f_node<T> *head{ nullptr };
};

template<class T> forward_sort_list<T>::~forward_sort_list()
{
  for (f_node<T> *it = head; it;) {
    head = head->next;
    delete it;// NOLINT
    it = head;
  }
}

template<class T> bool forward_sort_list<T>::Find(T val, f_node<T> **&ptr)
{
  for (ptr = &head; *ptr && val > (*ptr)->value; ptr = &((*ptr)->next)) { ; }
  return *ptr && (*ptr)->value == val;
}

/*
 ptr = &head;
 while( *ptr && val > (*ptr)->value )
 {
     ptr = &((*ptr)->next);
 }

 */

template<class T> bool forward_sort_list<T>::Ins(T val)
{
  f_node<T> **ptr;// NOLINT initialization
  if (Find(val, ptr)) { return false; }
  f_node<T> *n = new f_node<T>(val);// NOLINT
  n->next = *ptr;
  *ptr = n;
  return true;
}

template<class T> bool forward_sort_list<T>::Rem(T val)
{
  f_node<T> **p;
  if (!Find(val, p)) return 0;
  f_node<T> *t = *p;
  *p = t->next;
  delete t;
  return 1;
}

template<class T> void forward_sort_list<T>::Print()
{
  for (f_node<T> *t = head; t != 0; t = t->next) std::cout << t->value << " ";
  std::cout << "\n";
}

int main()
{
  forward_sort_list<int> l;
  l.Ins(9);
  l.Ins(11);
  l.Ins(15);
  l.Ins(3);
  l.Ins(7);
  l.Ins(1);
  l.Ins(18);

  l.Print();

  l.Rem(7);
  l.Print();
  l.Rem(1);
  l.Print();
  l.Rem(18);
  l.Print();
}
