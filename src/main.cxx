#include <iostream>

#include "graph/graph.hxx"

using std::cout;
using std::endl;

#include <memory>

using std::list;
using std::make_shared;
using std::map;
using std::shared_ptr;

int main() {
  Graph g;
  g.AddEdge(0, 2);
  auto adjacency_map = g.GetAdjacencyList(0);

  cout << "Adjacenty list for node 0:" << endl;
  for (auto &el : adjacency_map) {
    cout << el << endl;
  }

  auto result = g.DFS(0);
  cout << "DFS result for 0:" << endl;
  for (auto &el : result) {
    cout << el << endl;
  }

  return 0;
}
