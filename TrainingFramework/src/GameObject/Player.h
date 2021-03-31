#pragma once 
#include "Sprite2D.h"

class Player : public Sprite2D
{
public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Player();
	void	SetOnClick(void(*pBtClick)());
	void	HandleKeyEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();

private:
	void(*m_pBtClick)();
	bool	m_isHandle;

};
