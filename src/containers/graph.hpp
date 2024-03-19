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

#include <list>


template<class graph_type> struct node
{
  using edge_type = typename graph_type::edge_type;
  using value_type = typename graph_type::node_value_type;

  explicit node(value_type t_v) : value{ t_v } {}

  std::list<edge_type *> edges;
  value_type value;
};

template<class graph_type> struct edge
{
  using node_type = typename graph_type::node_type;
  using value_type = typename graph_type::edge_value_type;

  // edge(node_type *t_a, node_type *t_b, value_type t_e, bool t_d) : value{ t_e }, dir{ t_d }
  edge(node_type *t_a, node_type *t_b, value_type t_e, bool t_d)
  {
    nodes[0] = t_a;
    nodes[1] = t_b;
    value = t_e;
    dir = t_d;
    nodes[0]->edges.push_back(this);
    nodes[1]->edges.push_back(this);
  }

  ~edge()
  {
    edge *edge_a;
    edge *edge_b;
    edge_a = RemoveEdgeFromNode(nodes[0], value);
    edge_b = RemoveEdgeFromNode(nodes[1], value);
    assert(edge_a == edge_b);
  }

  edge *RemoveEdgeFromNode(node_type *t_n, value_type t_e)
  {
    for (auto i = t_n->edges.begin(); i != t_n->edges.end(); ++i) {
      if (i->value == t_e) {
        t_n->edges.erase(i);
        return *i;
      }
    }
    return 0;
  }

  node_type *nodes[2]{ nullptr, nullptr };// NOLINT C-style array
  // std::vector<node_type *> nodes{ nullptr, nullptr };// NOLINT C-style array
  // node_type *&first_end = &nodes[0];
  // node_type *&second_end = &nodes[1];
  value_type value{};
  bool dir;// 0=bidireccional, 1 = nodes[0]=>nodes[1]
};

template<class t_node_value_type, class t_edge_value_type> class graph
{
public:
  using node_value_type = t_node_value_type;
  using edge_value_type = t_edge_value_type;
  using graph_type = graph<node_value_type, edge_value_type>;
  using node_type = node<graph_type>;
  using edge_type = edge<graph_type>;

  bool InsertNode(node_value_type t_n)
  {
    nodes.push_back(new node_type(t_n));
    return true;
  }

  bool insert_edge(node_type *t_a, node_type *t_b, edge_value_type t_e, bool t_direction = false)
  {
    new edge_type(t_a, t_b, t_e, t_direction);
    return true;
  }

  enum direction : bool {
    first_to_second,
    second_to_first,
  };

  // bool RemoveEdge(node_type *a, node_type *b, edge_value_type e) {}

  // bool RemoveNode(node_type *n)// node_value_type _n;
  // {}

  // private:
  vector<node_type *> nodes;
};
