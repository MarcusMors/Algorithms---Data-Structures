#ifndef __ARRAY_NODE_H__
#define __ARRAY_NODE_H__

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

template<class T> struct array_node
{
  // array_node(T v[3], array_node<T> n) : values[0]{}{}{}
  array_node() = default;
  array_node(array_node<T> &n) : next{ n } {}
  array_node<T> *next{ nullptr };
  T values[3];
};

#endif// __ARRAY_NODE_H__
