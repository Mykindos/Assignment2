/* ********************************************************************************* *
 * *  File: transform.h                                                            * *
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

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "math/linear.h"

/*
 * Open namespace: math
 */
namespace math {
	/*
	 * Open namespace: math::affine
	 */
	namespace affine {

		using namespace math::linear;

		class AFFINE2D: public MATRIX3
		{
			public:
				AFFINE2D(POINT2 const & p,
						 VECTOR2 const & e0,
						 VECTOR2 const & e1,
						 VECTOR2 const & s = { 1, 1 }
						)
					: MATRIX3(	VECTOR3(s.x*e0.x, s.y*e0.y, 0),
								VECTOR3(s.x*e1.x, s.y*e1.y, 0),
								VECTOR3(s.x*p.x, s.y*p.y, 1)
							 )
				{}

				AFFINE2D(MATRIX2 const & A, TUPLE2 const & p)
				{
					C[0][0] = A[0][0];
					C[0][1] = A[0][1];
					C[0][2] = 0;
					C[1][0] = A[1][0];
					C[1][1] = A[1][1];
					C[1][2] = 0;
					C[2][0] = p.x;
					C[2][1] = p.y;
					C[2][2] = 1;
				}

				AFFINE2D(MATRIX3 const & m)
					: MATRIX3(m)
				{}

				operator MATRIX3() { return static_cast<MATRIX3 &>(*this); }

				void to_components(MATRIX2 & A, VECTOR2 & p) const
				{
					A[0][0] = this->C[0][0];
					A[0][1] = this->C[0][1];
					A[1][0] = this->C[1][0];
					A[1][1] = this->C[1][1];
					p.x = C[2][0];
					p.y = C[2][1];
				}

		};

	}
}

#endif