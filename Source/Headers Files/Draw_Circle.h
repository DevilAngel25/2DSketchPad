#pragma once
#include <string>
#include <math.h>
#include "ScanLine.h"
#include "Edge.h"
#include "Draw_Line.h"

//class to handle drawing circles
class Draw_Circle
{
	public:
		Draw_Circle(void);
		Draw_Circle(HDC& bdc, Edge e0, COLORREF bc, COLORREF fc, bool fill);
		Draw_Circle(const Draw_Circle& m);
		~Draw_Circle(void);

		int GetBR(void) const;
		int GetBG(void) const;
		int GetBB(void) const;

		int GetFR(void) const;
		int GetFG(void) const;
		int GetFB(void) const;

		void SetPOne(int, int);
		void SetPTwo(int, int);

		Draw_Circle& operator= (const Draw_Circle &rhs);


	private:
		Edge _e0, _e1;
		Vector2D _v0, _v1;

		int _x0, _y0, _x1, _y1, _r;
		int _x, _y;

		int _dx, _dy, _d;

		int _BorR, _BorG, _BorB;
		int _FillR, _FillG, _FillB;
		bool _Fill;

		void Init(Edge e0, COLORREF bc, COLORREF fc, bool fill);
		void Copy(const Draw_Circle& m);
		
};