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
#include <limits>
#include <list>
#include <set>
#include <vector>

using namespace std;

template<class graph_type> struct node
{
  using edge_type = typename graph_type::edge_type;
  using value_type = typename graph_type::node_value_type;

  explicit node(value_type t_v) : value{ t_v } {}

  list<edge_type *> edges;
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

  bool InsertEdge(node_type *t_a, node_type *t_b, edge_value_type t_e, bool t_direction = false)
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


template<class graph_type>
std::vector<node<graph_type> *> secondary_dijkstra(node<graph_type> *t_begin,
  node<graph_type> *t_end,
  std::vector<node<graph_type> *> t_path,
  typename edge<graph_type>::value_type &t_cont)
{
  using node_type = node<graph_type>;
  using edge_type = edge<graph_type>;
  using edge_value_type = typename edge<graph_type>::value_type;


  // if (t_begin->value == 'h') { cout << "\n am the one before the last" << endl; }

  std::vector<node_type *> best_path_until_now = t_path;
  edge_value_type best_value_until_now{ std::numeric_limits<edge_value_type>::max() };

  for (typename std::list<edge_type *>::iterator edges_it = t_begin->edges.begin(); edges_it != t_begin->edges.end();
       ++edges_it) {

    node_type *the_node_different_to_begin =
      (*edges_it)->nodes[0] != t_begin ? (*edges_it)->nodes[0] : (*edges_it)->nodes[1];


    if (the_node_different_to_begin == t_end) {
      vector<node_type *> path{ t_path };
      path.push_back(the_node_different_to_begin);
      t_cont += (*edges_it)->value;
      return path;
    }

    const auto is_a_repeated_node_in_the_path = [&]() -> bool {
      for (auto *node_in_path : t_path) {// NOLINT
        if (node_in_path == the_node_different_to_begin) { return true; }
      }
      return false;
    };


    if (is_a_repeated_node_in_the_path()) { continue; }

    vector<node_type *> path{ t_path };
    path.push_back(the_node_different_to_begin);
    edge_value_type path_value{ t_cont + (*edges_it)->value };

    path = secondary_dijkstra(the_node_different_to_begin, t_end, path, path_value);

    if (path_value < best_value_until_now) {
      best_value_until_now = path_value;
      best_path_until_now = path;
    }
  }
  t_cont = best_value_until_now;
  return best_path_until_now;
}


template<class graph_type>
std::vector<node<graph_type> *>
  dijkstra(node<graph_type> *t_begin, node<graph_type> *t_end, typename edge<graph_type>::value_type &t_weight)// NOLINT
{
  using node_type = node<graph_type>;
  using edge_value_type = typename edge<graph_type>::value_type;

  if (t_begin == t_end) {
    t_weight = 0;
    return std::vector<node_type *>{ t_begin };
  }


  edge_value_type best_value_until_now{ std::numeric_limits<edge_value_type>::max() };
  vector<node_type *> best_path_until_now;

  for (auto it = t_begin->edges.begin(); it != t_begin->edges.end(); ++it) {
    node_type *the_node_different_to_begin = (*it)->nodes[0] != t_begin ? (*it)->nodes[0] : (*it)->nodes[1];

    vector<node_type *> path{ t_begin, the_node_different_to_begin };
    if (the_node_different_to_begin == t_end) {
      t_weight = (*it)->value;
      return path;
    }

    edge_value_type path_value{ (*it)->value };

    path = secondary_dijkstra(the_node_different_to_begin, t_end, path, path_value);

    if (path_value < best_value_until_now) {
      best_value_until_now = path_value;
      best_path_until_now = path;
    }
  }

  t_weight = best_value_until_now;
  return best_path_until_now;
}


template<class node_value_type, class edge_value_type>
std::ostream &operator<<(std::ostream &os, graph<node_value_type, edge_value_type> t_graph)// NOLINT
{
  for (auto node : t_graph.nodes) {
    os << "N->" << node->value << "|";
    for (auto edge : node->edges) { os << "->" << edge->value; }
    os << "\n";
  }
  return os;
}


int main()
{
  using node_value_type = char;
  using edge_value_type = int;
  using graph_type = graph<node_value_type, edge_value_type>::graph_type;
  using node_type = node<graph_type>;

  graph<node_value_type, edge_value_type> a_graph;
  std::vector<node_value_type> a_node_input{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
  std::vector<edge_value_type> a_edge_input{ 3, 7, 2, 5, 8, 9, 10, 2, 14, 16, 4, 0 };// NOLINT magic number

  // simple case
  // a_graph.InsertEdge(a, b, 3);
  // a_graph.InsertEdge(a, c, 7);
  // a_graph.InsertEdge(a, d, 2);

  for (auto node_value : a_node_input) { a_graph.InsertNode(node_value); }

  node_type *&a = a_graph.nodes[0];// NOLINT
  node_type *&b = a_graph.nodes[1];// NOLINT
  node_type *&c = a_graph.nodes[2];// NOLINT
  node_type *&d = a_graph.nodes[3];// NOLINT
  node_type *&e = a_graph.nodes[4];// NOLINT
  node_type *&f = a_graph.nodes[5];// NOLINT
  node_type *&g = a_graph.nodes[6];// NOLINT
  node_type *&h = a_graph.nodes[7];// NOLINT
  node_type *&i = a_graph.nodes[8];// NOLINT

  cout << a_graph << endl;

  a_graph.InsertEdge(a, b, 3);
  a_graph.InsertEdge(a, c, 7);
  a_graph.InsertEdge(a, d, 2);

  a_graph.InsertEdge(b, e, 5);
  a_graph.InsertEdge(b, f, 8);


  a_graph.InsertEdge(e, h, 44);
  a_graph.InsertEdge(f, c, 55);

  a_graph.InsertEdge(c, d, 9);
  a_graph.InsertEdge(c, h, 10);

  a_graph.InsertEdge(g, h, 2);
  a_graph.InsertEdge(h, i, 15);
  a_graph.InsertEdge(g, i, 14);


  edge_value_type weight{ 0 };
  cout << a_graph << endl;

  std::vector<node_type *> best_path =
    // dijkstra<node_value_type, edge_value_type>(a_graph.nodes.front(), a_graph.nodes.back(), weight);
    dijkstra<graph_type>(a_graph.nodes.front(), a_graph.nodes.back(), weight);

  // for (auto *node : best_path) { cout << node << "-> " << endl; }
  for (auto *node_in_path : best_path) { cout << node_in_path->value << "->"; }// POSSIBLE
  cout << weight << endl;

  return 0;
}

// podar
// count triangles in a graph
// foldable but checking the value.
