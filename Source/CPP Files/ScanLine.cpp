#include "StdAfx.h"
#include "ScanLine.h"

// Constructors

ScanLine::ScanLine(void)
{
	Init(0, 0, 0, 0, 0);
}

ScanLine::ScanLine(HDC& bdc, int x0, int y0, int x1, int y1, COLORREF fc)
{
	Init(x0, y0, x1, y1, fc);

	//simple rectangle filling
	// take one corner and fill until the other corner is reached.
	if(x0 < x1 && y0 < y1) //fill in one quadrant.
	{
		_xMin = x0 + 1;
		_yMin = y0 + 1; 
		_xMax = x1;
		_yMax = y1;

		_y = _yMin;
		while ( _y < _yMax )
		{
			_x = _xMin;
			while ( _x < _xMax )
			{
				SetPixel(bdc, _x, _y, RGB(_FillR, _FillG, _FillB));
				_x = _x + 1;
			}
			_y = _y + 1;
		}
	}
	else if(x0 < x1 && y1 < y0) //fill in the second quadrant.
	{
		_xMin = x0 + 1;
		_yMin = y1 + 1; 
		_xMax = x1;
		_yMax = y0;

		_y = _yMin;
		while ( _y < _yMax )
		{
			_x = _xMin;
			while ( _x < _xMax )
			{
				SetPixel(bdc, _x, _y, RGB(_FillR, _FillG, _FillB));
				_x = _x + 1;
			}
			_y = _y + 1;
		}
	}
	else if(x1 < x0 && y0 < y1) // third quadrant.
	{
		_xMin = x1 + 1;
		_yMin = y0 + 1; 
		_xMax = x0;
		_yMax = y1;

		_y = _yMin;
		while ( _y < _yMax )
		{
			_x = _xMin;
			while ( _x < _xMax )
			{
				SetPixel(bdc, _x, _y, RGB(_FillR, _FillG, _FillB));
				_x = _x + 1;
			}
			_y = _y + 1;
		}
	}
	else if(x1 < x0 && y1 < y0) // and fourth
	{
		_xMin = x1 + 1;
		_yMin = y1 + 1; 
		_xMax = x0;
		_yMax = y0;

		_y = _yMin;
		while ( _y < _yMax )
		{
			_x = _xMin;
			while ( _x < _xMax )
			{
				SetPixel(bdc, _x, _y, RGB(_FillR, _FillG, _FillB));
				_x = _x + 1;
			}
			_y = _y + 1;
		}
	}
}

ScanLine::ScanLine(const ScanLine& p)
{
	Copy(p);
}

ScanLine::~ScanLine(void)
{
}

// Accessors and mutators


// get RGB
int ScanLine::GetFR() const
{
	return _FillR;
}

int ScanLine::GetFG() const
{
	return _FillG;
}

int ScanLine::GetFB() const
{
	return _FillB;
}

// Operator overloads

ScanLine& ScanLine::operator=(const ScanLine &rhs)
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

void ScanLine::Init(int x0, int y0, int x1, int y1, COLORREF fc)
{

	_FillR = GetRValue(fc);
	_FillG = GetGValue(fc);
	_FillB = GetBValue(fc);
}

void ScanLine::Copy(const ScanLine& p)
{

	_FillR = p.GetFR();
	_FillG = p.GetFG();
	_FillB = p.GetFB();

}
