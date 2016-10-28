/* ********************************************************************************* *
 * *  File: Geometry.h                                                             * *
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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>
#include "math\math_t.h"

using namespace math::affine;
using namespace math::linear;

class Segment
{
	protected:

		POINT2		p, q;	// end points of segment
		VECTOR2	n;		// normal vector of the wall

	public:

		Segment(POINT2 const & _p, POINT2 const & _q, VECTOR2 const & _n)
			: p(_p),
			q(_q),
			n(normalise(_n))
		{}

		VECTOR2				direction()	const	{ return normalise(q - p); }
		VECTOR2 const &		normal() const		{ return n; }
		POINT2 const &		start()		const { return p; }
		POINT2 const &		end()		const { return q; }
		float				length()	const { return (q - p).length(); }

};

enum class POLYGON_TYPE
{
	CIRCLE = 1,
	RECTANGLE,
	TRIANGLE
};

class Polytype
{
	protected:
		POLYGON_TYPE		type_;

		/*
		 * Construction only by derived types
		 */
		explicit Polytype(POLYGON_TYPE _t)
			: type_(_t)
		{}

	public:
		virtual ~Polytype(){}
		POLYGON_TYPE	type() const	{ return type_; }
};




class Circle : public Polytype
{
	protected:

		POINT2		p;		// origin
		float		r;		// radius

	public:

		Circle(POINT2 const & _p, double _r = 1.0)
			: Polytype(POLYGON_TYPE::CIRCLE),
			  p(_p),
			  r((float)_r)
		{}

		float const &		radius()	const { return r; }
		POINT2 const &		origin()	const { return p; }

		void position(POINT2 const & dp)	{ p = dp; }
		void scale(float const & dr)	{ r = dr; }
};


class Rect : public Polytype
{
	protected:
		POINT2		ul,
					br;

	public:

		Rect(POINT2 const & _ul, POINT2 const & _br)
			: Polytype(POLYGON_TYPE::RECTANGLE),
			  ul(_ul),
			  br(_br)
		{}

		POINT2 centre() const	{ return (ul + br) / 2.0f; }

		POINT2 const & start() const	{ return ul; }
		POINT2 const & end() const		{ return br; }

};

class Triangle : public Polytype
{
protected:
	POINT2  v[3];

public:
	Triangle(POINT2 v0, POINT2 v1, POINT2 v2)
		: Polytype(POLYGON_TYPE::TRIANGLE)
	{
		v[0] = v0;
		v[1] = v1;
		v[2] = v2;
	}

		POINT2 const & vertex(size_t i) const { return v[i % 3]; }
		POINT2 & vertex(size_t i) { return v[i % 3]; }

};

/*
 * Consider adding functionality to test for collisions between Geometry objects
 */



#endif