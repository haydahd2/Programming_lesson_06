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
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Player
	texture = ResourceManagers::GetInstance()->GetTexture("Stand");
	std::shared_ptr<Animation2D> Player = std::make_shared<Animation2D>(model, shader, texture);
	Player->Set2DPosition(screenWidth / 2, screenHeight / 2);
	Player->SetSize(100, 100);
	m_Animation.push_back(Player);

	//Coin
	texture = ResourceManagers::GetInstance()->GetTexture("Coin");
	Player = std::make_shared<Animation2D>(model, shader, texture);
	Player->Set2DPosition(screenWidth / 2, screenHeight / 2 - 200);
	Player->SetSize(100, 100);
	m_Animation.push_back(Player);

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
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_Animation)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score->Draw();
	for (auto it : m_Animation)
	{
		it->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}