#pragma once

class Background
{
private:
	int m_texture;

	float m_image1Y;
	float m_image2Y;

public:
	Background();

	void Scroll(float dt);

};