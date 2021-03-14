#include <boost/test/unit_test.hpp>
#include <list>

#include "graph/graph.hxx"

BOOST_AUTO_TEST_SUITE(DFSSimple)

BOOST_AUTO_TEST_CASE(dfs_simple) {
  Graph g;
  g.AddEdge(0, 1);
  BOOST_TEST(g.DFS(0) == (list<int>{0, 1}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DFSChains)

BOOST_AUTO_TEST_CASE(dfs_di_chain) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddEdge(1, 2);
  // NOTE: Extra parantheses needed for list initializer with several elements
  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 2}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 1}));
}

BOOST_AUTO_TEST_CASE(dfs_chain) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 0, 2}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 1, 0}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DFSVs)

BOOST_AUTO_TEST_CASE(dfs_di_v) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);
  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.DFS(1) == (list<int>{1}));
  BOOST_TEST(g.DFS(2) == (list<int>{2}));
}

BOOST_AUTO_TEST_CASE(dfs_v) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 0, 2}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 0, 1}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DFSAcyclic)

BOOST_AUTO_TEST_CASE(dfs_dag) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  g.AddDiEdge(1, 3);
  g.AddDiEdge(1, 4);

  g.AddDiEdge(2, 5);
  g.AddDiEdge(2, 6);
  g.AddDiEdge(2, 7);

  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 3, 4, 2, 5, 6, 7}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 3, 4}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 5, 6, 7}));
  BOOST_TEST(g.DFS(3) == (list<int>{3}));
  BOOST_TEST(g.DFS(4) == (list<int>{4}));
  BOOST_TEST(g.DFS(5) == (list<int>{5}));
  BOOST_TEST(g.DFS(6) == (list<int>{6}));
  BOOST_TEST(g.DFS(7) == (list<int>{7}));
}

BOOST_AUTO_TEST_CASE(dfs_ag) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  g.AddEdge(1, 3);
  g.AddEdge(1, 4);

  g.AddEdge(2, 5);
  g.AddEdge(2, 6);
  g.AddEdge(2, 7);

  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 3, 4, 2, 5, 6, 7}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 0, 2, 5, 6, 7, 3, 4}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 0, 1, 3, 4, 5, 6, 7}));
  BOOST_TEST(g.DFS(3) == (list<int>{3, 1, 0, 2, 5, 6, 7, 4}));
  BOOST_TEST(g.DFS(4) == (list<int>{4, 1, 0, 2, 5, 6, 7, 3}));
  BOOST_TEST(g.DFS(5) == (list<int>{5, 2, 0, 1, 3, 4, 6, 7}));
  BOOST_TEST(g.DFS(6) == (list<int>{6, 2, 0, 1, 3, 4, 5, 7}));
  BOOST_TEST(g.DFS(7) == (list<int>{7, 2, 0, 1, 3, 4, 5, 6}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DFSCyclic)

BOOST_AUTO_TEST_CASE(dfs_dcg) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(1, 2);
  g.AddDiEdge(2, 0);

  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 2, 0}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 0, 1}));
}

BOOST_AUTO_TEST_CASE(dfs_cg) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 0, 2}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 1, 0}));
}

BOOST_AUTO_TEST_CASE(dfs_cg_big) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  g.AddEdge(0, 3);
  g.AddEdge(3, 2);

  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 3);

  BOOST_TEST(g.DFS(0) == (list<int>{0, 1, 2, 3, 4, 5}));
  BOOST_TEST(g.DFS(1) == (list<int>{1, 0, 2, 3, 4, 5}));
  BOOST_TEST(g.DFS(2) == (list<int>{2, 1, 0, 3, 4, 5}));
  BOOST_TEST(g.DFS(3) == (list<int>{3, 0, 1, 2, 4, 5}));
  BOOST_TEST(g.DFS(4) == (list<int>{4, 3, 0, 1, 2, 5}));
  BOOST_TEST(g.DFS(5) == (list<int>{5, 4, 3, 0, 1, 2}));
}

BOOST_AUTO_TEST_SUITE_END()
