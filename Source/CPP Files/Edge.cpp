#include "stdAfx.h"
#include "Edge.h"


// Constructors
Edge::Edge(void)
{
	Init(_v0, _v1);
}

Edge::Edge(Vector2D v0, Vector2D v1)
{
	Init(v0, v1);
}

Edge::Edge(const Edge& e)
{
	Copy(e);
}

Edge::~Edge()
{
}

// Accessors and mutators
//Getters
Vector2D Edge::GetV0(void) const
{
	return _v0;
}

Vector2D Edge::GetV1(void) const
{
	return _v1;
}

//Setters
void Edge::SetV0(Vector2D v0)
{
	_v0 = v0;
}

void Edge::SetV1(Vector2D v1)
{
	_v1 = v1;
}

// Private methods

void Edge::Init(Vector2D v0, Vector2D v1)
{
	_v0 = v0;
	_v1 = v1;
}

void Edge::Copy(const Edge& e)
{
	_v0 = e.GetV0();
	_v1 = e.GetV1();
}