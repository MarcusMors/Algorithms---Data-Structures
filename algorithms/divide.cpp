// Copyright (t_c) 2022 José Enrique Vilca Campana
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

template<typename T> struct node
{
  T value;
  node<T> *next{ nullptr };
  explicit node(T v) : value{ v } {}
  explicit node(T v, node<T> *n) : value{ v }, next{ n } {}
};

void ArrToLE(char *t_c, node<char> *&t_list)
{
  node<char> *tmp = nullptr;
  for (; *t_c; t_c++) {
    if (!tmp) {
      t_list = new node<char>(*t_c);
      tmp = t_list;
    } else {
      tmp->next = new node<char>(*t_c);
      tmp = tmp->next;
    }
  }
}

struct is_number
{
  bool operator()(char t_c)
  {
    if (t_c >= 48 && t_c <= 57) return true;
    return false;
  }
};

struct is_letter
{
  bool operator()(char t_c)
  {
    if (t_c >= 65 && t_c <= 90) return true;
    return false;
  }
};

void print(node<char> *t_list)
{
  cout << "t_list->";
  for (; t_list; t_list = t_list->next) cout << t_list->value << "->";
  cout << "nullptr" << endl << endl;
}

template<typename T> void split(node<char> *&L_Origen, node<char> *&L_Filtro, T Filtro)
{
  // TO DO
}

int main()
{
  char ArrC[30] = "C13NC14#D3#L4#C0MPUT4C10N";
  node<char> *LeChar1, *LeChar2;
  node<char> *LeFiltro1 = nullptr, *LeFiltro2 = nullptr;

  ArrToLE(ArrC, LeChar1);
  cout << "Cadena 1" << endl;
  print(LeChar1);
  split(LeChar1, LeFiltro1, is_number());
  cout << "Cadena 1 - Split" << endl;
  print(LeChar1);
  cout << "Filtro 1 - Split" << endl;
  print(LeFiltro1);

  ArrToLE(ArrC, LeChar2);
  cout << "Cadena 2" << endl;
  print(LeChar2);
  split(LeChar2, LeFiltro2, is_letter());
  cout << "Cadena 2 - Split" << endl;
  print(LeChar2);
  cout << "Filtro 2 - Split" << endl;
  print(LeFiltro2);


  return 0;
}
