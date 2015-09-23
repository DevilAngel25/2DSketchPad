#include "stdAfx.h"
#include "Vector2D.h"

// Constructors
Vector2D::Vector2D(void)
{
	Init(0, 0);
}

Vector2D::Vector2D(int x, int y)
{
	Init(x, y);
}

Vector2D::Vector2D(const Vector2D& v)
{
	Copy(v);
}

Vector2D::~Vector2D(void)
{
}

// Accessors and mutators

//Get coords
int Vector2D::GetX(void) const
{
	return _x;
}

int Vector2D::GetY(void) const
{
	return _y;
}

//Set coords
void Vector2D::SetX(int x)
{
	_x = x;
}

void Vector2D::SetY(int y)
{
	_y = y;
}

// Private methods
void Vector2D::Init(int x, int y)
{
	_x = x;
	_y = y;
}

void Vector2D::Copy(const Vector2D& v)
{
	_x = v.GetX();
	_y = v.GetY();
}