/* ********************************************************************************* *
 * *  File: tuple_t.h                                                              * *
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

#ifndef TUPLE_T_H
#define TUPLE_T_H

//#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

/*
 * Open namespace: math
 */
namespace math { // open namespace 'math'
	/*
	 * Open namespace: math::linear
	 */
	namespace affine { // open namespace 'math::affine'


	template <typename T> struct _tuple_2;
	template <typename T> struct _tuple_3;
	template <typename T> struct _tuple_4;

	/*
	 * _tuple_2<T>		2 element tuple class
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T>
	struct _tuple_2
	{
		typedef T	value_type;

		// Attributes
		T x, y;

		static const size_t size = 2;

		/*
		 * Construction
		 */

		// Default
		_tuple_2()
			: x((T)0), y((T)0)
		{}

		// Initialisation
		_tuple_2( T const _x, T const _y )
			: x(_x), y(_y)
		{}

		// Copy
		_tuple_2( _tuple_2 const& t )
		{
			if (this != &t)
			{
				x = t.x;
				y = t.y;
			}
		}

		/*
		 * Array access
		 */
		// Read-only-access
		T const& operator[]( size_t const i) const
		{
			return *(&x + i);
		}

		// Write-access
		T& operator[]( size_t const i )
		{
			return *(&x + i);
		}

		/*
		 * Assignment
		 */
		_tuple_2 const& operator=( _tuple_2 const& t )
		{
			if (this != &t)
			{
				x = t.x;
				y = t.y;
			}
			return *this;
		}

		/*
		 * Logical operators
		 */

		bool const operator==( _tuple_2 const& t) const
		{
			return ( x == t.x ) && ( y == t.y ) ;
		}

		bool const operator!=( _tuple_2 const& t) const
		{
			return ! ( *this == t ) ;
		}

		/*
		 * Mathematical/ computational operators
		 */

		// Negation
		_tuple_2 const operator-() const
		{
			return _tuple_2( -x, -y );
		}

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

		// Scalar multiplication
		_tuple_2 const& operator*=( T const a )
		{
			x *= a;
			y *= a;
			return *this;
		}

		// Scalar division
		_tuple_2 const& operator/=( T const a )
		{
#ifdef _DEBUG
				assert( a != 0 && "Divide by zero error in _tuple_2<T>::operator/=");
#endif
			if ( a != 0 ) 
			{
				x /= a;
				y /= a;
			}
			else
			{
				x = y = std::numeric_limits<T>::quiet_NaN();
			}
			return *this;
		}

		// Addition
		inline _tuple_2 const operator+( _tuple_2 const& t ) const
		{
			return _tuple_2( x + t.x, y + t.y );
		}

		// Subtraction
		inline _tuple_2 const operator-( _tuple_2 const& t ) const
		{
			return _tuple_2( x - t.x, y - t.y );
		}

		// Postfix scalar multiplication
		inline _tuple_2 const operator*( T const a ) const
		{
			return _tuple_2( x*a, y*a );
		}

		// Prefix scalar multiplication
		template <typename U>
		friend inline _tuple_2<U> const operator*( T const a, _tuple_2<U> const& t)
		{
			return t * a;
		}

		// Postfix scalar division
		inline _tuple_2 const operator/( T const a ) const
		{
#ifdef _DEBUG
				assert( a != 0 && "Divide by zero error in _tuple_2<T>::operator/=");
#endif
			if ( a != 0 ) 
				return _tuple_2( x/a, y/a );
			else
				return _tuple_2(std::numeric_limits<T>::quiet_NaN(),std::numeric_limits<T>::quiet_NaN());
		}

