#ifndef INCLUDE_GRAPH_GRAPH_HXX_
#define INCLUDE_GRAPH_GRAPH_HXX_

#include <deque>
#include <list>
#include <map>
#include <set>

using std::deque;
using std::list;
using std::map;
using std::set;

class Graph {
 public:
  // NOTE: We need to initialize the shared pointer in order not to get segfault
  Graph() {}
  void AddEdge(int, int);
  void AddDiEdge(int, int);
  const list<int> GetAdjacencyList(int) const;
  list<int> DFS(int);
  bool IsCyclic();
  set<set<int>> GetCycles();

 private:
  map<int, list<int>> adjacency_map;
  void DFSRecurser(int, map<int, bool>*, list<int>*);
  void CyclicRecurser(int, int, map<int, bool>*, bool*);
  void GetCyclcesRecurser(int, int, map<int, bool>*, set<int>*);
  void TraceCycle(int, int, deque<int>*, set<set<int>>*);
};

#endif  // INCLUDE_GRAPH_GRAPH_HXX_
