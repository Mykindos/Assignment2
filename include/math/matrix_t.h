#ifndef MATRIX_T_H
#define MATRIX_T_H

#include <stdlib.h>
#include <limits>
#include <iostream>
#include <iomanip>

#include "math/vector_t.h"

/*
 * Open namespace: math
 */
namespace math { // open namespace 'math'
/*
 * Open namespace: math::linear
 */
namespace linear { // open namespace 'math::linear'

	/*
	 * _matrix_2<F,V>		2x2 matrix class
	 *
	 * @param: 
	 *		F			element type		(default: float)
	 *		V			column storage_type (default: _tuple_2<F>)
	 */
	template <typename F = float, typename V = _tuple_2<F> >
	struct _matrix_2
	{
		typedef typename F	value_type;

		/*
		 * Attributes
		 */
		// Size
		static const size_t ROWS = 2;
		static const size_t COLS = 2;

		// Data
		V C[2];

		/*
		 * Construction
		 */
		// Default (2x2 identity matrix)
		_matrix_2()
		{
			C[0][0] = (F)0; C[1][0] = (F)0; 
			C[0][1] = (F)0; C[1][1] = (F)0; 
		}

		// Initialisation
		_matrix_2( V const & _c0, V const & _c1)
		{
			C[0] = _c0;
			C[1] = _c1;
		}

		// Copy
		_matrix_2(_matrix_2 const& m)
		{
			if (this != &m)
			{
				C[0] = m.C[0];
				C[1] = m.C[1];
			}
		}
		/*
		 * Array Access 
		 */
		// Read-only-access
		V const& operator[](size_t i) const
		{
#ifdef _DEBUG
//			assert(!(i == 0 || i == 1) && "Invalid array access operator in _matrix_2<T>");
#endif
			return C[i];
		}

		// Write-access
		V& operator[](size_t i)
		{
#ifdef _DEBUG
//			assert((i < 0 || i > 1) && "Invalid array access operator in _matrix_2<T>");
#endif
			return C[i];
		}

		/*
		 * Mathematical/ Computational operators
		 */
		// Assignment
		_matrix_2 const& operator=(_matrix_2 const& m)
		{
			if (this != &m)
			{
				C[0] = m.C[0];
				C[1] = m.C[1];
			}
			return *this;
		}

		// logical equivalence
		bool const operator==(_matrix_2 const& m) const
		{
			return ( C[0] == m.C[0] && C[1] == m.C[1]);
		}

		// logical not-equivalent
		bool const operator!=(_matrix_2 const& m) const
		{
			return !( *this == m );
		}

		// Negation
		_matrix_2 const& operator-() const
		{
			return _matrix_2( -C[0], -C[1]);
		}

		// Additive assignment
		_matrix_2 const& operator+=( _matrix_2 const& m )
		{
			C[0] += m.C[0];
			C[1] += m.C[1];
		}

		// Subtractive assignment
		_matrix_2 const& operator-=( _matrix_2 const& m )
		{
			C[0] -= m.C[0];
			C[1] -= m.C[1];
		}

		// Scalar multiplication
		_matrix_2 const& operator*=( F const a )
		{
			C[0] *= a;
			C[1] *= a;
		}

		// Multiplicative assignment
		_matrix_2 const& operator*=( _matrix_2 const& m )
		{
			_matrix_2	temp = *this;
			C[0] = temp * m.C[0];
			C[1] = temp * m.C[1];

			return *this;
		}

		// Scalar division
		_matrix_2 const& operator/=( F const a )
		{
			C[0] /= a;
			C[1] /= a;

			return *this;
		}

		// Addition
		inline _matrix_2 const operator+( _matrix_2 const& m ) const
		{
			return _matrix_2( C[0] + m.C[0],  C[1] + m.C[1] );
		}

		// Subtraction
		inline _matrix_2 const operator-( _matrix_2 const& m ) const
		{
			return _matrix_2( C[0] - m.C[0],  C[1] - m.C[1] );
		}