		// Output
		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, _tuple_2<U> const& t)
		{
			return os << "(" << t.x << "," << t.y << ")";
		}
	};


	/*
	 * _tuple_3<T>		3 element tuple class
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T>
	struct _tuple_3
	{
		typedef T	value_type;

		// Attributes
		T x, y, z;

		static const size_t size = 3;
		/*
		 * Construction
		 */

		// Default
		_tuple_3()
			: x(0), y(0), z(0)
		{}

		// Initialisation
		_tuple_3( T const _x, T const _y, T const _z )
			: x(_x), y(_y), z(_z)
		{}

		// Copy
		_tuple_3( _tuple_3 const& t )
		{
			if (this != &t)
			{
				x = t.y;
				y = t.y;
				z = t.z;
			}
		}

		/*
		 * Array access
		 */
		// Read-only-access
		T const& operator[]( size_t const i) const
		{
			return *(&x + i);
		}

		// Write-access
		T& operator[]( size_t const i )
		{
			return *(&x + i);
		}

		/*
		 * Assignment
		 */
		_tuple_3 const& operator=( _tuple_3 const& t )
		{
			if (this != &t)
			{
				x = t.x;
				y = t.y;
				z = t.z;
			}
			return *this;
		}

		/*
		 * Logical operators
		 */

		bool const operator==( _tuple_3 const& t) const
		{
			return ( x == t.x ) && ( y == t.y ) && ( z == t.z );
		}

		bool const operator!=( _tuple_3 const& t) const
		{
			return ! ( *this == t ) ;
		}

		/*
		 * Mathematical/ computational operators
		 */

		// Negation
		inline _tuple_3 const operator-() const
		{
			return _tuple_3( -x, -y, -z );
		}

		// Additive assignment
		_tuple_3 const& operator+=( _tuple_3 const& t)
		{
			x += t.x;
			y += t.y;
			z += t.z;

			return *this;
		}

		// Subtractive assignment
		_tuple_3 const& operator-=( _tuple_3 const& t)
		{
			x -= t.x;
			y -= t.y;
			z -= t.z;

			return *this;
		}

		// Scalar multiplication
		_tuple_3 const& operator*=( T const a )
		{
			x *= a;
			y *= a;
			z *= a;

			return *this;
		}

		// Scalar division
		_tuple_3 const& operator/=( T const a )
		{
#ifdef _DEBUG
				assert( a != 0 && "Divide by zero error in _tuple_3<T>::operator/=");
#endif
			if ( a != 0 ) 
			{
				x /= a;
				y /= a;
				z /= a;
			}
			else
			{
				x = y = z = std::numeric_limits<T>::quiet_NaN();
			}
			return *this;
		}

		// Addition
		inline _tuple_3 const operator+( _tuple_3 const& t ) const
		{
			return _tuple_3( x + t.x, y + t.y, z + t.z );
		}

		// Subtraction
		inline _tuple_3 const operator-( _tuple_3 const& t ) const
		{
			return _tuple_3( x - t.x, y - t.y, z - t.z );
		}

		// Postfix scalar multiplication
		inline _tuple_3 const operator*( T const a ) const
		{
			return _tuple_3( x*a, y*a, z*a );
		}

		// Prefix scalar multiplication
		template <typename U>
		friend inline _tuple_3<U> const operator*( T const a, _tuple_3<U> const& t)
		{
			return t * a;
		}

		// Postfix scalar division
		inline _tuple_3 const operator/( T const a ) const
		{
#ifdef _DEBUG
				assert( a != 0 && "Divide by zero error in _tuple_3<T>::operator/=");
#endif
			if ( a != 0 ) 
				return _tuple_3( x/a, y/a, z/a );
			else
				return _tuple_3(std::numeric_limits<T>::quiet_NaN(),
								std::numeric_limits<T>::quiet_NaN(),
								std::numeric_limits<T>::quiet_NaN()
								);
		}

		// Output
		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, _tuple_3<U> const& t)
		{
			return os << "(" << t.x << "," << t.y << "," << t.z << ")";
		}

	};

	/*
	 * _tuple_4<T>		4 element tuple class
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T>
	struct _tuple_4
	{
		typedef T	value_type;

		// Attributes
		T x, y, z, w;

		static const size_t size = 4;

		/*
		 * Construction
		 */

		// Default
		_tuple_4()
			: x(0), y(0), z(0), w(0)
		{}

		// Initialisation
		_tuple_4( T const _x, T const _y, T const _z, T const _w )
			: x(_x), y(_y), z(_z), w(_w)
		{}

		// Copy
		_tuple_4( _tuple_4 const& t )
		{
			if (this != &t)
			{
				x = t.y;
				y = t.y;
				z = t.z;
				w = t.w;
			}
		}

		/*
		 * Array access
		 */
		// Read-only-access
		T const& operator[]( size_t const i) const
		{
			return *(&x + i);
		}

		// Write-access
		T& operator[]( size_t const i )
		{
			return *(&x + i);
		}

		/*
		 * Assignment
		 */
		_tuple_4 const& operator=( _tuple_4 const& t )
		{
			if (this != &t)
			{
				x = t.x;
				y = t.y;
				z = t.z;
				w = t.w;
			}
			return *this;
		}

		/*
		 * Logical operators
		 */

		bool const operator==( _tuple_4 const& t) const
		{
			return ( x == t.x ) && ( y == t.y ) && ( z == t.z ) && ( w == t.w );
		}

		bool const operator!=( _tuple_4 const& t) const
		{
			return ! ( *this == t ) ;
		}

		/*
		 * Mathematical/ computational operators
		 */

		// Negation
		inline _tuple_4 const operator-() const
		{
			return _tuple_4( -x, -y, -z, -w );
		}

		// Additive assignment
		_tuple_4 const& operator+=( _tuple_4 const& t)
		{
			x += t.x;
			y += t.y;
			z += t.z;
			w += t.w;

			return *this;
		}

		// Subtractive assignment
		_tuple_4 const& operator-=( _tuple_4 const& t)
		{
			x -= t.x;
			y -= t.y;
			z -= t.z;
			w -= t.w;

			return *this;
		}

		// Scalar multiplication
		_tuple_4 const& operator*=( T const a )
		{
			x *= a;
			y *= a;
			z *= a;
			w *= a;

			return *this;
		}

		// Scalar division
		_tuple_4 const& operator/=( T const a )
		{
#ifdef _DEBUG
				assert( a != 0 && "Divide by zero error in _tuple_4<T>::operator/=");
#endif
			if ( a != 0 ) 
			{
				x /= a;
				y /= a;
				z /= a;
				w /= a;
			}
			else
			{
				x = y = z = w = std::numeric_limits<T>::quiet_NaN();
			}
			return *this;
		}

		// Addition
		inline _tuple_4 const operator+( _tuple_4 const& t ) const
		{
			return _tuple_4( x + t.x, y + t.y, z + t.z, w + t.w );
		}

		// Subtraction
		inline _tuple_4 const operator-( _tuple_4 const& t ) const
		{
			return _tuple_4( x - t.x, y - t.y, z - t.z, w - t.w );
		}

		// Postfix scalar multiplication
		inline _tuple_4 const operator*( T const a ) const
		{
			return _tuple_4( x*a, y*a, z*a, w*a );
		}

		// Prefix scalar multiplication
		template <typename U>
		friend inline _tuple_4<U> const operator*( T const a, _tuple_4<U> const& t)
		{
			return t * a;
		}

		// Postfix scalar division
		inline _tuple_4 const operator/( T const a ) const
		{
#ifdef _DEBUG
				assert( a != 0 && "Divide by zero error in _tuple_4<T>::operator/=");
#endif
			if ( a != 0 ) 
				return _tuple_4( x/a, y/a, z/a, w/a );
			else
				return _tuple_4(std::numeric_limits<T>::quiet_NaN(),
								std::numeric_limits<T>::quiet_NaN(),
								std::numeric_limits<T>::quiet_NaN(),
								std::numeric_limits<T>::quiet_NaN()
								);
		}

		// Output
		template <typename U>
		friend inline std::ostream& operator<<(std::ostream& os, _tuple_4<U> const& t)
		{
			return os << "(" << t.x << "," << t.y << "," << t.z << "," << t.w << ")";
		}


	};



	template <typename T>
	void ZERO_TUPLE(_tuple_2<T> & t)
	{
		t.x = (T)0;
		t.y = (T)0;
	}

	template <typename T>
	void ZERO_TUPLE(_tuple_3<T> & t)
	{
		t.x = (T)0;
		t.y = (T)0;
		t.z = (T)0;
	}

	template <typename T>
	void ZERO_TUPLE(_tuple_4<T> & t)
	{
		t.x = (T)0;
		t.y = (T)0;
		t.z = (T)0;
		t.w = (T)0;
	}

	} // close namespace 'math::affine'
} // close namesace 'math'

#endif