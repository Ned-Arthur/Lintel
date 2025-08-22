#pragma once
#include <Lintel.h>

class Enemy : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	float speed = 10;
	int health = 3;

	const float maxWalkTime = 2.f;
	float walkTime = 0;
	int direction = 0;

	const float maxShootTime = 0.5f;
	float shootTime = 0;

	void Setup() override
	{
		InitSprite("assets/human.spt");
		Sprite()->RecolourFullSprite(Lintel::RED, Lintel::TRANSPARENT);
		InitPosition({ 30, 3 });
		InitSpriteCenter({ 1, 1 });
	}

	void Update()
	{
		if (walkTime >= maxWalkTime)
		{
			// Pick a direction to walk in
			direction = Lintel::Random::IntRange(0, 3);
			walkTime = 0;

			
		}

		float dx = 0, dy = 0;
		switch (direction)
		{
		case 0:
			dx += speed * Lintel::Time::DeltaTime;
			break;
		case 1:
			dy -= speed * Lintel::Time::DeltaTime;
			break;
		case 2:
			dx -= speed * Lintel::Time::DeltaTime;
			break;
		case 3:
			dy += speed * Lintel::Time::DeltaTime;
			break;
		}

		if (MoveByAndCollideWith(dx, dy, "solid", true))
		{
			walkTime = maxWalkTime;
		}
		else
		{
			walkTime += Lintel::Time::DeltaTime;
		}

		if (shootTime >= maxShootTime)
		{
			// Shoot in a different random direction
			//Renderer->CreateThing<EnemyBullet>()->init(Position, Lintel::Random::intRange(0, 7));

			shootTime = 0;
		}
		shootTime += Lintel::Time::DeltaTime;
	}

	void Hit(int damage)
	{
		health -= damage;
		if (health <= 0)
		{
			QueueDelete();
		}
	}
};
