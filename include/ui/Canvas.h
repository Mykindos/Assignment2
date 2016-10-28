/* ********************************************************************************* *
 * *  File: Canvas.h                                                               * *
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

#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <memory>

#include "ui\Texture.h"
#include "math\Geometry.h"

#define LRGB(r,g,b)          ((unsigned long)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))



class Canvas
{
	public:
		Canvas(){}
		virtual ~Canvas(){}

		virtual bool IsActive() = 0;
		virtual void Terminate() = 0;

		virtual void Display() = 0;
		virtual void Clear(int r, int g, int b) = 0;

		virtual void Resize() = 0;
		virtual void Size(unsigned short x, unsigned short y) = 0;

		virtual void DrawLine(Segment const & s, unsigned long line_rgb = LRGB(0, 0, 255), int width = 1) = 0;
		virtual void DrawPoly(Polytype const & p, unsigned long colour = LRGB(0, 0, 0), unsigned int width = 1) = 0;
		virtual void DrawFilledPoly(Polytype const & p, unsigned long fill_colour = LRGB(0, 0, 0), unsigned long line_colour = LRGB(0, 0, 0), unsigned int width = 1) = 0;
		virtual void DrawTexture(Texture const & t, POINT2 pos, POINT2 s = { 0, 0 }) = 0;

		virtual void Write(int x, int y, std::string text, unsigned long colour = LRGB(0,0,0)) = 0;
};


#endif