		// Postfix scalar multiplication
		inline _matrix_2 const operator*( F const a ) const
		{
			return _matrix_2( C[0]*a, C[1]*a );
		}

		// Postfix scalar divide
		inline _matrix_2 const operator/( F const a ) const
		{
			return _matrix_2( C[0]/a, C[1]/a );
		}

		// Prefix scalar multiplication
		template <typename U>
		friend inline _matrix_2<U> const operator*( F const a, _matrix_2<U> const& m)
		{
			return m * a;
		}

		// Postfix multiplication by a vector
		V const operator*( V const& v ) const
		{
			return ( C[0]*v.x + C[1]*v.y );
		}

		// Prefix multiplication by a vector
		template <typename U, typename W>
		friend inline W const operator*(W const& v, _matrix_2<U> const& m)
		{
			return W(inner_product(m.C[0],v), inner_product(m.C[1],v) );
		}

		// Postfix multiplication by a matrix of the same size
		_matrix_2<F> const operator*( _matrix_2<F> const& m) const
		{
			return _matrix_2( (*this) * m.C[0], (*this) * m.C[1]);
		}

		// Transpose
		template <typename U>
		friend inline _matrix_2<U> const transpose(_matrix_2<U> const& m)
		{
			return _matrix_2<U>(
					V(m.C[0][0], m.C[1][0]),
					V(m.C[0][1], m.C[1][1])
							    );
		}

		template <typename U>
		friend inline U const determinant(_matrix_2<U> const& m)
		{
			return ( m.C[0][0]*m.C[1][1] - m.C[1][0]*m.C[0][1] );
		}

		template <typename U>
		friend inline _matrix_2<U> const adjoint(_matrix_2<U> const& m)
		{
			return _matrix_2<U>( V(m.C[1][1],-m.C[0][1]), V(-m.C[1][0],m.C[0][0]) );
		}

		inline F const cofactor(size_t r, size_t c)
		{
			int k = ((r+c) % 2) ? 1 : -1;
			return k*C[c][r];
		}

		template <typename U>
		friend inline _matrix_2<U> const inverse(_matrix_2<U> const& m)
		{
			U det = determinant(m);
			if (det == 0)
			{
				TUPLE2 T(std::numeric_limits<F>::quiet_NaN(),std::numeric_limits<F>::quiet_NaN());
				return _matrix_2(T,T);
			}
			return adjoint(m) / det;
		}

		template <typename U>
		friend std::ostream& operator<<( std::ostream& os, _matrix_2<U> const& m)
		{
			os << "\n";
			os << (char)218 << std::setw(18) << ""  << (char)191 << "\n";
			os << (char)179 << std::setw(8) << m.C[0][0] << " " << std::setw(8) << m.C[1][0] << " " << (char)179 << "\n";
			os << (char)179 << std::setw(8) << m.C[0][1] << " " << std::setw(8) << m.C[1][1] << " " << (char)179 << "\n";
			os << (char)192 << std::setw(18) << ""  << (char)217 << "\n";
			return os;
		}

	};


	/*
	 * _matrix_3<F,V>		3x3 matrix class
	 *
	 * @param: 
	 *		F			element type		(default: float)
	 *		V			column storage_type (default: _tuple_3<F>)
	 */
	template <typename F = float, typename V = _tuple_3<F> >
	struct _matrix_3
	{
		typedef typename F	value_type;

		// Attributes
		V	C[3];

		static const size_t ROWS = 3;
		static const size_t COLS = 3;
		/*
		 * Construction
		 */
		// Default (3x3 identity matrix)
		_matrix_3()
		{
			C[0][0] = (F)1;
			C[1][1] = (F)1;
			C[2][2] = (F)1;
		}

		// Initialisation
		_matrix_3( V const& _c0, V const& _c1, V const& _c2)
		{
			C[0] = _c0;
			C[1] = _c1;
			C[2] = _c2;
		}

