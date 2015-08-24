#include "Sprite.h"
#include "Game.h"
#include "Vec3.h"
#include "Mat3.h"
#include <iostream>

Sprite::~Sprite()
{
	if (m_vbo != 0)
	{
		glDeleteBuffers( 1, &m_vbo );
	}
	if (m_ibo != 0)
	{
		glDeleteBuffers( 1, &m_ibo );
	}
}

void Sprite::LoadTexture(const char* textureName)
{
	//check file exists
	if(textureName != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(textureName, &m_width, &m_height, &m_bpp, SOIL_LOAD_AUTO);

		//check for successful read
		if(pImageData)
		{
			//create opengl texture handle
			m_ID = SOIL_create_OGL_texture(pImageData, m_width, m_height, m_bpp,
				SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS| SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
			//clear what was read in from file now that it is stored in the handle
			SOIL_free_image_data(pImageData);
		}

		//check for errors
		if(m_ID == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
	}
}

Sprite::Sprite(Game* game, const char* textureName, int width, int height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width;
	m_height = height;
}

void Sprite::Init()
{
	// initialise member variables
	m_ID = 0;
	m_height = 0;
	m_width = 0;
	m_bpp = 0;
	m_vbo = 0;
	m_ibo = 0;
	m_rotation = 0;
	m_parent = NULL;
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set up vertices
	// UV coords shown below:
	// (0,1)+-----------------+(1,1)
	//      |                 |
	//      |                 |
	//      |                 |
	//      |                 |
	//      |                 |
	// (0,0)+-----------------+(1,0)

	// top left
	m_vertices[0].Positions[0] = -1.0f;
	m_vertices[0].Positions[1] = 1.0f;
	m_vertices[0].Positions[2] = 0.0f;
	m_vertices[0].Positions[3] = 1.0f;
	m_vertices[0].Colours[0] = 1.0f;
	m_vertices[0].Colours[1] = 1.0f;
	m_vertices[0].Colours[2] = 1.0f;
	m_vertices[0].Colours[3] = 1.0f;
	m_vertices[0].UVs[0] = 0.0f;
	m_vertices[0].UVs[1] = 1.0f;

	// top right
	m_vertices[1].Positions[0] = 1.0f;
	m_vertices[1].Positions[1] = 1.0f;
	m_vertices[1].Positions[2] = 0.0f;
	m_vertices[1].Positions[3] = 1.0f;
	m_vertices[1].Colours[0] = 1.0f;
	m_vertices[1].Colours[1] = 1.0f;
	m_vertices[1].Colours[2] = 1.0f;
	m_vertices[1].Colours[3] = 1.0f;
	m_vertices[1].UVs[0] = 1.0f;
	m_vertices[1].UVs[1] = 1.0f;


	// bottom left
	m_vertices[2].Positions[0] = -1.0f;
	m_vertices[2].Positions[1] = -1.0f;
	m_vertices[2].Positions[2] = 0.0f;
	m_vertices[2].Positions[3] = 1.0f;
	m_vertices[2].Colours[0] = 1.0f;
	m_vertices[2].Colours[1] = 1.0f;
	m_vertices[2].Colours[2] = 1.0f;
	m_vertices[2].Colours[3] = 1.0f;
	m_vertices[2].UVs[0] = 0.0f;
	m_vertices[2].UVs[1] = 0.0f;

	// bottom right
	m_vertices[3].Positions[0] = 1.0f;
	m_vertices[3].Positions[1] = -1.0f;
	m_vertices[3].Positions[2] = 0.0f;
	m_vertices[3].Positions[3] = 1.0f;
	m_vertices[3].Colours[0] = 1.0f;
	m_vertices[3].Colours[1] = 1.0f;
	m_vertices[3].Colours[2] = 1.0f;
	m_vertices[3].Colours[3] = 1.0f;
	m_vertices[3].UVs[0] = 1.0f;
	m_vertices[3].UVs[1] = 0.0f;

	glGenBuffers(1, &m_vbo);
	//check it succeeded
	if(m_vbo != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//allocate space for vertices on the graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, m_vertices, sizeof(Vertex)*4);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//create ID for index buffer object
	glGenBuffers(1, &m_ibo);
	//check it succeeded
	if(m_ibo != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		//allocate space for index info on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		((char*)iBuffer)[0] = 0;
		((char*)iBuffer)[1] = 1;
		((char*)iBuffer)[2] = 2;
		((char*)iBuffer)[3] = 1;
		((char*)iBuffer)[4] = 3;
		((char*)iBuffer)[5] = 2;
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Sprite::Draw(float deltaTime)
{
	// update vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//allocate space for vertices on the graphics card
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, NULL, GL_STATIC_DRAW);
	//get pointer to allocated space on the graphics card
	GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	//copy data to graphics card
	memcpy(vBuffer, m_vertices, sizeof(Vertex)*4);
	//unmap and unbind buffer
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//bind texture
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*8));

	//draw to the screen
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::Update(float deltaTime)
{

	Mat3 translation = (translation.CreateTranslation( Vector3( m_position)));
	Mat3 rotation = (rotation.CreateRotation(m_rotation));

	m_transform = rotation * translation;

	if (m_parent)
	{
		m_worldTransform = m_transform * m_parent->GetWorldTransform();
	}
	else 
	{
		m_worldTransform = m_transform;
	}

	for (auto i = m_children.begin(); i != m_children.end(); i++)
	{
		(*i)->Update(deltaTime);
	}

	ApplyTransform();
}

void Sprite::ApplyTransform()
{
	Vector3 topLeft(0 - m_anchor.x, 1 - m_anchor.y);
	Vector3 topRight(1 - m_anchor.x, 1 - m_anchor.y);
	Vector3 bottomLeft(0 - m_anchor.x, 0 - m_anchor.y);
	Vector3 bottomRight(1 - m_anchor.x, 0 - m_anchor.y);

	Mat3 scale = (scale.CreateScale( Vector3( (float)m_width, (float)m_height)));

	topLeft = m_worldTransform * (scale * topLeft);
	topRight = m_worldTransform * (scale * topRight);
	bottomLeft = m_worldTransform * (scale * bottomLeft);
	bottomRight = m_worldTransform * (scale * bottomRight);

	topLeft.x = ((2.0f / m_game->GetScreenWidth()) * topLeft.x) - 1.0f;
	topLeft.y = ((2.0f / m_game->GetScreenHeight()) * topLeft.y) - 1.0f;
	
	topRight.x = ((2.0f / m_game->GetScreenWidth()) * topRight.x) - 1.0f;
	topRight.y = ((2.0f / m_game->GetScreenHeight()) * topRight.y) - 1.0f;
	
	bottomLeft.x = ((2.0f / m_game->GetScreenWidth()) * bottomLeft.x) - 1.0f;
	bottomLeft.y = ((2.0f / m_game->GetScreenHeight()) * bottomLeft.y) - 1.0f;
	
	bottomRight.x = ((2.0f / m_game->GetScreenWidth()) * bottomRight.x) - 1.0f;
	bottomRight.y = ((2.0f / m_game->GetScreenHeight()) * bottomRight.y) - 1.0f;

	m_vertices[0].Positions[0] = topLeft.x;
	m_vertices[0].Positions[1] = topLeft.y;
	m_vertices[1].Positions[0] = topRight.x;
	m_vertices[1].Positions[1] = topRight.y;
	m_vertices[2].Positions[0] = bottomLeft.x;
	m_vertices[2].Positions[1] = bottomLeft.y;
	m_vertices[3].Positions[0] = bottomRight.x;
	m_vertices[3].Positions[1] = bottomRight.y;
}

int Sprite::GetHeight()	const
{
	return m_height;
}

int Sprite::GetWidth()	const
{
	return m_width;
}

int Sprite::GetBPP()	const
{
	return m_bpp;
}

unsigned int Sprite::GetID()	const
{
	return m_ID;
}

Vector2 Sprite::GetPosition()	const
{
	return m_position;
}

Vector2 Sprite::GetPreviousPosition()	const
{
	return m_previousPosition;
}

float Sprite::GetRotation()	const
{
	return m_rotation;
}

void Sprite::SetPosition(const Vector2& position)
{
	m_position = position;
}

void Sprite::SetPosition(float x, float y)
{
	m_position = Vector2(x, y);
}

Vector2 Sprite::GetAnchorPoint()	const
{
	return m_anchor;
}

void Sprite::SetAnchorPoint(const Vector2& anchor)
{
	m_anchor = anchor;
}

void Sprite::SetParent(Sprite* parent)
{
	m_parent = parent;
}

void Sprite::AddChild(Sprite* child)
{
	m_children.push_back(child);
	child->SetParent(this);
}

Mat3 Sprite::GetTransform()	const
{
	return m_transform;
}

Mat3 Sprite::GetWorldTransform() const
{
	return m_worldTransform;
}

void Sprite::SetRotation( float a_rotation)
{
	m_rotation = a_rotation;
}

float Sprite::GetRadius()	const
{
	return m_radius;
}

Mat3 Sprite::Invert()
{
	return m_worldTransform.Inverse();
}

void Sprite::Transform(const Mat3 &rhs)
{
	Vector3 topLeft(0 - m_anchor.x, 1 - m_anchor.y);
	Vector3 topRight(1 - m_anchor.x, 1 - m_anchor.y);
	Vector3 bottomLeft(0 - m_anchor.x, 0 - m_anchor.y);
	Vector3 bottomRight(1 - m_anchor.x, 0 - m_anchor.y);

	Mat3 scale = (scale.CreateScale( Vector3( (float)m_width, (float)m_height)));

	topLeft = rhs * (scale * topLeft);
	topRight = rhs * (scale * topRight);
	bottomLeft = rhs * (scale * bottomLeft);
	bottomRight = rhs * (scale * bottomRight);

	topLeft.x = ((2.0f / m_game->GetScreenWidth()) * topLeft.x) - 1.0f;
	topLeft.y = ((2.0f / m_game->GetScreenHeight()) * topLeft.y) - 1.0f;
	
	topRight.x = ((2.0f / m_game->GetScreenWidth()) * topRight.x) - 1.0f;
	topRight.y = ((2.0f / m_game->GetScreenHeight()) * topRight.y) - 1.0f;
	
	bottomLeft.x = ((2.0f / m_game->GetScreenWidth()) * bottomLeft.x) - 1.0f;
	bottomLeft.y = ((2.0f / m_game->GetScreenHeight()) * bottomLeft.y) - 1.0f;
	
	bottomRight.x = ((2.0f / m_game->GetScreenWidth()) * bottomRight.x) - 1.0f;
	bottomRight.y = ((2.0f / m_game->GetScreenHeight()) * bottomRight.y) - 1.0f;

	m_vertices[0].Positions[0] = topLeft.x;
	m_vertices[0].Positions[1] = topLeft.y;
	m_vertices[1].Positions[0] = topRight.x;
	m_vertices[1].Positions[1] = topRight.y;
	m_vertices[2].Positions[0] = bottomLeft.x;
	m_vertices[2].Positions[1] = bottomLeft.y;
	m_vertices[3].Positions[0] = bottomRight.x;
	m_vertices[3].Positions[1] = bottomRight.y;
}

	void Sprite::AdjustAlpha(float alpha)
	{
		m_vertices[0].Colours[3] = alpha;
		m_vertices[1].Colours[3] = alpha;
		m_vertices[2].Colours[3] = alpha;
		m_vertices[3].Colours[3] = alpha;
	}