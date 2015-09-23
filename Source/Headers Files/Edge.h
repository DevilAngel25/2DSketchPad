#pragma once
#include <string>
#include "Vector2D.h"

//create a class to handle edges
class Edge
{
	public:
		Edge(void);
		Edge(Vector2D v0, Vector2D v1);
		Edge(const Edge& e);
		~Edge(void);

		Vector2D GetV0(void) const;
		Vector2D GetV1(void) const;

		void SetV0(Vector2D v0);
		void SetV1(Vector2D v1);

	private:
		Vector2D _v0, _v1;
		unsigned int colour;

		void Init(Vector2D v0, Vector2D v1);
		void Copy(const Edge& v);
		
};
