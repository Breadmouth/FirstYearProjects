#include "Screen.h"

Screen::Screen(unsigned int width, unsigned int height, ScreenManager* sm)
{
	m_width = width;
	m_height = height;
	m_sm = sm;
}
Screen::~Screen()
{

}