		// Copy
		_matrix_3(_matrix_3 const& m)
		{
			if (this != &m)
			{
				C[0] = m.C[0];
				C[1] = m.C[1];
				C[2] = m.C[2];
			}
		}


		/*
		 * Array Access 
		 */
		// Read-only-access
		V const& operator[](size_t i) const
		{
			return C[i];
		}

		// Write-access
		V& operator[](size_t i)
		{
			return C[i];
		}

		/*
		 * Mathematical/ Computational operators
		 */
		// Assignment
		_matrix_3 const& operator=(_matrix_3 const& m)
		{
			if (this != &m)
			{
				C[0] = m.C[0];
				C[1] = m.C[1];
				C[2] = m.C[2];
			}
			return *this;
		}

		// logical equivalence
		bool const operator==(_matrix_3 const& m) const
		{
			return ( C[0] == m.C[0] && C[1] == m.C[1] && C[2] == m.C[2]);
		}

		// logical not-equivalent
		bool const operator!=(_matrix_3 const& m) const
		{
			return !( *this == m );
		}

		// Negation
		_matrix_3 const& operator-() const
		{
			return _matrix_3( -C[0], -C[1], -C[2]);
		}

		// Additive assignment
		_matrix_3 const& operator+=( _matrix_3 const& m )
		{
			C[0] += m.C[0];
			C[1] += m.C[1];
			C[2] += m.C[2];
		}

		// Subtractive assignment
		_matrix_3 const& operator-=( _matrix_3 const& m )
		{
			C[0] -= m.C[0];
			C[1] -= m.C[1];
			C[2] -= m.C[2];
		}

		// Scalar multiplication
		_matrix_3 const& operator*=( F const a )
		{
			C[0] *= a;
			C[1] *= a;
			C[2] *= a;
		}

		// Multiplicative assignment
		_matrix_3 const& operator*=( _matrix_3 const& m )
		{
			_matrix_3	temp = *this;
			C[0] = temp * m.C[0];
			C[1] = temp * m.C[1];
			C[2] = temp * m.C[2];

			return *this;
		}

		// Scalar division
		_matrix_3 const& operator/=( F const a )
		{
			C[0] /= a;
			C[1] /= a;
			C[2] /= a;

			return *this;
		}

		// Addition
		inline _matrix_3 const operator+( _matrix_3 const& m ) const
		{
			return _matrix_3( C[0] + m.C[0],  C[1] + m.C[1],  C[2] + m.C[2] );
		}

		// Subtraction
		inline _matrix_3 const operator-( _matrix_3 const& m ) const
		{
			return _matrix_3( C[0] - m.C[0],  C[1] - m.C[1],  C[2] - m.C[2] );
		}

		// Postfix scalar multiplication
		inline _matrix_3 const operator*( F const a ) const
		{
			return _matrix_3( C[0]*a, C[1]*a, C[2]*a );
		}

		// Postfix scalar divide
		inline _matrix_3 const operator/( F const a ) const
		{
			return _matrix_3( C[0]/a, C[1]/a, C[2]/a );
		}

		// Prefix scalar multiplication
		template <typename U>
		friend inline _matrix_3<U> const operator*( F const a, _matrix_3<U> const& m)
		{
			return m * a;
		}

		// Postfix multiplication by a tuple
		inline V const operator*( V const& v ) const
		{
			return ( C[0]*v.x + C[1]*v.y + C[2]*v.z );
		}
		// Prefix multiplication by a tuple
		template <typename U, typename W>
		friend inline W const operator*(W const& v, _matrix_3<U,W> const& m)
		{
			return W(inner_product(m.C[0],v),
					 inner_product(m.C[1],v),
					 inner_product(m.C[2],v) );
		}

		// Postfix multiplication by a matrix of the same size
		inline _matrix_3<F> const operator*( _matrix_3<F> const& m) const
		{
			return _matrix_3<F>( (*this) * m.C[0], (*this) * m.C[1], (*this) * m.C[2]);
		}

