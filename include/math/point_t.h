/* ********************************************************************************* *
 * *  File: point_t.h                                                              * *
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

#ifndef POINT_H
#define POINT_H

#include "math/tuple_t.h"
#include "math/vector_t.h"

/*
 * Open namespace: math
 */
namespace math { // open namespace 'math'
	/*
	 * Open namespace: math::linear
	 */
	namespace affine { // open namespace 'math::affine'

		using namespace math::linear;

	/*
	 * _point_2<T>		3 element point class implementing homogeneous coordinates
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T>
	class _point_2 : public _tuple_2<T>
	{
		public:
			typedef typename _tuple_2<T>::value_type	value_type;

			_point_2() 
				: _tuple_2()
			{}

			_point_2(_tuple_2 const & t)
				: _tuple_2(t)
			{}

			_point_2(_point_2 const & t)
				: _tuple_2(t.x, t.y)
			{}

			_point_2(T const & _x, T const & _y)
				: _tuple_2(_x, _y)
			{}

			// Addition
			//inline _point_2 const operator+( _tuple_2 const& t ) const
			//{
			//	return _point_2( x + t.x, y + t.y );
			//}

			// Additive assignment
			_point_2 const& operator+=( _vector_2<T> const& t)
			{
				x += t.x;
				y += t.y;
				return *this;
			}

			// Subtractive assignment
			_point_2 const& operator-=( _vector_2<T> const& t)
			{
				x -= t.x;
				y -= t.y;
				return *this;
			}

			// Addition: point + vector
			inline _point_2 operator+( _vector_2<T> const& t ) const
			{
				return _point_2( x + t.x, y + t.y );
			}

			// Subtraction: point - vector
			inline _point_2 operator-( _vector_2<T> const& t ) const
			{
				return _point_2( x - t.x, y - t.y );
			}

			// Addition: point + double
			inline _point_2 operator+(double const& t) const
			{
				return _point_2(x + t, y + t);
			}

			// Subtraction: point - point
			inline _vector_2<T> operator-( _point_2 const& t ) const
			{
				return _vector_2<T>( x - t.x, y - t.y );
			}



			// Prefix multiplication by a scalar
			template <typename U>
			friend inline _point_2<U> operator*( U const a, _point_2<U> const& p)
			{
				return p * a;
			}
	
			// Addition of point plus vector
			template <typename U>
			friend inline _point_2<U> operator+(_vector_2<U> const & v, _point_2<U> const & p)
			{
				return (_point_2<U>)((_tuple_2<U>)v + (_tuple_2<U>)p);
			}

			// Addition of vector plus point
			template <typename U>
			friend inline _point_2<U> operator+(_point_2<U> const & p, _vector_2<U> const & v)
			{
				return (v+p);
			}

			// Subtraction of point from vector
			template <typename U>
			friend inline _point_2<U> operator-(_vector_2<U> const & v, _point_2<U> const & p)
			{
				return (v + -p);
			}

			// Subtraction of vector from point
			template <typename U>
			friend inline _point_2<U> operator-(_point_2<U> const & p, _vector_2<U> const & v)
			{
				return (-v + p);
			}

			/*
			 * The following operators are overloaded and hidden as private since they are not meaningful for points
			 * If C++0x11 is available, we can use the '=delete' modifier on the definition.
			 */
		private:
			// Additive assignment
			_tuple_2 const& operator+=( _tuple_2 const& t)
			{
				x += t.x;
				y += t.y;
				return *this;
			}

			// Subtractive assignment
			_tuple_2 const& operator-=( _tuple_2 const& t)
			{
				x -= t.x;
				y -= t.y;
				return *this;
			}




	};

		} // close namespace 'math::affine'
} // close namesace 'math'

#endif

