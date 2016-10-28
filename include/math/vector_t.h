/* ********************************************************************************* *
 * *  File: vector_t.h                                                             * *
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

#ifndef VECTOR_T_H
#define VECTOR_T_H


#include "math/tuple_t.h"
/*
 * Open namespace: math
 */
namespace math { // open namespace 'math'
	/*
	 * Open namespace: math::linear
	 */
	namespace linear { // open namespace 'math::linear'

	using namespace math::affine;

	enum class AXIS_FRD : size_t {FORWARD = 0, RIGHT = 1, DOWN = 2};
	enum class AXIS_RFU : size_t {RIGHT = 0, FORWARD = 1, UP = 2};
	enum class AXIS_XYZ : size_t {X = 0, Y = 1, Z = 2};

	/*
	 * _vector_2<T>				2 element vector class
	 *   : public _tuple_2<T>	extends tuple_2<T>
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T>
	struct _vector_2 : public _tuple_2<T>
	{
		typedef typename _tuple_2<T>::value_type	value_type;

		/*
		 * Construction
		 */

		// Default
		_vector_2()
			: _tuple_2()
		{}

		// Initialisation
		_vector_2( T const _x, T const _y )
			: _tuple_2(_x, _y)
		{}

		_vector_2( _tuple_2<T> const& t)
			: _tuple_2(t)
		{}

		// Copy
		_vector_2( _vector_2 const& v )
		{
			if (this != &v)
			{
				x = v.x;
				y = v.y;
			}
		}

		// Magnitude
		inline T const length() const
		{
			return sqrt( length_sqr() );
		}

		inline T const length_sqr() const
		{
			return T( x*x + y*y );
		}

		template <typename U>
		friend inline _vector_2<U>& normalise(_vector_2<U>& v)
		{
			v /= v.length();
			return v;
		}

		template <typename U>
		friend inline _vector_2<U> normalise(_vector_2<U> const & v)
		{
			return v / v.length();
		}

		template <typename U>
		friend inline U const inner_product(_vector_2<U> const& u, _vector_2<U> const& v)
		{
			return  U( u.x*v.x + u.y*v.y );
		}

	};


	/*
	 * _vector_3<T>				3 element vector class
	 *   : public _tuple_3<T>	extends tuple_3<T>
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T>
	struct _vector_3 : public _tuple_3<T>
	{

		typedef typename _tuple_3<T>::value_type	value_type;

		/*
		 * Construction
		 */

		// Default
		_vector_3()
			: _tuple_3((T)0, (T)0, (T)0)
		{}

		// Initialisation
		_vector_3( T const _x, T const _y, T const _z )
			: _tuple_3(_x, _y, _z)
		{}

		_vector_3( _tuple_3<T> const& t)
			: _tuple_3(t)
		{}

		// Copy
		_vector_3( _vector_3 const& v )
		{
			if (this != &v)
			{
				x = v.y;
				y = v.y;
				z = v.z;
			}
		}

		// Magnitude
		inline T const length() const
		{
			return sqrt( length_sqr() );
		}

		inline T const length_sqr() const
		{
			return T( x*x + y*y + z*z );
		}

		template <typename U>
		friend inline _vector_3<U>& normalise(_vector_3<U>& v)
		{
			v /= v.length();
			return v;
		}

		template <typename U>
		friend inline _vector_3<U> normalise(_vector_3<U> const & v)
		{
			return v / v.length();
		}

		template <typename U>
		friend inline U const inner_product(_vector_3<U> const& u, _vector_3<U> const& v)
		{
			return ( u.x*v.x + u.y*v.y + u.z*v.z );
		}

		template <typename U>
		friend inline _vector_3<U> const outer_product(_vector_3<U> const& u, _vector_3<U> const& v)
		{
			return _vector_3<T>(
								u.y * v.z - u.z * v.y,
								u.z * v.x - u.x * v.z,
								u.x * v.y - u.y * v.x
								);
		}

	};


	/*
	 * _vector_4<T>				4 element vector class
	 *   : public _tuple_4<T>	extends tuple_4<T>
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T>
	struct _vector_4 : public _tuple_4<T>
	{

		typedef typename _tuple_4<T>::value_type	value_type;

		/*
		 * Construction
		 */

		// Default
		_vector_4()
			: _tuple_4()
		{}

		// Initialisation
		_vector_4( T const _x, T const _y, T const _z, T const _w )
			: _tuple_4(_x, _y, _z, _w)
		{}

		_vector_4( _tuple_4<T> const& t)
			: _tuple_4(t)
		{}

		// Copy
		_vector_4( _vector_4 const& v )
		{
			if (this != &v)
			{
				x = v.y;
				y = v.y;
				z = v.z;
				w = v.w;
			}
		}

		// Magnitude
		inline T const length() const
		{
			return sqrt( length_sqr() );
		}

		inline T const length_sqr() const
		{
			return T( x*x + y*y + z*z + w*w );
		}
	
		template <typename U>
		friend inline _vector_4<U>& normalise(_vector_4<U>& v)
		{
			v /= v.length();
			return v;
		}

		template <typename U>
		friend inline _vector_4<U> normalise(_vector_4<U> const & v)
		{
			return v / v.length();
		}

		template <typename U>
		friend inline U const inner_product(_vector_4<U> const& u, _vector_4<U> const& v)
		{
			return U( u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w );
		}
	};

	} // close namespace 'math::linear'
} // close namesace 'math'

#endif