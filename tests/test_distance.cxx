#include <boost/test/unit_test.hpp>
#include <list>

#include "graph/graph.hxx"

using std::list;

BOOST_AUTO_TEST_SUITE(DistanceSimple)

BOOST_AUTO_TEST_CASE(distance_simple) {
  Graph g;
  g.AddEdge(0, 1);
  BOOST_TEST(g.Distance(0, 1) == 1);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DistanceChains)

BOOST_AUTO_TEST_CASE(distance_di_chain) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(g.Distance(0, 1) == 1);
  BOOST_TEST(g.Distance(1, 1) == 0);
  BOOST_TEST(g.Distance(1, 2) == 1);
  BOOST_TEST(g.Distance(0, 2) == 2);
}

BOOST_AUTO_TEST_CASE(distance_chain) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(g.Distance(0, 1) == 1);
  BOOST_TEST(g.Distance(1, 2) == 1);
  BOOST_TEST(g.Distance(0, 2) == 2);
  BOOST_TEST(g.Distance(2, 0) == 2);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DistanceVs)

BOOST_AUTO_TEST_CASE(distance_di_v) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  BOOST_TEST(g.Distance(0, 1) == 1);
  BOOST_TEST(g.Distance(0, 2) == 1);
  BOOST_TEST(g.Distance(1, 0) == -1);
  BOOST_TEST(g.Distance(2, 0) == -1);
  BOOST_TEST(g.Distance(1, 2) == -1);
}

BOOST_AUTO_TEST_CASE(distance_v) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  BOOST_TEST(g.Distance(0, 1) == 1);
  BOOST_TEST(g.Distance(0, 2) == 1);
  BOOST_TEST(g.Distance(1, 0) == 1);
  BOOST_TEST(g.Distance(2, 0) == 1);
  BOOST_TEST(g.Distance(1, 2) == 2);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DistanceAcyclic)

BOOST_AUTO_TEST_CASE(distance_dag) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  g.AddDiEdge(1, 3);
  g.AddDiEdge(1, 4);

  g.AddDiEdge(2, 5);
  g.AddDiEdge(2, 6);
  g.AddDiEdge(2, 7);

  BOOST_TEST(g.Distance(0, 7) == 2);
  BOOST_TEST(g.Distance(0, 4) == 2);
  BOOST_TEST(g.Distance(1, 4) == 1);
  BOOST_TEST(g.Distance(2, 5) == 1);
  BOOST_TEST(g.Distance(6, 6) == 0);
  BOOST_TEST(g.Distance(7, 3) == -1);
}

BOOST_AUTO_TEST_CASE(distance_ag) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  g.AddEdge(1, 3);
  g.AddEdge(1, 4);

  g.AddEdge(2, 5);
  g.AddEdge(2, 6);
  g.AddEdge(2, 7);

  BOOST_TEST(g.Distance(0, 7) == 2);
  BOOST_TEST(g.Distance(0, 4) == 2);
  BOOST_TEST(g.Distance(1, 4) == 1);
  BOOST_TEST(g.Distance(2, 5) == 1);
  BOOST_TEST(g.Distance(6, 6) == 0);
  BOOST_TEST(g.Distance(7, 3) == 4);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(DistanceCyclic)

BOOST_AUTO_TEST_CASE(distance_dcg) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(1, 2);
  g.AddDiEdge(2, 0);

  BOOST_TEST(g.Distance(0, 1) == 1);
  BOOST_TEST(g.Distance(1, 2) == 1);
  BOOST_TEST(g.Distance(2, 0) == 1);
  BOOST_TEST(g.Distance(0, 2) == 2);
}

BOOST_AUTO_TEST_CASE(distance_cg) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  BOOST_TEST(g.Distance(0, 1) == 1);
  BOOST_TEST(g.Distance(1, 2) == 1);
  BOOST_TEST(g.Distance(2, 0) == 1);
  BOOST_TEST(g.Distance(0, 2) == 1);
}

BOOST_AUTO_TEST_CASE(distance_cg_big) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  g.AddEdge(0, 3);
  g.AddEdge(3, 2);

  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 3);

  BOOST_TEST(g.Distance(2, 5) == 2);
  BOOST_TEST(g.Distance(4, 1) == 3);
  BOOST_TEST(g.Distance(1, 5) == 3);
  BOOST_TEST(g.Distance(0, 2) == 1);
}

BOOST_AUTO_TEST_SUITE_END()
