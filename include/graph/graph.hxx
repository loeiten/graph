#ifndef INCLUDE_GRAPH_GRAPH_HXX_
#define INCLUDE_GRAPH_GRAPH_HXX_

#include <list>
#include <map>
#include <memory>

using std::list;
using std::make_shared;
using std::map;
using std::shared_ptr;

class Graph {
 public:
  // NOTE: We need to initialize the shared pointer in order not to get segfault
  Graph() : adjacency_list(make_shared<map<int, list<int>>>()) {}
  void AddEdge(int, int);
  const list<int> GetAdjacencyList(int) const;
  // void DFS(int from);
 private:
  shared_ptr<map<int, list<int>>> adjacency_list;
};

#endif  // INCLUDE_GRAPH_GRAPH_HXX_
