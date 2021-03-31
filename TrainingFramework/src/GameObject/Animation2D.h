#pragma once
#include "baseobject.h"

class Animation2D : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLfloat			m_numFrames;
	GLfloat			m_currentFrame;
	GLfloat			m_currentTime;
	GLfloat			m_frameTime;
public:
	Animation2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLfloat numFrames, GLfloat frameTime);
	~Animation2D();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;


	void		SetText(std::string text);
	std::string	GetText();

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

	void SetNumFrames(GLint numFrames);
	void SetFrameTime(GLfloat frameTime);
};