		// Transpose
		template <typename U>
		friend inline _matrix_3<U> transpose(_matrix_3<U> const& m)
		{
			return _matrix_3<U>( V(m.C[0][0], m.C[1][0], m.C[2][0]),
							     V(m.C[0][1], m.C[1][1], m.C[2][1]),
							     V(m.C[0][2], m.C[1][2], m.C[2][2]) );
		}

		template <typename U>
		friend inline U const determinant(_matrix_3<U> const& m)
		{
			return inner_product(m.C[0], outer_product( m.C[1], m.C[2] ) );
		}

		_matrix_2<F> const submatrix(size_t row, size_t col) const
		{
			size_t i = 0;
			_matrix_2<F>	m;
			for (size_t c = 0; c < 3; ++c)
			{
				size_t j = 0;
				if ( c == col )
					continue;

				for (size_t r = 0; r < 3; ++r)
				{
					if ( r == row )
						continue;
					m[i][j] = C[c][r];
					j++;
				}
				i++;
			}
			return m;
		}

		template <typename U>
		friend inline _matrix_3<U> const adjoint(_matrix_3<U> const& m)
		{
			_matrix_3<U> A;
			//		A is the matrix of Cofactors C(r,c)
			//		C(r,c): (-1)^(r+c)*det(S(r,c))		S(r,c) is the submatrix formed by removing row(r) and column(c) from m
			for (size_t c = 0; c < 3; ++c)
			{
				for (size_t r = 0; r < 3; ++r)
				{
					int k = ((r + c) % 2) ? -1 : 1 ;
					A[c][r] = k * determinant( m.submatrix(r,c) );
				}
			}
			return A;
		}

		template <typename U>
		friend inline _matrix_3<U> const inverse(_matrix_3<U> const& m)
		{
			_matrix_3<U> A;
			F det = determinant(m);
			if (det == 0)
				return std::numeric_limits<F>::quiet_NaN() * _matrix_3();
			A = adjoint(m) / det ;
			return A;
		}

		template <typename U>
		friend std::ostream& operator<<( std::ostream& os, _matrix_3<U> const& m)
		{
			os << "\n";
			os << (char)218 << std::setw(27) << "" << (char)191 << "\n";
			os << (char)179 << std::setw(8)  << m.C[0][0] << " " << std::setw(8) << m.C[1][0] << " " << std::setw(8) << m.C[2][0]<< " " << (char)179 << "\n";
			os << (char)179 << std::setw(8)  << m.C[0][1] << " " << std::setw(8) << m.C[1][1] << " " << std::setw(8) << m.C[2][1]<< " " << (char)179 << "\n";
			os << (char)179 << std::setw(8)  << m.C[0][2] << " " << std::setw(8) << m.C[1][2] << " " << std::setw(8) << m.C[2][2]<< " " << (char)179 << "\n";
			os << (char)192 << std::setw(27) << "" << (char)217 << "\n";

			return os;
		}

	};

	/*
	 * _matrix_4<F,V>		4x4 matrix class
	 *
	 * @param: 
	 *		F			element type		(default: float)
	 *		V			column storage_type (default: _tuple_4<F>)
	 */
	template <typename F = float, typename V = _tuple_4<F> >
	struct _matrix_4
	{
		typedef typename F	value_type;

		// Attributes
		V	C[4];

		static const size_t ROWS = 4;
		static const size_t COLS = 4;
		/*
		 * Construction
		 */
		// Default (4x4 identity matrix)
		_matrix_4()
		{
			C[0][0] = (F)1;
			C[1][1] = (F)1;
			C[2][2] = (F)1;
			C[3][3] = (F)1;
		}

		// Initialisation
		_matrix_4( V const& _c0, V const& _c1, V const& _c2, V const& _c3)
		{
			C[0] = _c0;
			C[1] = _c1;
			C[2] = _c2;
			C[3] = _c3;
		}

		// Copy
		_matrix_4(_matrix_4 const& m)
		{
			if (this != &m)
			{
				C[0] = m.C[0];
				C[1] = m.C[1];
				C[2] = m.C[2];
				C[3] = m.C[3];
			}
		}


