#ifndef INCLUDE_GRAPH_GRAPH_HXX_
#define INCLUDE_GRAPH_GRAPH_HXX_

#include <list>
#include <map>
#include <vector>

using std::list;
using std::map;
using std::vector;

class Graph {
 public:
  // NOTE: We need to initialize the shared pointer in order not to get segfault
  Graph() {}
  void AddEdge(int, int);
  void AddDiEdge(int, int);
  const list<int> GetAdjacencyList(int) const;
  list<int> DFS(int);

 private:
  map<int, list<int>> adjacency_map;
  void DFSRecurser(int, map<int, bool>*, list<int>*);
};

#endif  // INCLUDE_GRAPH_GRAPH_HXX_
