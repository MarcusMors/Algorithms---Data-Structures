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
#include <string>
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

template<class graph_type>
string insert_edge(graph_type a_graph,
  node<graph_type> *a,
  node<graph_type> *b,
  typename graph_type::edge_value_type value,
  bool last_one = false)
{
  a_graph.insert_edge(a, b, value);
  if (last_one) {
    return string{ R"({"from":")" } + string{ a->value } + string{ R"(","to":")" }//
           + string{ b->value } + string{ "\"}]}" };
  }
  return string{ R"({"from":")" } + string{ a->value } + string{ R"(","to":")" }//
         + string{ b->value } + string{ R"("},)" };
}


int main()
{
  using node_value_type = char;
  using edge_value_type = int;
  using graph_type = graph<node_value_type, edge_value_type>::graph_type;
  using node_type = node<graph_type>;

  graph<node_value_type, edge_value_type> a_graph;
  std::vector<node_value_type> a_node_input{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' };

  string my_graph_json{ R"({"kind":{"graph":true},)" };
  string nodes_json{ R"("nodes":[)" };
  string edges_json{ R"("edges":[)" };
  // "\"edges\":[{\"from\":\"1\",\"to\":\"2\"}]}";

  // for (auto node_value : a_node_input) { a_graph.InsertNode(node_value); }
  for (size_t i = 0; i < a_node_input.size() - 1; i++) {
    auto node_value = a_node_input[i];
    a_graph.InsertNode(node_value);
    nodes_json += "{\"id\": \"" + string{ node_value } + "\"},";
  }
  {
    auto node_value = a_node_input.back();
    a_graph.InsertNode(node_value);
    nodes_json += "{\"id\": \"" + string{ node_value } + "\"}],";
  }


  node_type *&a = a_graph.nodes[0];
  node_type *&b = a_graph.nodes[1];
  node_type *&c = a_graph.nodes[2];
  node_type *&d = a_graph.nodes[3];
  node_type *&e = a_graph.nodes[4];
  node_type *&f = a_graph.nodes[5];
  node_type *&g = a_graph.nodes[6];
  node_type *&h = a_graph.nodes[7];
  node_type *&i = a_graph.nodes[8];
  node_type *&j = a_graph.nodes[9];
  node_type *&k = a_graph.nodes[10];

  cout << a_graph << endl;

  edges_json += insert_edge<graph_type>(a_graph, a, b, 3);
  edges_json += insert_edge<graph_type>(a_graph, a, c, 7);
  edges_json += insert_edge<graph_type>(a_graph, a, d, 2);

  edges_json += insert_edge<graph_type>(a_graph, b, e, 5);
  edges_json += insert_edge<graph_type>(a_graph, b, f, 8);


  edges_json += insert_edge<graph_type>(a_graph, e, h, 44);
  edges_json += insert_edge<graph_type>(a_graph, f, c, 55);

  edges_json += insert_edge<graph_type>(a_graph, c, d, 9);
  edges_json += insert_edge<graph_type>(a_graph, c, h, 10);

  edges_json += insert_edge<graph_type>(a_graph, g, h, 2);
  edges_json += insert_edge<graph_type>(a_graph, h, i, 15);
  edges_json += insert_edge<graph_type>(a_graph, g, i, 14);

  edges_json += insert_edge<graph_type>(a_graph, j, k, 30, true);

  my_graph_json += nodes_json + edges_json;

  edge_value_type weight{ 0 };
  // cout << a_graph << endl;

  std::vector<node_type *> best_path =//
    dijkstra<graph_type>(a_graph.nodes.front(), a_graph.nodes.back(), weight);

  // for (auto *node : best_path) { cout << node << "-> " << endl; }
  for (auto *node_in_path : best_path) { cout << node_in_path->value << "->"; }// POSSIBLE
  cout << weight << endl;

  // cout << my_graph_json << endl;

  return 0;
}
/*
USE THE FOLLOWING COMMAND IN THE DEBUG CONSOLE TO ALLOW GDB PRINT MORE THAN 200 CHARS
-exec set print elements 0
source: https://github.com/hediet/vscode-debug-visualizer/issues/53
 */
