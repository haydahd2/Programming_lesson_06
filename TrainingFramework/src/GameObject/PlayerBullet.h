#pragma once
#include "BaseObject.h"

template<class T>

class PlayerBullet
{
private:
	std::vector<std::shared_ptr<T>> objects;
	int POOL_SIZE = 100;
	bool isSpawning = false;
	float currentTime = 0;
	float spawnInterval = 1;

public:
	PlayerBullet()
	{
		srand(time(0));
		Init();
	}

	void Init()
	{
		for (int i = 0; i < POOL_SIZE; i++)
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			auto obj = std::make_shared<T>(model, shader, nullptr);
			objects.push_back(obj);
		}
	}

	std::shared_ptr<T> GetObjectT()
	{
		for (auto obj : objects)
		{
			if (!obj->isActive)
			{
				obj->isActive = true;
				return obj;
			}
		}

		Init();

		POOL_SIZE *= 2;
		return GetObjectT();
	}

	void ReturnObject(std::shared_ptr<T> obj)
	{
		obj->Reset();
	}

	void Update(GLfloat deltaTime)
	{
		if (isSpawning)
		{
			//std::cout << currentTime << std::endl;
			currentTime += deltaTime;
			if (currentTime > spawnInterval)
			{

				currentTime -= spawnInterval;
				SpawnObjectT();
			}
		}

		for (auto obj : objects)
		{
			if (obj->isActive)
				obj->Update(deltaTime);
		}
	}

	void Draw()
	{
		for (auto obj : objects)
		{
			if (obj->isActive)
				obj->Draw();
		}
	}