		/*
		 * Array Access 
		 */
		// Read-only-access
		V const& operator[](size_t i) const
		{
			return C[i];
		}

		// Write-access
		V& operator[](size_t i)
		{
			return C[i];
		}

		/*
		 * Mathematical/ Computational operators
		 */
		// Assignment
		_matrix_4 const& operator=(_matrix_4 const& m)
		{
			if (this != &m)
			{
				C[0] = m.C[0];
				C[1] = m.C[1];
				C[2] = m.C[2];
				C[3] = m.C[3];
			}
			return *this;
		}

		// logical equivalence
		bool const operator==(_matrix_4 const& m) const
		{
			return ( C[0] == m.C[0] && C[1] == m.C[1] && C[2] == m.C[2] && C[3] == m.C[3]);
		}

		// logical not-equivalent
		bool const operator!=(_matrix_4 const& m) const
		{
			return !( *this == m );
		}

		// Negation
		_matrix_4 const& operator-() const
		{
			return _matrix_4( -C[0], -C[1], -C[2], -C[3]);
		}

		// Additive assignment
		_matrix_4 const& operator+=( _matrix_4 const& m )
		{
			C[0] += m.C[0];
			C[1] += m.C[1];
			C[2] += m.C[2];
			C[3] += m.C[3];
		}

		// Subtractive assignment
		_matrix_4 const& operator-=( _matrix_4 const& m )
		{
			C[0] -= m.C[0];
			C[1] -= m.C[1];
			C[2] -= m.C[2];
			C[3] -= m.C[3];
		}

		// Scalar multiplication
		_matrix_4 const& operator*=( F const a )
		{
			C[0] *= s;
			C[1] *= s;
			C[2] *= s;
			C[3] *= s;
		}

		// Multiplicative assignment
		_matrix_4 const& operator*=( _matrix_4 const& m )
		{
			_matrix_4	temp = *this;
			C[0] = temp * m.C[0];
			C[1] = temp * m.C[1];
			C[2] = temp * m.C[2];
			C[3] = temp * m.C[3];

			return *this;
		}

		// Scalar division
		_matrix_4 const& operator/=( F const a )
		{
			C[0] /= a;
			C[1] /= a;
			C[2] /= a;
			C[3] /= a;

			return *this;
		}

		// Addition
		inline _matrix_4 const operator+( _matrix_4 const& m ) const
		{
			return _matrix_4( C[0] + m.C[0],  C[1] + m.C[1],  C[2] + m.C[2], C[3] + m.C[3] );
		}

		// Subtraction
		inline _matrix_4 const operator-( _matrix_4 const& m ) const
		{
			return _matrix_4( C[0] - m.C[0],  C[1] - m.C[1],  C[2] - m.C[2], C[3] - m.C[3] );
		}

		// Postfix scalar multiplication
		inline _matrix_4 const operator*( F const a ) const
		{
			return _matrix_4( C[0]*a, C[1]*a, C[2]*a, C[3]*a );
		}

		// Postfix scalar divide
		inline _matrix_4 const operator/( F const a ) const
		{
			return _matrix_4( C[0]/a, C[1]/a, C[2]/a, C[3]/a );
		}

		// Prefix scalar multiplication
		template <typename U>
		friend inline _matrix_4<U> const operator*( F const a, _matrix_4<U> const& m)
		{
			return m * a;
		}

		// Postfix multiplication by a vector
		inline V const operator*( V const& v ) const
		{
			return ( C[0]*v.x + C[1]*v.y + C[2]*v.z +C[3]*v.w);
		}
		// Prefix multiplication by a vector
		template <typename U, typename W>
		friend inline W const operator*(W const& v, _matrix_4<U> const& m)
		{
			return V(inner_product(m.C[0],v),
					 inner_product(m.C[1],v),
					 inner_product(m.C[2],v),
					 inner_product(m.C[3],v)
					);
		}

