/* ********************************************************************************* *
 * *  File: frame.h                                                                * *
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

#ifndef FRAME_H
#define FRAME_H

#include "math/linear.h"
#include "math/transform.h"

/*
 * Open namespace: math
 */
namespace math{
	/*
	 * Open namespace: math::affine
	 */
	namespace affine{


	using namespace math::linear;



	struct FRAME
	{
		/*
		 * Attributes
		 */
		MATRIX2	B;
		VECTOR2 O;

		/*
		 * Construction
		 */
		// Default
		FRAME()
			: B(), O()
		{}

		// Initialisation
		FRAME(
			MATRIX2 const& b,
			TUPLE2 const& o
			)
			: B(b), O(o)
		{}

		FRAME(
			TUPLE2  const& o,
			VECTOR2 const& e0,
			VECTOR2 const& e1
			)
			: B(e0,e1), O(o)
		{}

		FRAME( AFFINE2D const & m )
		{
			m.to_components(B, O);
		}

		// Copy
		FRAME(FRAME const& f)
		{
			if (&f != this)
			{
				B = f.B;
				O = f.O;
			}
		}

		// Conversion
		operator AFFINE2D()
		{
			return AFFINE2D(B, O);
		}


		inline VECTOR2 to_local(VECTOR2 const & v) const
		{
			return transpose(B) * v;
		}

		inline VECTOR2 to_parent(VECTOR2 const & v) const
		{
			return B* v;
		}

		inline POINT2 to_local(POINT2 const & p) const
		{
			return static_cast<POINT2>(transpose(B) * (p - O));
		}

		inline POINT2 to_parent(POINT2 const & p) const
		{
			return B * p + O;
		}

		friend inline void translate(FRAME & F, VECTOR3 const& p)
		{
			F.O = F.O + p;			
		}

		friend inline void rotate(FRAME & F, MATRIX2 const & R)
		{
			F.B = R * F.B;
		}

		friend inline void rotate(FRAME & F, SCALAR const & a)
		{
			// a is an angle in radians
			float cos_a = cos(a);
			float sin_a = sin(a);

			F.B = MATRIX2(VECTOR2(cos_a, sin_a), VECTOR2(-sin_a, cos_a)) * F.B;
		}


		friend inline void transform(FRAME & F, AFFINE2D const & M)
		{
			AFFINE2D result = AFFINE2D(F) * M;
			result.to_components(F.B, F.O);
		}

	};

	} // close namespace affine
} // close namespace math

#endif