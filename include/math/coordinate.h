#ifndef COORDINATE_H
#define COORDINATE_H

#include "math/linear.h"

/*
 * Open namespace: math
 */
namespace math{
	/*
	 * Open namespace: math::affine
	 */
	namespace affine{


	using namespace math::linear;

	struct BASIS : public MATRIX3
	{

		/*
		 * Construction
		 */

		// Default
		BASIS() 
			: MATRIX3()
		{}

		// Initialisation
		BASIS(
			VECTOR3 const& e0,
			VECTOR3 const& e1,
			VECTOR3 const& e2
			)
			: MATRIX3(e0,e1,e2)
		{}

		BASIS( MATRIX3 const& m)
			: MATRIX3(m)
		{}

		BASIS( QUATERNION const& q)
			: MATRIX3(LINEAR_TRANSFORM(q))
		{}

		// Copy
		BASIS(BASIS const& b)
		{
			if (&b != this)
			{
				C[0] = b.C[0];
				C[1] = b.C[1];
				C[2] = b.C[2];
			}
		}
		/*
		 * Array access
		 */

		//// Read only access
		inline VECTOR3 const& operator[](size_t i) const
		{
			return this->C[i];
		}


		/*
		 * Conversion
		 */

		QUATERNION const to_quaternion() const
		{

		}


		/*
		 * Mathematical/Computational operators
		 */


		friend inline BASIS operator*(MATRIX3 const& a, BASIS const& b)
		{
			return BASIS(a*MATRIX3(b));
		}


		inline VECTOR3 to_parent(VECTOR3 const &v) const
		{
			return C[0]*v.x + C[1]*v.y + C[2]*v.z;
		}

		inline VECTOR3 to_local(VECTOR3 const& v) const
		{
			return VECTOR3(
						inner_product(C[0],v),
						inner_product(C[1],v),
						inner_product(C[2],v)
						);
		}

		friend inline BASIS inverse(BASIS const& b)
		{
			return BASIS(transpose(b));
		}

	};


	struct FRAME
	{
		/*
		 * Attributes
		 */
		BASIS	B;
		VECTOR3 O;

		/*
		 * Construction
		 */
		// Default
		FRAME()
			: B(), O()
		{}

		// Initialisation
		FRAME(
			MATRIX3 const& b,
			VECTOR3 const& o
			)
			: B(b), O(o)
		{}

		FRAME(
			VECTOR3 const& o,
			VECTOR3 const& e0,
			VECTOR3 const& e1,
			VECTOR3 const& e2
			)
			: B(e0,e1,e2), O(o)
		{}

		FRAME( AFFINE_TRANSFORM const& m )
			: B(), O()
		{
			for (size_t c = 0; c < MATRIX3::ROWS; ++c)
			{
				for (size_t r = 0; r < MATRIX3::COLS; ++r)
				{
					B.C[c][r] = m.C[c][r];
				}
			}
			O = VECTOR3(m.C[3][0],m.C[3][1],m.C[3][2]);
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

		inline VECTOR3 to_local(VECTOR3 const& p) const
		{
			return B.to_local(p - O);
		}

		inline VECTOR3 to_parent(VECTOR3 const& p) const
		{
			return B.to_parent(p) + O;
		}

		friend inline FRAME const& translate(FRAME& f, VECTOR3 const& p)
		{
			f.O += p;
			return f;
		}

		friend inline FRAME const& rotate(FRAME& f, LINEAR_TRANSFORM const& a)
		{
			f.B = (a * f.B);
			return f;
		}

	};

	} // close namespace affine
} // close namespace math

#endif