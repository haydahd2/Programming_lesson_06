#pragma once
#include "gamestatebase.h"

class Sprite2D;
class Sprite3D;
class Text;
class Animation2D;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

private:
	int gravity;
	int eGravity;
	int pJump;
	int eJump;
	int friction;
	int pressTime;
	bool isAlive;
	bool isJump;
	bool eIsJump;
	bool isDash;
	bool isFire;
	bool floor;
	bool pDash;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Sprite2D> m_Bullet;
	std::shared_ptr<Animation2D> m_Player;
	std::shared_ptr<Animation2D> m_Enemy;
	std::shared_ptr<Text>  m_score;
	std::list<std::shared_ptr<Animation2D>> m_Animation;
};

