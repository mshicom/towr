/**
@file    spliner_3d.cc
@author  Alexander Winkler (winklera@ethz.ch)
@date    Oct 21, 2014
@brief   Creates 3 dimensional spline from start to end with duration T
 */

#include <xpp/utils/spliner_3d.h>

namespace xpp {
namespace utils {

template<typename SplineType>
void Spliner3d<SplineType>::SetBoundary(double T, const Point& start,
                                                  const Point& end)
{
	Spliner::Point start_x, end_x;
	Spliner::Point start_y, end_y;
	Spliner::Point start_z, end_z;

	start_x.x   = start.p(X);  end_x.x   = end.p(X);
	start_x.xd  = start.v(X);  end_x.xd  = end.v(X);
	start_x.xdd = start.a(X);  end_x.xdd = end.a(X);

	start_y.x   = start.p(Y);  end_y.x   = end.p(Y);
	start_y.xd  = start.v(Y);  end_y.xd  = end.v(Y);
	start_y.xdd = start.a(Y);  end_y.xdd = end.a(Y);

	start_z.x   = start.p(Z);  end_z.x   = end.p(Z);
	start_z.xd  = start.v(Z);  end_z.xd  = end.v(Z);
	start_z.xdd = start.a(Z);  end_z.xdd = end.a(Z);


	splineX.SetBoundary(T, start_x, end_x);
	splineY.SetBoundary(T, start_y, end_y);
	splineZ.SetBoundary(T, start_z, end_z);
}


template<typename SplineType>
bool Spliner3d<SplineType>::GetPoint(const double dt, Point& p) const
{
  Spliner::Point coord_result;

  splineX.GetPoint(dt, coord_result);
  p.p(X) = coord_result.x;
  p.v(X) = coord_result.xd;
  p.a(X) = coord_result.xdd;

  splineY.GetPoint(dt, coord_result);
  p.p(Y) = coord_result.x;
  p.v(Y) = coord_result.xd;
  p.a(Y) = coord_result.xdd;

  splineZ.GetPoint(dt, coord_result);
  p.p(Z) = coord_result.x;
  p.v(Z) = coord_result.xd;
  p.a(Z) = coord_result.xdd;

  return true;
}

// generate required template classes from the class template
template class Spliner3d<LinearSpliner>;
template class Spliner3d<CubicSpliner>;
template class Spliner3d<QuinticSpliner>;


} // namespace utils
} // namespace xpp
