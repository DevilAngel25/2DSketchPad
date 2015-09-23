#include "StdAfx.h"
#include "Store.h"

#define _MAX_SHAPE 10000

//create a struct of shapes.
typedef struct
{
	unsigned int Type;
	Edge e0;
	COLORREF BC;
	COLORREF FC;
	bool Fill;
} _StoreShape;

_StoreShape _list_Shape[_MAX_SHAPE];
_StoreShape _temp_Shape;

// Constructors
Store::Store(void)
{
	Init(0, 0, _e0, 0, 0, false);
}

Store::Store(int type, int count, Edge e0, COLORREF bc, COLORREF fc, bool fill)
{
	Init(type, count, e0, bc, fc, fill);
}

Store::Store(const Store& p)
{
	Copy(p);
}

Store::~Store(void)
{
}

// Accessors and mutators

//-- GET --\\

//-- Get the Shape type
int Store::GetType(int i) const
{
	return _list_Shape[i].Type;
}

//-- Get the Edge
Edge Store::GetEdge(int i) const
{
	return _list_Shape[i].e0;
}

//-- Get the Border color
int Store::GetBC(int i) const
{
	return _list_Shape[i].BC;
}

//-- Get the Fill color
int Store::GetFC(int i) const
{
	return _list_Shape[i].FC;
}

//-- Get the Fill
bool Store::GetFill(int i) const
{
	return _list_Shape[i].Fill;
}


//-- SET --\\

//-- set the Shape type
void Store::SetType(int i, int j)
{
	_list_Shape[i].Type = j;
}

//-- Set the Edge
void Store::SetEdge(int i, Edge j)
{
	_list_Shape[i].e0 = j;
}

//-- Set the Border color
void Store::SetBC(int i, int j)
{
	_list_Shape[i].BC = j;
}

//-- Set the Fill color
void Store::SetFC(int i, int j)
{
	_list_Shape[i].FC = j;
}

//-- Set the Fill
void Store::SetFill(int i, bool j)
{
	_list_Shape[i].Fill = j;
}


// Operator overloads

Store& Store::operator=(const Store &rhs)
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
void Store::Init(int type, int count, Edge e0, COLORREF bc, COLORREF fc, bool fill)
{
	_count = count;
	_type = type;

	_temp_Shape.Type = type;
	_temp_Shape.e0 = e0;

	_temp_Shape.BC = bc;
	_temp_Shape.FC = fc;
	_temp_Shape.Fill = fill;

	SetType(count, type);
	SetEdge(count, e0);

	SetBC(count, bc);
	SetFC(count, fc);
	SetFill(count, fill);
}

void Store::Copy(const Store& p)
{
	int i = _count;

	_temp_Shape.e0 = p.GetEdge(i);

	_temp_Shape.BC = p.GetBC(i);
	_temp_Shape.FC = p.GetFC(i);
	_temp_Shape.Fill = p.GetFill(i);
}