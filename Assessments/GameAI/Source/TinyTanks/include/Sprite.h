#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <vector>
#include "Vec2.h"
#include "Mat3.h"

class Game;

struct Vertex
{
	float Positions[4];
	float Colours[4];
	float UVs[2];
};

class Sprite
{
public:
	
	Sprite(Game* game, const char* textureName, int width, int height);

	Sprite(Game* game);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetTextureID(unsigned int textureID);

	~Sprite();

	virtual void Update(float deltaTime);
	void Draw(float deltaTime);

	unsigned int m_texture;
	int GetWidth()	const;
	int GetHeight()	const;
	int GetBPP()		const;

	Mat3 GetTransform()	const;
	Mat3 GetWorldTransform() const;

	unsigned int GetID()	const;	
	
	Vector2 GetPosition()	const;
	Vector2 GetPreviousPosition()	const;
	float GetRadius()	const;
	float GetRotation()	const;

	void SetRotation( float a_rotation);

	Vector2 GetAnchorPoint()	const;
	void SetAnchorPoint(const Vector2& anchor);

	void SetPosition(const Vector2& position);
	void SetPosition(float x, float y);

	void SetParent(Sprite* parent);
	void AddChild(Sprite* child);

	float GetAlpha();
	void SetAlpha(float a);

	Mat3 Invert();

	void Transform(const Mat3 &rhs);

protected:
	int m_width;
	int m_height;
	int m_bpp;
	float m_alpha;

	float m_rotation;
	float m_radius;

	Mat3 m_transform;
	Mat3 m_worldTransform;

	unsigned int m_vbo;
	unsigned int m_ibo;

	unsigned int m_ID;

	Game* m_game;

	Vertex m_vertices[4];

	Vector2 m_position;
	Vector2 m_previousPosition;
	Vector2 m_anchor;


	Sprite* m_parent;
	std::vector<Sprite*> m_children;
	
	void Init();
	void ApplyTransform();
	void LoadTexture(const char* textureName);
};