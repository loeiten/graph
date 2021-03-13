#include "graph/graph.hxx"

#include <vector>

using std::vector;

void Graph::AddEdge(int from_node, int to_node) {
  adjacency_map[from_node].push_back(to_node);
  adjacency_map[to_node].push_back(from_node);
}

void Graph::AddDiEdge(int from_node, int to_node) {
  adjacency_map[from_node].push_back(to_node);
}

const list<int> Graph::GetAdjacencyList(int node) const {
  // NOTE: The operator[] on std::map is marked as non-const, and cannot be used
  // in a const, hence we use .at()
  return adjacency_map.at(node);
}

list<int> Graph::DFS(int from) {
  // NOTE: The following must only be declared once
  map<int, bool> visited_map;
  for (auto& cur_pair : adjacency_map) {
    visited_map[cur_pair.first] = false;
  }
  map<int, bool>* visited_map_ptr = &visited_map;

  // NOTE: We add the starting node
  list<int> result{from};
  list<int>* result_ptr = &result;

  DFSRecurser(from, visited_map_ptr, result_ptr);

  return result;
}

void Graph::DFSRecurser(int node, map<int, bool>* visited_map_ptr,
                        list<int>* result_ptr) {
  // The node is now visited
  (*visited_map_ptr)[node] = true;

  // Loop through all the adjacent nodes of the current node
  for (const auto& neighbour_node : adjacency_map[node]) {
    // Check if the neighbour_node exists in the visited_map
    if (!(*visited_map_ptr)[neighbour_node]) {
      // If it is not visited, visit it

      result_ptr->push_back(neighbour_node);
      DFSRecurser(neighbour_node, visited_map_ptr, result_ptr);
    }
  }
}
