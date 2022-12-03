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
  using node_value_type = typename graph_type::node_value_type;

  explicit node(node_value_type t_v) : value{ t_v } {}

  list<edge_type *> edges;
  node_value_type value;
};

template<class graph_type> struct edge
{
  using node_type = typename graph_type::node_type;
  using edge_value_type = typename graph_type::edge_value_type;

  edge(node_type *t_a, node_type *t_b, edge_value_type t_e, bool t_d)
    : first_end{ t_a }, second_end{ t_b }, value{ t_e }, dir{ t_d }
  {
    first_end->edges.push_back(this);
    second_end->edges.push_back(this);
  }

  ~edge()
  {
    edge *edge_a;
    edge *edge_b;
    edge_a = RemoveEdgeFromNode(nodes[0], value);
    edge_b = RemoveEdgeFromNode(nodes[1], value);
    assert(edge_a == edge_b);
  }

  edge *RemoveEdgeFromNode(node_type *t_n, edge_value_type t_e)
  {
    for (auto i = t_n->edges.begin(); i != t_n->edges.end(); ++i) {
      if (i->value == t_e) {
        t_n->edges.erase(i);
        return *i;
      }
    }
    return 0;
  }

  // node_type *nodes[2];// NOLINT C-style array
  std::vector<node_type *> nodes{ nullptr, nullptr };// NOLINT C-style array
  node_type *&first_end = &nodes[0];
  node_type *&second_end = &nodes[1];
  edge_value_type value;
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


template<class t_node_value_type, class t_edge_value_type>
std::list<node<graph<t_node_value_type, t_edge_value_type>> *> secondary_call_dijkstra(
  node<graph<t_node_value_type, t_edge_value_type>> *t_begin,
  node<graph<t_node_value_type, t_edge_value_type>> *t_end,
  std::list<node<graph<t_node_value_type, t_edge_value_type>> *> t_path,
  t_edge_value_type &t_cont)
{
  using node_type = node<graph<t_node_value_type, t_edge_value_type>>;
  using edge_type = edge<graph<t_node_value_type, t_edge_value_type>>;


  std::list<node_type *> best_path_until_now = t_path;
  if (t_begin == t_end) { return best_path_until_now; }
  t_edge_value_type best_value_until_now = std::numeric_limits<t_edge_value_type>::max();

  // for (auto edge_it = t_begin->edges.begin(); edge_it != t_begin->edges.end(); edge_it++) {
  for (typename std::list<edge_type *>::iterator edge_it = t_begin->edges.begin(); edge_it != t_begin->edges.end();
       edge_it++) {
    bool repeated_node{ false };
    // for (auto path_node_ptr : t_path) {
    //   if (path_node_ptr == (*edge_it)->nodes[1]) { repeated_node = true; }// POSSIBLE
    // }S

    for (typename std::list<node_type *>::iterator it = t_path.begin(); it != t_path.end(); it++) {
      // cout << &(*it) << endl;
      // cout << &((*edge_it)) << endl;
      if (*it == (*edge_it)->nodes[1]) { repeated_node = true; }// POSSIBLE
    }

    // for (auto path_node_ptr : t_path) {
    //   if (path_node_ptr == (*edge_it)->second_end) { repeated_node = true; }// POSSIBLE
    // }
    if (repeated_node) { continue; }

    auto path_copy = t_path;
    auto cont_copy = t_cont;

    path_copy.push_back(t_begin);

    auto local_path = secondary_call_dijkstra((*edge_it)->second_end, t_end, path_copy, cont_copy);

    if (cont_copy < best_value_until_now) {
      best_value_until_now = cont_copy;
      best_path_until_now = local_path;
    }
  }


  t_cont += best_value_until_now;

  return best_path_until_now;
}


template<class t_node_value_type, class t_edge_value_type>
std::list<node<graph<t_node_value_type, t_edge_value_type>> *> dijkstra(
  node<graph<t_node_value_type, t_edge_value_type>> *t_begin,
  node<graph<t_node_value_type, t_edge_value_type>> *t_end,
  t_edge_value_type &t_weight)
{
  using node_type = node<graph<t_node_value_type, t_edge_value_type>>;
  // t_weight = 0;
  t_edge_value_type best_value_until_now = std::numeric_limits<t_edge_value_type>::max();

  std::vector<std::list<node_type *>> paths;
  std::vector<t_edge_value_type> counts(t_begin->edges.size(), 0);

  for (auto it = t_begin->edges.begin(); it != t_begin->edges.end(); it++) {

    std::list<node_type *> path{ (*it)->second_end };
    paths.push_back(path);
  }

  {
    size_t i = 0;
    for (auto it = t_begin->edges.begin(); it != t_begin->edges.end(); i++, it++) {
      paths[i] =
        secondary_call_dijkstra<t_node_value_type, t_edge_value_type>((*it)->second_end, t_end, paths[i], counts[i]);
    }// POSSIBLE
  }

  size_t best_path_index = 0;
  for (size_t i = 0; i < counts.size(); i++) {
    if (counts[i] < best_value_until_now) {
      best_value_until_now = counts[i];
      best_path_index = i;
    }
  }
  t_weight = best_value_until_now;
  return paths[best_path_index];
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

  graph<node_value_type, edge_value_type> g;
  std::vector<node_value_type> node_v{
    'a',// 0
    'b',// 1
    'c',// 2
    'd',// 3
    'e',// 4
    'f',// 5
    'g',// 6
    'h',// 7
    'i',// 8
  };
  // std::vector<node_value_type> node_v{  };
  // std::vector<edge_value_type> a_edge_input{ 3, 7, 2, 5, 8, 9, 10, 2, 14, 16, 4, 0 };// NOLINT magic number


  for (auto node_value : node_v) { g.InsertNode(node_value); }
  cout << g << endl;

  g.InsertEdge(g.nodes[0], g.nodes[1], 3);
  g.InsertEdge(g.nodes[0], g.nodes[2], 7);
  g.InsertEdge(g.nodes[0], g.nodes[3], 2);

  g.InsertEdge(g.nodes[1], g.nodes[4], 5);
  g.InsertEdge(g.nodes[1], g.nodes[5], 8);


  g.InsertEdge(g.nodes[4], g.nodes[7], 44);
  g.InsertEdge(g.nodes[5], g.nodes[2], 55);

  g.InsertEdge(g.nodes[2], g.nodes[3], 9);
  g.InsertEdge(g.nodes[2], g.nodes[7], 10);

  g.InsertEdge(g.nodes[6], g.nodes[7], 2);
  g.InsertEdge(g.nodes[6], g.nodes[8], 14);

  g.InsertEdge(g.nodes[7], g.nodes[8], 16);

  // dijkstra(g, g.nodes.begin(), g.nodes.back());
  edge_value_type weight{ 0 };

  using graph_type = graph<node_value_type, edge_value_type>::graph_type;
  // using node_type = graph<node_value_type, edge_value_type>::node_type;
  // using edge_type = graph<node_value_type, edge_value_type>::edge_type;

  std::list<node<node_value_type> *> best_path =//
    dijkstra<graph_type>(g.nodes.front(), g.nodes.back(), weight);

  // std::list<node<node_value_type> *> best_path =//
  //   dijkstra<node_type, edge_type>(g.nodes.front(), g.nodes.back(), weight);

  cout << g << endl;

  // std::list<node<graph<node_value_type, edge_value_type>> *> best_path =
  //   // dijkstra<node_value_type, edge_value_type>(g.nodes.front(), g.nodes.back(), weight);
  //   dijkstra<node_value_type, edge_value_type>(g.nodes.front(), g.nodes.back(), weight);

  for (auto *node : best_path) { cout << node << "-> " << endl; }
  for (auto node : best_path) { cout << node->value << "-> " << endl; }// POSSIBLE
}
