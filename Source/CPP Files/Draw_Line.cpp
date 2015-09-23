#include "StdAfx.h"
#include "Draw_Line.h"

// Constructors

Draw_Line::Draw_Line(void)
{
	Init(_e0, 0);
}

Draw_Line::Draw_Line(HDC& bdc, Edge e0, COLORREF bc)
{
	//Init default values
	Init(e0, bc);

	//Init other vars
	_dx = abs(_x1 - _x0);
	_dy = abs(_y1 - _y0);
	_twoDy = _dy << 1;
	_twoDx = _dx << 1;
	_x = _x0;
	_y = _y0;

	if (_dy <= _dx) //if drawing in four of eight octants, draw a line from on vector to the next.
	{
		_d = _dx - _twoDy;

		for(_x = _x0; _x <= _x1; _x++)
		{
			SetPixel(bdc, _x, _y, RGB(_BorR, _BorG, _BorB)); //set the pixel coords and color
			if(_d < 0)
			{
				_d += _twoDx;
				if(_y0 <= _y1)
				{
					_y++;
				}
				else
				{
					_y--;
				}
			}
			_d -= _twoDy;
		}

		for(_x = _x0; _x > _x1; _x--)
		{
			SetPixel(bdc, _x, _y, RGB(_BorR, _BorG, _BorB));
			if(_d < 0)
			{
				_d += _twoDx;
				if(_y0 <= _y1)
				{
					_y++;
				}
				else
				{
					_y--;
				}
			}
			_d -= _twoDy;
		}
	}
	else if (_dy > _dx)
	{
		_d = _dy - _twoDx;

		for(_y = _y0; _y <= _y1; _y++)
		{
			SetPixel(bdc, _x, _y, RGB(_BorR, _BorG, _BorB));
			if(_d < 0)
			{
				_d += _twoDy;
				if(_x0 <= _x1)
				{
					_x++;
				}
				else
				{
					_x--;
				}
			}
			_d -= _twoDx;
		}

		for(_y = _y0; _y > _y1; _y--)
		{
			SetPixel(bdc, _x, _y, RGB(_BorR, _BorG, _BorB));
			if(_d < 0)
			{
				_d += _twoDy;
				if(_x0 <= _x1)
				{
					_x++;
				}
				else
				{
					_x--;
				}
			}
			_d -= _twoDx;
		}
	}
}

Draw_Line::Draw_Line(const Draw_Line& p)
{
	Copy(p);
}

Draw_Line::~Draw_Line(void)
{
}

// get RGB
int Draw_Line::GetBR() const
{
	return _BorR;
}

int Draw_Line::GetBG() const
{
	return _BorG;
}

int Draw_Line::GetBB() const
{
	return _BorB;
}

// Operator overloads

Draw_Line& Draw_Line::operator=(const Draw_Line &rhs)
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
void Draw_Line::Init(Edge e0, COLORREF bc)
{
	_e0 = e0;
	_v0 = e0.GetV0();
	_v1 = e0.GetV1();

	_x0 = _v0.GetX();
	_y0 = _v0.GetY();

	_x1 = _v1.GetX();
	_y1 = _v1.GetY();

	_BorR = GetRValue(bc);
	_BorG = GetGValue(bc);
	_BorB = GetBValue(bc);
}

void Draw_Line::Copy(const Draw_Line& p)
{
	_BorR = p.GetBR();
	_BorG = p.GetBG();
	_BorB = p.GetBB();
}
