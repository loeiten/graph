#include <boost/test/unit_test.hpp>
#include <limits>
#include <list>

#include "graph/weighted_graph.hxx"

using std::list;
using std::numeric_limits;

// NOTE: Using machine epsilon to compare floats
//       https://www.boost.org/doc/libs/1_75_0/libs/test/doc/html/boost_test/testing_tools/extended_comparison/floating_point.html
//       https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon

BOOST_AUTO_TEST_SUITE(WeightedDistanceSimple)

BOOST_AUTO_TEST_CASE(
    weighted_distance_simple,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddEdge(0, 1);
  BOOST_TEST(g.Distance(0, 1) == 1.0);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(WeightedDistanceChains)

BOOST_AUTO_TEST_CASE(
    weighted_distance_di_chain,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddDiEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(g.Distance(0, 1) == 1.0);
  BOOST_TEST(g.Distance(1, 1) == 0.0);
  BOOST_TEST(g.Distance(1, 2) == 1.0);
  BOOST_TEST(g.Distance(0, 2) == 2.0);
}

BOOST_AUTO_TEST_CASE(
    weighted_distance_chain,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(g.Distance(0, 1) == 1.0);
  BOOST_TEST(g.Distance(1, 2) == 1.0);
  BOOST_TEST(g.Distance(0, 2) == 2.0);
  BOOST_TEST(g.Distance(2, 0) == 2.0);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(WeightedDistanceVs)

BOOST_AUTO_TEST_CASE(
    weighted_distance_di_v,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  BOOST_TEST(g.Distance(0, 1) == 1.0);
  BOOST_TEST(g.Distance(0, 2) == 1.0);
  BOOST_TEST(g.Distance(1, 0) == numeric_limits<double>::infinity());
  BOOST_TEST(g.Distance(2, 0) == numeric_limits<double>::infinity());
  BOOST_TEST(g.Distance(1, 2) == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(
    weighted_distance_v,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  BOOST_TEST(g.Distance(0, 1) == 1.0);
  BOOST_TEST(g.Distance(0, 2) == 1.0);
  BOOST_TEST(g.Distance(1, 0) == 1.0);
  BOOST_TEST(g.Distance(2, 0) == 1.0);
  BOOST_TEST(g.Distance(1, 2) == 2.0);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(WeightedDistanceAcyclic)

BOOST_AUTO_TEST_CASE(
    weighted_distance_dag,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  g.AddDiEdge(1, 3);
  g.AddDiEdge(1, 4);

  g.AddDiEdge(2, 5);
  g.AddDiEdge(2, 6);
  g.AddDiEdge(2, 7);

  BOOST_TEST(g.Distance(0, 7) == 2.0);
  BOOST_TEST(g.Distance(0, 4) == 2.0);
  BOOST_TEST(g.Distance(1, 4) == 1.0);
  BOOST_TEST(g.Distance(2, 5) == 1.0);
  BOOST_TEST(g.Distance(6, 6) == 0.0);
  BOOST_TEST(g.Distance(7, 3) == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(
    weighted_distance_ag,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  g.AddEdge(1, 3);
  g.AddEdge(1, 4);

  g.AddEdge(2, 5);
  g.AddEdge(2, 6);
  g.AddEdge(2, 7);

  BOOST_TEST(g.Distance(0, 7) == 2.0);
  BOOST_TEST(g.Distance(0, 4) == 2.0);
  BOOST_TEST(g.Distance(1, 4) == 1.0);
  BOOST_TEST(g.Distance(2, 5) == 1.0);
  BOOST_TEST(g.Distance(6, 6) == 0.0);
  BOOST_TEST(g.Distance(7, 3) == 4.0);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(WeightedDistanceCyclic)

BOOST_AUTO_TEST_CASE(
    weighted_distance_dcg,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(1, 2);
  g.AddDiEdge(2, 0);

  BOOST_TEST(g.Distance(0, 1) == 1.0);
  BOOST_TEST(g.Distance(1, 2) == 1.0);
  BOOST_TEST(g.Distance(2, 0) == 1.0);
  BOOST_TEST(g.Distance(0, 2) == 2.0);
}

BOOST_AUTO_TEST_CASE(
    weighted_distance_cg,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  BOOST_TEST(g.Distance(0, 1) == 1.0);
  BOOST_TEST(g.Distance(1, 2) == 1.0);
  BOOST_TEST(g.Distance(2, 0) == 1.0);
  BOOST_TEST(g.Distance(0, 2) == 1.0);
}

BOOST_AUTO_TEST_CASE(
    weighted_distance_cg_big,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  g.AddEdge(0, 3);
  g.AddEdge(3, 2);

  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 3);

  BOOST_TEST(g.Distance(2, 5) == 2.0);
  BOOST_TEST(g.Distance(4, 1) == 3.0);
  BOOST_TEST(g.Distance(1, 5) == 3.0);
  BOOST_TEST(g.Distance(0, 2) == 1.0);
}

BOOST_AUTO_TEST_CASE(
    weighted_distance_cg_actual_weights,
    *boost::unit_test::tolerance(numeric_limits<double>::epsilon())) {
  WeightedGraph g;
  g.AddEdge(1, 2, 3.5);
  g.AddEdge(1, 3, 4.5);
  g.AddEdge(1, 6, 7.0);

  g.AddEdge(2, 4, 7.5);
  g.AddEdge(2, 3, 5.0);

  g.AddEdge(3, 6, 1.0);

  g.AddEdge(4, 5, 3.0);
  g.AddEdge(6, 5, 4.2);

  BOOST_TEST(g.Distance(1, 5) == 9.7);
}

BOOST_AUTO_TEST_SUITE_END()
