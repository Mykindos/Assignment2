#ifndef QUATERNION_T_H
#define QUATERNION_T_H

#include <limits>

#include "math/calc.h"
#include "math/linear.h"

/*
 * Open namespace: math
 */
namespace math {

	/*
	 * Open namespace: math::linear
	 */
	namespace linear {

	/*
	 * _quaternion<T>			4 element quaternion class
	 *
	 * @param: 
	 *		T			element type
	 */
	template <typename T = float>
	struct _quaternion
	{
		typedef T				value_type;
		typedef _vector_3<T>	vector_type;

		// Attributes
		value_type		r;	// real part
		vector_type		u;	// imaginary part

		/*
		 * Construction
		 */

		// Default
		_quaternion()
			: r((T)1), u((T)0,(T)0,(T)0)
		{}


		// Initialisation
		_quaternion(
				value_type const _r,
				_vector_3<T> const& _u )
			: r(_r), u(_u)
		{}

		_quaternion(
				T const _r,
				T const _u1,
				T const _u2,
				T const _u3 )
			: r(_r), u(_u1,_u2,_u3)
		{}

		// Copy
		_quaternion( _quaternion const& q )
		{
			if (this != &q)
			{
				r = q.r;
				u = q.u;
			}
		}


		/*
		 * Assignment
		 */
		_quaternion const& operator=( _quaternion const& q )
		{
			if (this != &q)
			{
				r = q.r;
				u = q.u;
			}
			return *this;
		}

		/*
		 * Logical operators
		 */

		bool const operator==( _quaternion const& q) const
		{
			return ( r == q.r ) && ( u == q.u ) ;
		}

		bool const operator!=( _quaternion const& q) const
		{
			return ! ( *this == q ) ;
		}

		/*
		 * Mathematical/ computational operators
		 */

		// Negation
		inline _quaternion const operator-() const
		{
			return _quaternion( -r, -u );
		}

		// Additive assignment
		_quaternion const& operator+=( _quaternion const& q)
		{
			r += q.r;
			u += q.u;

			return *this;
		}

		// Subtractive assignment
		_quaternion const& operator-=( _quaternion const& q)
		{
			r -= q.r;
			u -= q.u;

			return *this;
		}

		// Multiplicative assignment
		_quaternion const& operator*=( _quaternion const& q)
		{
			r = r*q.r - inner_product(u,q.u);
			float _x = u.x,
				  _y = u.y,
				  _z = u.z;
			u.x = _y*q.u.z - _z*q.u.y + r*q.u.x + _x*q.r;
			u.y = _z*q.u.x - _x*q.u.z + r*q.u.y + _y*q.r;
			u.z = _x*q.u.y - _y*q.u.x + r*q.u.z + _z*q.r;

			return *this;
		}

		// Scalar multiplication
		_quaternion const& operator*=( T const s )
		{
			r *= s;
			u *= s;

			return *this;
		}

		// Scalar division
		_quaternion const& operator/=( T const s )
		{
			if ( s == 0 )
			{
				r = u.x = u.y = u.z = std::numeric_limits<T>::quiet_NaN();
				return *this;
			}
			r /= s;
			u /= s;
			return *this;
		}

		// Addition
		inline _quaternion const operator+( _quaternion const& q ) const
		{
			return _quaternion( r + q.r, u + q.y );
		}

		// Subtraction
		inline _quaternion const operator-( _quaternion const& q ) const
		{
			return _quaternion( r - q.r, u - q.u );
		}

		// Quaternion multiplication
		inline _quaternion const operator*( _quaternion const &q) const
		{
			return _quaternion(
				r*q.r - inner_product(u,q.u),
				u.y*q.u.z - u.z*q.u.y + r*q.u.x + u.x*q.r,
				u.z*q.u.x - u.x*q.u.z + r*q.u.y + u.y*q.r,
				u.x*q.u.y - u.y*q.u.x + r*q.u.z + u.z*q.r
				);
		}

		// Quaternion division
		inline _quaternion const operator/( _quaternion const &q) const	
		{
			_quaternion p(q.r,-q.u); 
			p /= p.length_sqr(); 
 			return *this * p;
		}

		// Postfix scalar multiplication
		inline _quaternion const operator*( T const s ) const
		{
			return _quaternion( r*s, u*s );
		}

		// Prefix scalar multiplication
		template <typename U>
		friend inline _quaternion<U> const operator*( T const s, _quaternion<U> const& q)
		{
			return q * s;
		}

		// Postfix scalar division
		inline _quaternion const operator/( T const s ) const
		{
			if ( s == 0 )
			{
				r = u.x = u.y = u.z = std::numeric_limits<T>::quiet_NaN();
				return *this;
			}
			return _quaternion( r/s, u/a );
		}

		// Prefix vector multiplication
		template <typename U>
		friend inline _quaternion const operator*( vector_type const& v, _quaternion<U> const& q)
		{
			return _quaternion(T(0),v)*q;
		}

		// Magnitude
		inline T const length() const
		{
			return ::sqrtf( (float)length_sqr() );
		}

		inline T const length_sqr() const
		{
			return T( r*r + inner_product(u,u) );
		}

		template <typename U>
		friend inline _quaternion<U>& normalise(_quaternion<U> &q)
		{
			q /= q.length();
			return q;
		}

		template <typename U>
		friend inline _quaternion<U>& conjugate(_quaternion<U> &q)
		{
			q.u *= U(-1);
			return q;
		}

		template <typename U>
		friend inline T const& inner_product( _quaternion<U> const& q1, _quaternion<U> const& q2)
		{
			return T( q1.r*q2.r + inner_product(q1.u,q2.u) );
		}

		template <typename U>
		friend inline _quaternion<U> lerp( _quaternion<U> const &q1, _quaternion<U> const &q2, T const t)
		{
			_quaternion q(q1*(1-t) + q2*t);
			normalise(q);
			return q;
		}

		template <typename U>
		friend _quaternion<U> slerp( _quaternion<U> const &q1, _quaternion<U> const &q2, T const t)
		{
			_quaternion q3;
			T d = inner_product(q1,q2);
			if ( d < 0 )
			{
				d = -d;
				q3 = -q2;
			}
			else
				q3 = q2;
			if ( d < 0.95f )
			{
				float theta = ::acosf(d);
				return (q1*::sinf(theta*(1-t)) + q3*::sinf(theta*t))/::sinf(theta);
			}
			else
				return lerp(q1,q3,t);
		}

		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, _quaternion<U> const& q)
		{
			return os << "(" << q.r << "," << q.u.x << "," << q.u.y << "," << q.u.z << ")";
		}



	};

	typedef __declspec( align(16) ) _quaternion<float> QUATERNION;

	} // close namespace 'math::linear'
} // close namesace 'math'

#endif