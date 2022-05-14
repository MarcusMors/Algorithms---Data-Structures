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
#include <vector>
using namespace std;

struct bin_node
{
  bin_node(int t_value) : value{ t_value } {}
  int value{};
  bin_node *nodes[2]{ nullptr, nullptr };// NOLINT C-style array
  bin_node *&left = nodes[0];
  bin_node *&right = nodes[1];
};

class bin_tree
{
public:
  bin_tree() : m_root{ nullptr }, m_b{ true } {}
  ~bin_tree();
  bool insert(int t_value);
  bool remove(int t_value);
  bin_node *begin() { return m_root; }
  bin_node *begin() const { return m_root; }

private:
  bool find(int t_value, bin_node **&t_ptr);
  bin_node **replace(bin_node **t_ptr) const;
  void InOrder(bin_node *n);
  bin_node *m_root{ nullptr };
  bool m_b{ true };
};

bin_tree::~bin_tree()
{
  // ?
}

bool bin_tree::find(int t_value, bin_node **&t_ptr)
{
  auto advance_to_next_ptr = [&](const bool &branch) { t_ptr = &((*t_ptr)->nodes[branch]); };

  t_ptr = &m_root;
  for (bool branch; *t_ptr && (*t_ptr)->value != t_value;// NOLINT initialized branch, implicit conversion
       advance_to_next_ptr(branch)) {
    branch = (*t_ptr)->value < t_value;// 0 left, 1 right
  }
  return *t_ptr != nullptr;
}

bool bin_tree::insert(int t_value)
{
  bin_node **t_ptr;// NOLINT initialized
  if (find(t_value, t_ptr)) { return false; }
  *t_ptr = new bin_node(t_value);// NOLINT create new node
  return true;
}

bool bin_tree::remove(int t_value)
{
  bin_node **t_ptr;// NOLINT initialized
  if (!find(t_value, t_ptr)) { return false; }

  // transform case 2
  if ((*t_ptr)->left && (*t_ptr)->right) {// NOLINT implicit conversion

    // search a replacement
    bin_node **replace_ptr = replace(t_ptr);
    // put replace_ptr value to t_ptr
    (*t_ptr)->value = (*replace_ptr)->value;
    t_ptr = replace_ptr;
    // now, it's case 1,0
  }

  // case 0,1
  bin_node *tree = *t_ptr;
  *t_ptr = (*t_ptr)->nodes[(*t_ptr)->nodes[0] == nullptr];
  delete tree;
  return true;
}

bin_node **bin_tree::replace(bin_node **t_ptr) const
{
  // most right leaf in the left
  // most left leaf in the rightt
  // the path is determined by !m_b : false
  // m_b : true
  // assert(*t_ptr != nullptr);
  bin_node **nav = &((*t_ptr)->nodes[!m_b]);// NOLINT not integer for array subscript
  while ((*nav)->nodes[m_b]) nav = &((*nav)->nodes[m_b]);// NOLINT not integer for subscript
  return nav;
}

// void bin_tree::InOrder(bin_node *n) { return; }

ostream &operator<<(std::ostream &os, const bin_node *rhs)// NOLINT
{
  if (rhs->left) { os << rhs->left; }// NOLINT implicit conversion
  os << rhs->value << ", ";// print this leave
  if (rhs->right) { os << rhs->right; }// NOLINT implicit conversion
  return os;
}
ostream &operator<<(std::ostream &os, const bin_tree &rhs)// NOLINT
{
  os << rhs.begin();
  return os;
}

int main()
{
  bin_tree tree;

  std::vector<int> insert_array{ 50, 30, 60, 80, 55, 11, 33, 5, 14, 31, 48 };// NOLINT magic number
  // std::vector<int> insert_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };// NOLINT magic number

  for (auto &&num : insert_array) { tree.insert(num); }
  cout << tree << "\n";

  // works
  // cout << "removing\n";
  // tree.remove(1);
  // cout << tree << "\n";
  // tree.remove(14);
  // cout << tree << "\n";
  // tree.remove(11);
  // cout << tree << "\n";
  // tree.remove(15);
  // cout << tree << "\n";
  // tree.remove(7);
  // cout << tree << "\n";

  // remove a non-existant node

  tree.remove(20);
  cout << tree << "\n";
  tree.remove(48);
  cout << tree << "\n";
  tree.remove(55);
  cout << tree << "\n";
  tree.remove(5);
  cout << tree << "\n";
  tree.remove(80);
  cout << tree << "\n";
  tree.remove(30);
  cout << tree << "\n";
  return 0;
}
