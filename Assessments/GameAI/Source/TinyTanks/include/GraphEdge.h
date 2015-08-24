#pragma once
#include "GL/glew.h"
#include "Vec2.h"

class GraphNode;
class Vector2;

class GraphEdge
{
public:
	GraphNode* From;
	GraphNode* To;
	float Weight;

	inline void DrawLine(Vector2 lhs, Vector2 rhs)
	{
		Vector2 lhsGL = Screen2GL(lhs);
		Vector2 rhsGL = Screen2GL(rhs);
		glLineWidth(4); 
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex2f(-1 + lhsGL.x, -1 + lhsGL.y);
		glVertex2f(-1 + rhsGL.x, -1 + rhsGL.y);
		glEnd();
	}

	inline Vector2 Screen2GL(const Vector2 &input)
	{
		Vector2 pixSize = (Vector2(2.0f, 2.0f) / Vector2(800, 600));
		Vector2 point = Vector2(input.x * pixSize.x, input.y * pixSize.y);
		return point;
	}
};