#include <iostream>

#include "graph/graph.hxx"
#include "graph/weighted_graph.hxx"

using std::cout;
using std::endl;

int main() {
  Graph g;
  g.AddEdge(0, 2);
  g.AddDiEdge(1, 2);
  auto adjacency_map = g.GetAdjacencyList(0);

  cout << "Adjacenty list for node 0:" << endl;
  for (auto &el : adjacency_map) {
    cout << el << endl;
  }

  cout << "g.IsLeaf(2)=" << g.IsLeaf(2) << endl;
  cout << "g.IsLeaf(1, 2)=" << g.IsLeaf(1, 2) << endl;

  auto result = g.DFS(0);
  cout << "DFS result for 0:" << endl;
  for (auto &el : result) {
    cout << el << endl;
  }

  result = g.BFS(0);
  cout << "BFS result for 0:" << endl;
  for (auto &el : result) {
    cout << el << endl;
  }

  cout << "g.Distance(0, 2)=" << g.Distance(0, 2) << endl;

  auto cyclic = g.IsCyclic();
  cout << "The graph is " << (cyclic ? "" : "not ") << "cyclic" << endl;

  auto cycles = g.GetCycles();
  cout << "The graph contains " << (*cycles.begin()).size() << " cycles"
       << endl;

  WeightedGraph wg;
  wg.AddEdge(1, 2, 5.5);
  wg.AddDiEdge(4, 2, 1.5);

  cout << "wg.Distance(1, 2)=" << wg.Distance(1, 2) << endl;

  return 0;
}
