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
	float TimeCount, distX, distY, dist, distX2, distY2, dist2;
	int gravity, eGravity, pJump, eJump, friction, pressTime;
	bool isAlive;
	bool isJump;
	bool eIsJump;
	bool isDash;
	bool isFire;
	bool floor;
	bool pDash;
	bool createBullet;
	bool getHit;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Sprite2D> Bullet;
	std::shared_ptr<Animation2D> m_Player;
	std::shared_ptr<Animation2D> m_Enemy;
	std::shared_ptr<Text>  m_score;
	std::list<std::shared_ptr<Animation2D>> m_Animation;
};

