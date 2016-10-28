/* ********************************************************************************* *
 * *  File: linear.h                                                               * *
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

#ifndef LINEAR_H
#define LINEAR_H

#include <cmath>
#include "math/tuple_t.h"
#include "math/point_t.h"
#include "math/vector_t.h"
#include "math/matrix_t.h"
#include "math/quaternion_t.h"
#include "math/calc.h"

/*
 * Open namespace: math
 */
namespace math { // open namespace 'math'
	/*
	 * Open namespace: math::linear
	 */
	namespace linear { // open namespace 'math::linear'

		using namespace math::affine;

		// Default scalar types
		typedef  float			SCALAR;

		// Default tuple types
		typedef _tuple_2<SCALAR> TUPLE2;
		typedef _tuple_3<SCALAR> TUPLE3;
		typedef _tuple_4<SCALAR> TUPLE4;

		// Default point types
		typedef _point_2<SCALAR> POINT2;


		// Default vector types
		typedef _vector_2<SCALAR> VECTOR2;
		typedef _vector_3<SCALAR> VECTOR3;
		typedef _vector_4<SCALAR> VECTOR4;

		typedef _matrix_2<SCALAR> MATRIX2;
		typedef _matrix_3<SCALAR> MATRIX3;
		typedef _matrix_4<SCALAR> MATRIX4;



		/*
		 * Linear Interpolation
		 */
		template <typename V, typename F>
		inline V lerp(V const & p, V const & q, F const & t)
		{
			return p + t * (p - q);
		}

		/*
		 * Use the following (nlerp,slerp) only with math::linear:_vector_#<F> 
		 * or quaternion<F> types
		 */

		/*
		 * Normalised Linear Interpolation
		 */
		template <typename V, typename F>
		inline V nlerp(V const & p, V const & q, F const & t)
		{
			return normalise(lerp(p,q,t));
		}

		/*
		 * Spherical Linear Interpolation
		 */
		template <typename V, typename F>
		inline V slerp(V const & p, V const & q, F const & t)
		{
			V v1 = p, v2 = q;
			F dot = inner_product(normalise(v1),normalise(v2));
			if (equivalent(dot,1.0,1.0e-4))
			{
				return normalise(lerp(v1,v2,t));
			}

			F d = clamp(dot,-1.0,1.0);
			double theta = ::acos(d) * t;
	
			return v1 * ::cos(theta) + normalise(v2 - d * v1) * ::sin(theta);
		}

		static const MATRIX2 EYE2 = MATRIX2(TUPLE2(1,0),TUPLE2(0,1));

	} // close namespace linear
} // close namespace math

#endif