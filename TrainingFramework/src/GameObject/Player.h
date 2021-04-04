#pragma once 
#include "Sprite2D.h"

class Player : public Sprite2D
{
public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Player();
	void	Display(int x, int y);
	void	HandleKeyEvents(int key, bool bIsPressed);
	bool	IsHandle();
	void	Dash(GLfloat deltaTime);
private:
	bool	m_isHandle;

};
