#pragma once
#include <string>
#include "Edge.h"

//A class to store any shape that is drawn
class Store
{
	public:
		Store(void);
		Store(int type, int count, Edge e0, COLORREF bc, COLORREF fc, bool fill); //takes the type of shape, which shape to access, an edge to store, colors, and whether the shape is filled.
		Store(const Store& m);
		~Store(void);

		//-- GET --\\

		int GetType(int) const;

		Edge GetEdge(int) const;

		int GetBC(int) const;
		int GetFC(int) const;
		bool GetFill(int) const;


		//-- SET --\\

		void SetType(int, int);

		void SetEdge(int, Edge);

		void SetBC(int, int);
		void SetFC(int, int);
		void SetFill(int, bool);

		Store& operator= (const Store &rhs);

	private:
		Edge _e0;
		Vector2D _v0, _v1;

		int _count, _type;

		void Init(int type, int count, Edge e0, COLORREF bc, COLORREF fc, bool fill);
		void Copy(const Store& m);
		
};