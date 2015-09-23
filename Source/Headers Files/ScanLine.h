#pragma once
#include <string>

//implement a basic and crude scanline function.
class ScanLine
{
	public:
		ScanLine(void);
		ScanLine(HDC& bdc, int x0, int y0, int x1, int y1, COLORREF fc); //passing in device handle, coords and color.
		ScanLine(const ScanLine& m);
		~ScanLine(void);

		int GetPOne(int) const;
		int GetPTwo(int) const;

		int GetFR(void) const;
		int GetFG(void) const;
		int GetFB(void) const;

		void SetPOne(int, int);
		void SetPTwo(int, int);

		ScanLine& operator= (const ScanLine &rhs);

	private:
		int _x, _y;
		int _xMin, _xMax, _yMin, _yMax;
		int _FillR, _FillG, _FillB;

		void Init(int x0, int y0, int x1, int y1, COLORREF fc);
		void Copy(const ScanLine& m);
		
};