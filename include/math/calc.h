/* ********************************************************************************* *
 * *  File: calc.h                                                                 * *
 * *  ----------------                                                             * *
 * *  COPYRIGHT NOTICE                                                             * *
 * *  ----------------                                                             * *
 * *  (C)[2012] - [2015] Deakin University                                         * *
 * *  All rights reserved.                                                         * *
 * *  All information contained herein is, and remains the property of Deakin      * *
 * *  University and the author (Tim Wilkin).                                      * *
 * *  Dissemination of this information or reproduction of this material is        * *
 * *  strictly forbidden unless prior written permission is obtained from Deakin   * *
 * *  University.The right to create derivative works from this material is        * *
 * *  hereby granted to students enrolled in SIT255, but only for the purposes of  * *
 * *  assessment while an enrolled student at Deakin University.                   * *
 * *                                                                               * *
 * ********************************************************************************* */

#ifndef CALC_H
#define CALC_H

#include <cmath>
#include <cfloat>

namespace math { // open namespace math

/*
 * Mathematical Constants
 */

float const PI	 = abs(acos(-1.0f));
float const PI_2 = PI / 2.0f;
float const PI_3 = PI / 3.0f;
float const PI_4 = PI / 4.0f;
float const PI_6 = PI / 6.0f;

/*
 *  Helper functions
 */

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

inline float const to_radian(float d)
{
	return ( d * PI / 180.0f );
}

inline float const to_degrees(float r)
{
	return ( r * 180.0f / PI );
}

template <typename T>
inline T sgn(T const& a)
{
	return (a > 0) ? 1 : ( ( a < 0 ) ? -1 : 0 );
}

template <typename T>
inline T min(T const& a, T const& b)
{
	return ( b < a ) ? b : a;
}

template <typename T>
inline T max(T const& a, T const& b)
{
	return ( b > a ) ? b : a;
}

template <typename T>
inline T clamp(T const& v, T const& lower, T const& upper)
{
	return ( v < lower ) ? lower : ( ( v > upper ) ? upper : v );
}

template <typename T>
inline bool const equivalent(T const& a, T const& b, float eps = 1.0e-6)
{
	return ( fabs( float(b - a) ) <= eps );
}

template <typename T>
inline T sqrt_t ( T const a )
{
	return (T)sqrt( a );
}


} // close namespace math
#endif