		// Postfix multiplication by a matrix of the same size
		inline _matrix_4 const operator*( _matrix_4 const& m) const
		{
			return _matrix_4( (*this) * m.C[0], (*this) * m.C[1], (*this) * m.C[2], (*this) * m.C[3] );
		}

		// Transpose
		template <typename U>
		friend inline _matrix_4<U> transpose(_matrix_4<U> const& m)
		{
			return _matrix_4<U>( V(m.C[0][0], m.C[1][0], m.C[2][0], m.C[3][0]),
							     V(m.C[0][1], m.C[1][1], m.C[2][1], m.C[3][1]),
							     V(m.C[0][2], m.C[1][2], m.C[2][2], m.C[3][2]),
							     V(m.C[0][3], m.C[1][3], m.C[2][3], m.C[3][3]) );
		}
		template <typename U>
		friend inline U const determinant(_matrix_4<U> const& m)
		{
		//	C_ij = (-1)^(i+j)det(S_ij)
			return	determinant(m.submatrix(0,0)) -
					determinant(m.submatrix(0,1)) +
					determinant(m.submatrix(0,2)) -
					determinant(m.submatrix(0,3));
		}

		_matrix_3<F> const submatrix(size_t row, size_t col) const
		{
			size_t i = 0;
			_matrix_3<F>	m;
			for (size_t c = 0; c < 4; ++c)
			{
				size_t j = 0;
				if ( c == col )
					continue;

				for (size_t r = 0; r < 4; ++r)
				{
					if ( r == row )
						continue;
					m[i][j] = C[c][r];
					j++;
				}
				i++;
			}
			return m;
		}

		template <typename U>
		friend inline _matrix_4<U> const adjoint(_matrix_4<U> const& m)
		{
			_matrix_4 A;
			//		A is the matrix of Cofactors C(r,c)
			//		C(r,c): (-1)^(r+c)*det(S(r,c))		S(r,c) is the submatrix formed by removing row(r) and column(c) from m
			for (size_t c = 0; c < 4; ++c)
			{
				for (size_t r = 0; r < 4; ++r)
				{
					int k = ((r + c) % 2) ? -1 : 1 ;
					A[c][r] = k * determinant( m.submatrix(r,c) );
				}
			}
			return A;
		}

		template <typename U>
		friend inline _matrix_4<U> const inverse(_matrix_4<U> const& m)
		{
			F det = determinant(m);
			if (det == 0)
				return std::numeric_limits<F>::quiet_NaN() * _matrix_4();
			return adjoint(m) / det ;
		}

		template <typename U>
		friend std::ostream& operator<< ( std::ostream& os, _matrix_4<U> const& m)
		{
			os << "\n";
			os << (char)218 << std::setw(36) << "" << (char)191 << "\n";
			os << (char)179 << std::setw(8) << m.C[0][0] << " " << std::setw(8) << m.C[1][0] << " " << std::setw(8) << m.C[2][0]<< " " << std::setw(8) << m.C[3][0]<< " " << (char)179 << "\n";
			os << (char)179 << std::setw(8) << m.C[0][1] << " " << std::setw(8) << m.C[1][1] << " " << std::setw(8) << m.C[2][1]<< " " << std::setw(8) << m.C[3][1]<< " " << (char)179 << "\n";
			os << (char)179 << std::setw(8) << m.C[0][2] << " " << std::setw(8) << m.C[1][2] << " " << std::setw(8) << m.C[2][2]<< " " << std::setw(8) << m.C[3][2]<< " " << (char)179 << "\n";
			os << (char)179 << std::setw(8) << m.C[0][3] << " " << std::setw(8) << m.C[1][3] << " " << std::setw(8) << m.C[2][3]<< " " << std::setw(8) << m.C[3][3]<< " " << (char)179 << "\n";
			os << (char)192 << std::setw(36) << ""  << (char)217 << "\n";

			return os;
		}

	};


	} // close namespace 'math::linear'
} // close namesace 'math'

#endif