#pragma once
#include <string>
#include "Edge.h"
#include "Vector2D.h"

//class to handle drawing lines using bresenham line algorithm.
class Draw_Line
{
	public:
		Draw_Line(void);
		Draw_Line(HDC& bdc, Edge e0, COLORREF bc);
		Draw_Line(const Draw_Line& m);
		~Draw_Line(void);

		int GetBR(void) const;
		int GetBG(void) const;
		int GetBB(void) const;

		Draw_Line& operator= (const Draw_Line &rhs);

	private:
		Edge _e0;
		Vector2D _v0, _v1;

		int _dx, _dy, _d;
		int _twoDy, _twoDx;
		int _x0, _x1, _y0, _y1, _x, _y;

		int _BorR, _BorG, _BorB;

		void Init(Edge e0, COLORREF bc);
		void Copy(const Draw_Line& m);
		
};