#pragma once
#include <string>

#include "Draw_Line.h"
#include "ScanLine.h"
#include "Edge.h"
#include "Vector2D.h"

//create a class to handle drawing squares.
class Draw_Square
{
	public:
		Draw_Square(void);
		Draw_Square(HDC& bdc, Edge e0, COLORREF bc, COLORREF fc, bool fill);
		Draw_Square(const Draw_Square& m);
		~Draw_Square(void);

		int GetBR(void) const;
		int GetBG(void) const;
		int GetBB(void) const;

		int GetFR(void) const;
		int GetFG(void) const;
		int GetFB(void) const;

		Draw_Square& operator= (const Draw_Square &rhs);

	private:
		Edge _e0;
		Vector2D _v0, _v1;
		int _x0, _y0, _x1, _y1;
		int _b, _t, _l, _r;
		int _BorR, _BorG, _BorB;
		int _FillR, _FillG, _FillB;
		bool _Fill;

		void Init(Edge e0, COLORREF bc, COLORREF fc, bool fill);
		void Copy(const Draw_Square& m);
		
};