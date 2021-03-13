#include <iostream>

#include "graph/graph.hxx"

using std::cout;
using std::endl;

int main() {
  Graph g;
  g.AddEdge(0, 2);
  auto adjacency_list = g.GetAdjacencyList(0);

  cout << "Adjacenty list for node 0:" << endl;
  for (auto &el : adjacency_list) {
    cout << el << endl;
  }

  return 0;
}
