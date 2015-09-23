#pragma once
#include <string>

//class to old a 2d vector x,y
class Vector2D
{
	public:
		Vector2D(void);
		Vector2D(int x, int y);
		Vector2D(const Vector2D& v);
		~Vector2D(void);

		int GetX(void) const;
		int GetY(void) const;

		void SetX(int x);
		void SetY(int y);

	private:
		int _x, _y;

		void Init(int x, int y);
		void Copy(const Vector2D& v);
		
};
