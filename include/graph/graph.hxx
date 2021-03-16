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

/**
 * Class contiaining the graph
 */
class Graph {
 public:
  /**
   * Default constructor
   */
  Graph() {}

  /**
   * Connect two nodes in the graph in an undirected way
   *
   * \param from_node The node to create the edge from
   * \param to_node The node to create the edge to
   */
  void AddEdge(int from_node, int to_node);

  /**
   * Connect two nodes in the graph in a directed way
   *
   * \param from_node The node to create the edge from
   * \param to_node The node to create the edge to
   */
  void AddDiEdge(int from_node, int to_node);

  /**
   * Return the adjacency list of a node
   *
   * \param node Node to get the adjacancy list from
   * \return A list of int containing the connections from the node
   */
  const list<int> GetAdjacencyList(int node) const;

  /**
   * Check if a node is a leaf node
   *
   * Here a leaf node is a node with connection to other nodes
   *
   * \see IsLeaf(int cur_node, int prev_node) for non-directed leaf nodes
   *
   * \param node Node to check
   * \return true if the node is a leaf node
   */
  bool IsLeaf(int node) const;

  /**
   * Check if a node is a leaf node
   *
   * Here there are two ways a node can be a leaf node
   * 1. The node has no adjacent nodes (happens if the node is
   *    connected with a directed edge)
   * 2. The node has one adjacent node, and this node is the
   *    node just visited
   *
   * \param cur_node Node to check
   * \param prev_node Node just visited
   * \return true if the node is a leaf node
   */
  bool IsLeaf(int cur_node, int prev_node) const;

  /**
   * Do a depth first search
   *
   * \param from Node to start the search from
   * \return A list of int containing the result of the search
   */
  list<int> DFS(int from) const;

  /**
   * Do a breadth first search
   *
   * \param from Node to start the search from
   * \return A list of int containing the result of the search
   */
  list<int> BFS(int from) const;

  /**
   * Find shortest path in unweighted graph
   *
   * Returns -1 if node is not found
   *
   * \param from Node to start the search from
   * \param to Node to end the search at
   * \return The distance between the input
   */
  int Distance(int from, int to) const;

  /**
   * Checks if a graph is cyclic
   *
   * \return true if the graph contains at least one cycle
   */
  bool IsCyclic() const;

  /**
   * Get a trace of all the cycles in the graph
   *
   * \return A set containing all the sets of ints containing a traced cycle
   */
  set<set<int>> GetCycles() const;

 protected:
  map<int, list<int>>
      adjacency_map; /**< The map of the connectivity of all the nodes */

 private:
  /**
   * The recurser used for DFS
   *
   * \param node The node to recurse from
   * \param[out] visited_map_ptr Pointer to the map where the keys are nodes and
   *             values boolean indicated visited
   * \param[out] result_ptr Pointer to the result being returned from DFS
   */
  void DFSRecurser(int node, map<int, bool>* visited_map_ptr,
                   list<int>* result_ptr) const;

  /**
   * The recurser used for IsCyclic
   *
   * \param node The node to recurse from
   * \param prev_node The node just visited (we do not call a undirected edge a
   *                  cycle)
   * \param[out] visited_map_ptr Pointer to the map where the keys are
   *                             nodes and values boolean indicated visited
   * \param[out] cyclic_ptr Pointer to the boolean indicating cyclic graph
   */
  void CyclicRecurser(int node, int prev_node, map<int, bool>* visited_map_ptr,
                      bool* cyclic_ptr) const;

  /**
   * The recurser used for GetCycles
   *
   * \param node The node to recurse from
   * \param prev_node The node just visited (we do not call a undirected edge a
   *                  cycle)
   * \param[out] visited_map_ptr Pointer to the map where the keys are
   *                             nodes and values boolean indicated visited
   * \param[out] cyclic_start_ptr Pointer to a set of nodes one can use to trace
   *                              the cycle
   */
  void GetCyclcesRecurser(int node, int prev_node,
                          map<int, bool>* visited_map_ptr,
                          set<int>* cycle_start_ptr) const;

  /**
   * The tracer for GetCycles
   *
   * \param node The node to recurse from
   * \param prev_node The node just visited (we do not call a undirected edge a
   *                  cycle)
   * \param[out] visited_ptr Pointer to a deque of visited nodes
   * \param[out] A set containing all the sets of ints containing a traced cycle
   */
  void TraceCycle(int node, int prev_node, deque<int>* visited_ptr,
                  set<set<int>>* cycles_ptr) const;
};

#endif  // INCLUDE_GRAPH_GRAPH_HXX_
