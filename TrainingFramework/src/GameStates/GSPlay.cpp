#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "Animation2D.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
	gravity = 0;
	eGravity = 0;
	pJump = 800;
	eJump = 800;
	friction = 20;
	pressTime = 0;
	floor = true;
	isAlive = true;
	isDash = false;
	isJump = false;
	eIsJump = false;
	isFire = false;
	pDash = false;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto Anishader = ResourceManagers::GetInstance()->GetShader("AnimationShader");

	//BackGround
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg-gameplay");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(screenWidth / 2 + screenWidth, screenHeight / 2);
	m_BackGround1->SetSize(screenWidth, screenHeight);

	//bullet

	//Player
	auto numFrames = 3;
	auto frameTime = 0.15;
	texture = ResourceManagers::GetInstance()->GetTexture("run");
	m_Player = std::make_shared<Animation2D>(model, Anishader, texture, numFrames, frameTime);
	m_Player->Set2DPosition(screenWidth / 2 - 470, screenHeight / 2 + 210);
	m_Player->SetSize(100, 100);

	//Enemy
	auto EnumFrames = 3;
	texture = ResourceManagers::GetInstance()->GetTexture("eJumper");
	m_Enemy = std::make_shared<Animation2D>(model, Anishader, texture, EnumFrames, frameTime);
	m_Enemy->Set2DPosition(screenWidth, screenHeight / 2 + 210);
	m_Enemy->SetSize(80, 120);

	

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	switch (key)
	{
	case KEY_DASH:
		if (isJump)
			break;
		else if (!floor)
			break;
		else if (pDash)
			break;
		else isDash = true;
		break;
	case KEY_JUMP:
		if (!floor)
			break;
		else if (isDash)
			break;
		else isJump = true;
		break;
	case KEY_FIRE:
		isFire = true;
	default:
		break;
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	//set gravity
	if (m_Player->Get2DPosition().y >= screenHeight / 2 + 210)
	{
		m_Player->SetTexture(ResourceManagers::GetInstance()->GetTexture("run"));
		gravity = 0;
		floor = true;
	}
	if (!floor)
	{
		m_Player->Set2DPosition(m_Player->Get2DPosition().x, m_Player->Get2DPosition().y + gravity * deltaTime);
		gravity += friction;
	}

	//set background
	if (m_BackGround->Get2DPosition().x <= -screenWidth / 2)
	{
		m_BackGround->Set2DPosition(m_BackGround->Get2DPosition().x + screenWidth * 2 - 5, screenHeight / 2);
	}
	else 
	{
		m_BackGround->Set2DPosition(m_BackGround->Get2DPosition().x - 100 * deltaTime, screenHeight / 2);
	}
	if (m_BackGround1->Get2DPosition().x <= -screenWidth / 2)
	{
		m_BackGround1->Set2DPosition(m_BackGround1->Get2DPosition().x + screenWidth * 2 - 5, screenHeight / 2);
	}
	else
	{
		m_BackGround1->Set2DPosition(m_BackGround1->Get2DPosition().x - 100 * deltaTime, screenHeight / 2);
	}

	//set action
	if (isAlive) 
	{
		if (isJump)
		{
			if (m_Player->Get2DPosition().y >= screenHeight / 2 - 100 && pJump >= 0)
			{
				m_Player->SetTexture(ResourceManagers::GetInstance()->GetTexture("jump"));
				m_Player->Set2DPosition(m_Player->Get2DPosition().x, m_Player->Get2DPosition().y - pJump * deltaTime);
				pJump -= friction;
			}
			else
			{
				pJump = 800;
				isJump = false;
				floor = false;
			}
		}
		if (isDash)
		{
			if (m_Player->Get2DPosition().x < screenWidth / 2 - 250 && !pDash)
			{
				m_Player->SetNumFrames(1);
				m_Player->SetTexture(ResourceManagers::GetInstance()->GetTexture("dash"));
				m_Player->Set2DPosition(m_Player->Get2DPosition().x + 400 * deltaTime, m_Player->Get2DPosition().y);
			}
			else
			{
				pDash = true;
			}
			if (m_Player->Get2DPosition().x <= screenWidth / 2 - 470)
			{
				isDash = false;
				pDash = false;
			}
			if(pDash)
			{
				m_Player->SetNumFrames(3);
				m_Player->SetTexture(ResourceManagers::GetInstance()->GetTexture("run"));
				m_Player->Set2DPosition(m_Player->Get2DPosition().x - 200 * deltaTime, m_Player->Get2DPosition().y);
			}
		}
		if (isFire)
		{
			isFire = false;
		}
		else
		{
		}

	}
//ENEMY------------------------------------------------------------------------------------------------------------------------
	if (m_Enemy->Get2DPosition().x <= -screenWidth)
	{
		m_Enemy->Set2DPosition(m_Enemy->Get2DPosition().x + screenWidth * 2, m_Enemy->Get2DPosition().y);
	}
	else
	{
		m_Enemy->Set2DPosition(m_Enemy->Get2DPosition().x - 200 * deltaTime, m_Enemy->Get2DPosition().y);
	}
	//Enemy jump
	if (!eIsJump)
	{
		if (eJump >= 0)
		{
			m_Enemy->Set2DPosition(m_Enemy->Get2DPosition().x, m_Enemy->Get2DPosition().y - eJump * deltaTime);
			eJump -= friction;
		}
		else
		{
			eIsJump = true;
		}
	}
	else
	{
		if (m_Enemy->Get2DPosition().y >= screenHeight / 2 + 210)
		{
			eGravity = 0;
			eJump = 800;
			eIsJump = false;
		}
		else
		{
			m_Enemy->Set2DPosition(m_Enemy->Get2DPosition().x, m_Enemy->Get2DPosition().y + eGravity * deltaTime);
			eGravity += friction;
		}
	}
	if(m_Enemy)
	//Contact
	if (m_Enemy->Get2DPosition().x == m_Player->Get2DPosition().x && m_Enemy->Get2DPosition().y == m_Player->Get2DPosition().y)
	{
		m_Player->SetNumFrames(4);
		m_Player->SetTexture(ResourceManagers::GetInstance()->GetTexture("dead"));
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	}

	m_Enemy->Update(deltaTime);
	m_Player->Update(deltaTime);
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_BackGround1->Draw();
	m_score->Draw();
	m_Player->Draw();
	m_Enemy->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}