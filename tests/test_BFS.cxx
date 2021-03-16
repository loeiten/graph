#include <boost/test/unit_test.hpp>
#include <list>

#include "graph/graph.hxx"

using std::list;

BOOST_AUTO_TEST_SUITE(BFSSimple)

BOOST_AUTO_TEST_CASE(bfs_simple) {
  Graph g;
  g.AddEdge(0, 1);
  BOOST_TEST(g.BFS(0) == (list<int>{0, 1}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(BFSChains)

BOOST_AUTO_TEST_CASE(bfs_di_chain) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddEdge(1, 2);
  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 2}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 1}));
}

BOOST_AUTO_TEST_CASE(bfs_chain) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 0, 2}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 1, 0}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(BFSVs)

BOOST_AUTO_TEST_CASE(bfs_di_v) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);
  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.BFS(1) == (list<int>{1}));
  BOOST_TEST(g.BFS(2) == (list<int>{2}));
}

BOOST_AUTO_TEST_CASE(bfs_v) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 0, 2}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 0, 1}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(BFSAcyclic)

BOOST_AUTO_TEST_CASE(bfs_dag) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  g.AddDiEdge(1, 3);
  g.AddDiEdge(1, 4);

  g.AddDiEdge(2, 5);
  g.AddDiEdge(2, 6);
  g.AddDiEdge(2, 7);

  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2, 3, 4, 5, 6, 7}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 3, 4}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 5, 6, 7}));
  BOOST_TEST(g.BFS(3) == (list<int>{3}));
  BOOST_TEST(g.BFS(4) == (list<int>{4}));
  BOOST_TEST(g.BFS(5) == (list<int>{5}));
  BOOST_TEST(g.BFS(6) == (list<int>{6}));
  BOOST_TEST(g.BFS(7) == (list<int>{7}));
}

BOOST_AUTO_TEST_CASE(bfs_ag) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  g.AddEdge(1, 3);
  g.AddEdge(1, 4);

  g.AddEdge(2, 5);
  g.AddEdge(2, 6);
  g.AddEdge(2, 7);

  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2, 3, 4, 5, 6, 7}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 0, 3, 4, 2, 5, 6, 7}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 0, 5, 6, 7, 1, 3, 4}));
  BOOST_TEST(g.BFS(3) == (list<int>{3, 1, 0, 4, 2, 5, 6, 7}));
  BOOST_TEST(g.BFS(4) == (list<int>{4, 1, 0, 3, 2, 5, 6, 7}));
  BOOST_TEST(g.BFS(5) == (list<int>{5, 2, 0, 6, 7, 1, 3, 4}));
  BOOST_TEST(g.BFS(6) == (list<int>{6, 2, 0, 5, 7, 1, 3, 4}));
  BOOST_TEST(g.BFS(7) == (list<int>{7, 2, 0, 5, 6, 1, 3, 4}));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(BFSCyclic)

BOOST_AUTO_TEST_CASE(bfs_dcg) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(1, 2);
  g.AddDiEdge(2, 0);

  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 2, 0}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 0, 1}));
}

BOOST_AUTO_TEST_CASE(bfs_cg) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 0, 2}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 1, 0}));
}

BOOST_AUTO_TEST_CASE(bfs_cg_big) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  g.AddEdge(0, 3);
  g.AddEdge(3, 2);

  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 3);

  BOOST_TEST(g.BFS(0) == (list<int>{0, 1, 2, 3, 4, 5}));
  BOOST_TEST(g.BFS(1) == (list<int>{1, 0, 2, 3, 4, 5}));
  BOOST_TEST(g.BFS(2) == (list<int>{2, 1, 0, 3, 4, 5}));
  BOOST_TEST(g.BFS(3) == (list<int>{3, 0, 2, 4, 5, 1}));
  BOOST_TEST(g.BFS(4) == (list<int>{4, 3, 5, 0, 2, 1}));
  BOOST_TEST(g.BFS(5) == (list<int>{5, 4, 3, 0, 2, 1}));
}

BOOST_AUTO_TEST_SUITE_END()
