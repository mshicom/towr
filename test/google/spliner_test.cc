/*
 * gtest_zmp.cpp
 *
 *  Created on: May 23, 2014
 *      Author: awinkler
 */

#include <gtest/gtest.h>
#include <xpp/utils/spliner.h>
#include <iostream>

#define prt(x) std::cout << #x << " = " << x << std::endl;

namespace xpp {
namespace utils {

typedef Spliner::Point Point;

// A start and an end position for the splines. checking only boundary conditions
class SplineTest : public ::testing::Test {
protected:
  virtual void SetUp()
  {
    start.x   =  5.0;
    start.xd  = -1.0;
    start.xdd =  3.0;

    end.x   =  4.0;
    end.xd  =  2.0;
    end.xdd =  2.2;

    T = 3.2;
  }

  Spliner::Point start;
  Spliner::Point end;
  double T;
};

TEST_F(SplineTest, LinearSpliner)
{
  LinearSpliner s;
  s.SetBoundary(T, start, end);

  Spliner::Point p0, p1;
  s.GetPoint(0.0, p0);
  s.GetPoint(T, p1);

  // pos
  EXPECT_FLOAT_EQ(start.x, p0.x);
  EXPECT_FLOAT_EQ(end.x, p1.x);
  // vel
  EXPECT_FLOAT_EQ(p0.xd, p1.xd);
  // acc
  EXPECT_FLOAT_EQ(0.0, p0.xdd);
  EXPECT_FLOAT_EQ(0.0, p1.xdd);
}


TEST_F(SplineTest, CubicSpliner)
{
  CubicSpliner s;
  s.SetBoundary(T, start, end);

  Spliner::Point p0, p1;
  s.GetPoint(0.0, p0);
  s.GetPoint(T, p1);

  // pos
  EXPECT_FLOAT_EQ(start.x, p0.x);
  EXPECT_FLOAT_EQ(end.x, p1.x);
  // vel
  EXPECT_FLOAT_EQ(start.xd, p0.xd);
  EXPECT_FLOAT_EQ(end.xd, p1.xd);
}


TEST_F(SplineTest, FifthOrderSpliner)
{
  QuinticSpliner s;
  s.SetBoundary(T, start, end);

  Spliner::Point p0, p1;
  s.GetPoint(0.0, p0);
  s.GetPoint(T, p1);

  // pos
  EXPECT_FLOAT_EQ(start.x, p0.x);
  EXPECT_FLOAT_EQ(end.x, p1.x);
  // vel
  EXPECT_FLOAT_EQ(start.xd, p0.xd);
  EXPECT_FLOAT_EQ(end.xd, p1.xd);
  // acc
  EXPECT_FLOAT_EQ(start.xdd, p0.xdd);
  EXPECT_FLOAT_EQ(end.xdd, p1.xdd);
}


TEST_F(SplineTest, FifthOrderSplinerSameStartGoal)
{
  QuinticSpliner s;
  double t = 0.001;


  Point p;
  p.x   = 2.0;
  p.xd  = 2.0;
  p.xdd = 2.0;

  Point pg;
  p.x   = 2.1;
  p.xd  = 2.0;
  p.xdd = 2.0;

  s.SetBoundary(t, p, pg);

  for (double c : s.c) prt(c);

  Spliner::Point p0, p1, p2;
  s.GetPoint(0.0, p0);
  s.GetPoint(t/2.0, p1);
  s.GetPoint(t,   p2);

  // pos
  EXPECT_FLOAT_EQ(2.0, p0.x);
  EXPECT_FLOAT_EQ(2.0, p1.x);
  EXPECT_FLOAT_EQ(2.0, p2.x);
  // vel
  EXPECT_FLOAT_EQ(2.0, p0.xd);
  EXPECT_FLOAT_EQ(2.0, p1.xd);
  EXPECT_FLOAT_EQ(2.0, p2.xd);
  // acc
  EXPECT_FLOAT_EQ(2.0, p0.xdd);
  EXPECT_FLOAT_EQ(2.0, p1.xdd);
  EXPECT_FLOAT_EQ(2.0, p2.xdd);
}


} // namespace utils
} // namespace xpp
