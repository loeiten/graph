#include <graph/graph.hxx>

void Graph::AddEdge(int from_node, int to_node) {
  (*adjacency_list)[from_node].push_back(to_node);
}

const list<int> Graph::GetAdjacencyList(int node) const {
  return (*adjacency_list)[node];
}
