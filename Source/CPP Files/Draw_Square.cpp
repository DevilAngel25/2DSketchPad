#include "StdAfx.h"
#include "Draw_Square.h"

// Constructors

Draw_Square::Draw_Square(void)
{
	Init(_e0, 0, 0, 0);
}

Draw_Square::Draw_Square(HDC& bdc, Edge e0, COLORREF bc, COLORREF fc, bool fill)
{
	Init(e0, bc, fc, fill);

	_t = _y1;
	_b = _y0;
	_r = _x1;
	_l = _x0;

	//Set vectors and put them into edges to be drawn.
	_v0.SetX(_r), _v0.SetY(_b);
	_v1.SetX(_l), _v1.SetY(_b);
	_e0.SetV0(_v0), _e0.SetV1(_v1);

	Draw_Line(bdc, _e0, bc); //edge 1


	_v0.SetX(_r), _v0.SetY(_b);
	_v1.SetX(_r), _v1.SetY(_t);
	_e0.SetV0(_v0), _e0.SetV1(_v1);

	Draw_Line(bdc, _e0, bc); //edge 2


	_v0.SetX(_r), _v0.SetY(_t);
	_v1.SetX(_l), _v1.SetY(_t);
	_e0.SetV0(_v0), _e0.SetV1(_v1);

	Draw_Line(bdc, _e0, bc); //ect...


	_v0.SetX(_l), _v0.SetY(_t);
	_v1.SetX(_l), _v1.SetY(_b);
	_e0.SetV0(_v0), _e0.SetV1(_v1);

	Draw_Line(bdc, _e0, bc);

	if(fill)
	{
		ScanLine(bdc, _l, _b, _r, _t, fc); //if the shape is filled, implement scanline.
	}
}

Draw_Square::Draw_Square(const Draw_Square& p)
{
	Copy(p);
}

Draw_Square::~Draw_Square(void)
{
}

// Accessors and mutators

// get Border RGB
int Draw_Square::GetBR() const
{
	return _BorR;
}

int Draw_Square::GetBG() const
{
	return _BorG;
}

int Draw_Square::GetBB() const
{
	return _BorB;
}

// get Fill RGB
int Draw_Square::GetFR() const
{
	return _FillR;
}

int Draw_Square::GetFG() const
{
	return _FillG;
}

int Draw_Square::GetFB() const
{
	return _FillB;
}

// Operator overloads

Draw_Square& Draw_Square::operator=(const Draw_Square &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}


// Private methods

void Draw_Square::Init(Edge e0, COLORREF bc, COLORREF fc, bool fill)
{
	//set edge
	_e0 = e0;

	//set vectors
	_v0 = e0.GetV0();
	_v1 = e0.GetV1();

	//set coords
	_x0 = _v0.GetX();
	_y0 = _v0.GetY();

	_x1 = _v1.GetX();
	_y1 = _v1.GetY();

	//set RGB val
	_BorR = GetRValue(bc);
	_BorG = GetGValue(bc);
	_BorB = GetBValue(bc);

	_Fill = fill;

	if(fill)
	{
		_FillR = GetRValue(fc);
		_FillG = GetGValue(fc);
		_FillB = GetBValue(fc);
	}
}

void Draw_Square::Copy(const Draw_Square& p)
{
	_BorR = p.GetBR();
	_BorG = p.GetBG();
	_BorB = p.GetBB();

	if(_Fill)
	{
		_FillR = p.GetFR();
		_FillG = p.GetFG();
		_FillB = p.GetFB();
	}
}
