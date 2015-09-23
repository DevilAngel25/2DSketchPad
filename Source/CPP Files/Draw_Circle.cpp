#include "StdAfx.h"
#include "Draw_Circle.h"

// Constructors

Draw_Circle::Draw_Circle(void)
{
	Init(_e0, 0, 0, 0);
}

Draw_Circle::Draw_Circle(HDC& bdc, Edge e0, COLORREF bc, COLORREF fc, bool fill)
{
	Init(e0, bc, fc, fill);

	_dx = abs(_x1 - _x0);
	_dy = abs(_y1 - _y0);

	_r = 10;
	_x = 0;

	_d = 3 - (2 * _r);

	//Draw the border of a circle using a modified (bresenham line) circle algorithm 
	if (_dy <= _dx)
	{

		if(_x0 > _x1)
		{
			_r = _x0 - _x1;
		}
		else
		{
			_r = _x1 - _x0;
		}

		_y = _r;

		
		//set outer pixles
		SetPixel(bdc, _x0, _y0 + _r, RGB(_BorR, _BorG, _BorB));
		SetPixel(bdc, _x0, _y0 - _r, RGB(_BorR, _BorG, _BorB));
		SetPixel(bdc, _x0 + _r, _y0, RGB(_BorR, _BorG, _BorB));
		SetPixel(bdc, _x0 - _r, _y0, RGB(_BorR, _BorG, _BorB));
		
		if(fill)// if fill, draw lines across the circle to fill it in.
		{
			_v0.SetX(_x0 + (_r - 1)), _v0.SetY(_y0);
			_v1.SetX(_x0 - _r), _v1.SetY(_y0);
			_e0.SetV0(_v0), _e0.SetV1(_v1);
			Draw_Line(bdc, _e0, fc);
		}
 
		while(_x < _y)
		{
			_x++;
			if(_d < 0) 
			{
				_d = _d + (4 * _x) + 6;
			}
			else
			{
				_y--;
				_d = _d + (4 * (_x - _y)) + 10;
			}
				//draw the main part of the circle
				SetPixel(bdc, _x0 + _x, _y0 + _y, RGB(_BorR, _BorG, _BorB));
				SetPixel(bdc, _x0 - _x, _y0 + _y, RGB(_BorR, _BorG, _BorB));
				SetPixel(bdc, _x0 + _x, _y0 - _y, RGB(_BorR, _BorG, _BorB));
				SetPixel(bdc, _x0 - _x, _y0 - _y, RGB(_BorR, _BorG, _BorB));
				SetPixel(bdc, _x0 + _y, _y0 + _x, RGB(_BorR, _BorG, _BorB));
				SetPixel(bdc, _x0 - _y, _y0 + _x, RGB(_BorR, _BorG, _BorB));
				SetPixel(bdc, _x0 + _y, _y0 - _x, RGB(_BorR, _BorG, _BorB));
				SetPixel(bdc, _x0 - _y, _y0 - _x, RGB(_BorR, _BorG, _BorB));
			
			if(fill) //fill color
			{
				_v0.SetX(_x0 + _x), _v0.SetY(_y0 + (_y - 1));
				_v1.SetX(_x0 - (_x + 1)), _v1.SetY(_y0 + (_y - 1));
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);

				_v0.SetX(_x0 + _x), _v0.SetY(_y0 - (_y - 1));
				_v1.SetX(_x0 - (_x + 1)), _v1.SetY(_y0 - (_y - 1));
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);

				_v0.SetX(_x0 + (_y - 1)), _v0.SetY(_y0 + _x);
				_v1.SetX(_x0 - _y), _v1.SetY(_y0 + _x);
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);

				_v0.SetX(_x0 + (_y - 1)), _v0.SetY(_y0 - _x);
				_v1.SetX(_x0 - _y), _v1.SetY(_y0 - _x);
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);
			}
		}
	}
	else if (_dy > _dx)
	{
		if(_y0 > _y1)
		{
			_r = _y0 - _y1;
		}
		else
		{
			_r = _y1 - _y0;
		}

		_y = _r;

		
			SetPixel(bdc, _x0, _y0 + _r, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0, _y0 - _r, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 + _r, _y0, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 - _r, _y0, RGB(_BorR, _BorG, _BorB));

		if(fill)
		{
			_v0.SetX(_x0 + (_r - 1)), _v0.SetY(_y0);
			_v1.SetX(_x0 - _r), _v1.SetY(_y0);
			_e0.SetV0(_v0), _e0.SetV1(_v1);
			Draw_Line(bdc, _e0, fc);
		}

		while(_x < _y)
		{
			_x++;
			if(_d < 0) 
			{
				_d = _d + (4 * _x) + 6;
			}
			else
			{
				_y--;
				_d = _d + (4 * (_x - _y)) + 10;
			}

			SetPixel(bdc, _x0 + _x, _y0 + _y, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 - _x, _y0 + _y, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 + _x, _y0 - _y, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 - _x, _y0 - _y, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 + _y, _y0 + _x, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 - _y, _y0 + _x, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 + _y, _y0 - _x, RGB(_BorR, _BorG, _BorB));
			SetPixel(bdc, _x0 - _y, _y0 - _x, RGB(_BorR, _BorG, _BorB));

			if(fill)
			{
				_v0.SetX(_x0 + _x), _v0.SetY(_y0 + (_y - 1));
				_v1.SetX(_x0 - (_x + 1)), _v1.SetY(_y0 + (_y - 1));
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);

				_v0.SetX(_x0 + _x), _v0.SetY(_y0 - (_y - 1));
				_v1.SetX(_x0 - (_x + 1)), _v1.SetY(_y0 - (_y - 1));
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);

				_v0.SetX(_x0 + (_y - 1)), _v0.SetY(_y0 + _x);
				_v1.SetX(_x0 - _y), _v1.SetY(_y0 + _x);
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);

				_v0.SetX(_x0 + (_y - 1)), _v0.SetY(_y0 - _x);
				_v1.SetX(_x0 - _y), _v1.SetY(_y0 - _x);
				_e0.SetV0(_v0), _e0.SetV1(_v1);
				Draw_Line(bdc, _e0, fc);
			}
		}
	}
}

Draw_Circle::Draw_Circle(const Draw_Circle& p)
{
	Copy(p);
}

Draw_Circle::~Draw_Circle(void)
{
}

// Accessors and mutators

// get Border RGB
int Draw_Circle::GetBR() const
{
	return _BorR;
}

int Draw_Circle::GetBG() const
{
	return _BorG;
}

int Draw_Circle::GetBB() const
{
	return _BorB;
}

// get Fill RGB
int Draw_Circle::GetFR() const
{
	return _FillR;
}

int Draw_Circle::GetFG() const
{
	return _FillG;
}

int Draw_Circle::GetFB() const
{
	return _FillB;
}

// Operator overloads

Draw_Circle& Draw_Circle::operator=(const Draw_Circle &rhs)
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

void Draw_Circle::Init(Edge e0, COLORREF bc, COLORREF fc, bool fill)
{
	//Set Default Edge Values
	_e0 = e0;

	_v0 = _e0.GetV0();
	_v1 = _e0.GetV1();

	_x0 = _v0.GetX();
	_y0 = _v0.GetY();
	_x1 = _v1.GetX();
	_y1 = _v1.GetY();

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

void Draw_Circle::Copy(const Draw_Circle& p)
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
