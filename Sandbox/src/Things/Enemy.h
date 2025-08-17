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
		initSpriteFP("assets/human.spt");
		initPos({ 30, 3 });
		spriteCenter = { 1, 1 };
	}

	void LateSetup()
	{
		Sprite()->recolour(Lintel::RED, Lintel::TRANSPARENT);
	}

	void Update()
	{
		if (walkTime >= maxWalkTime)
		{
			// Pick a direction to walk in
			direction = Lintel::Random::intRange(0, 3);
			walkTime = 0;

			
		}

		float dx = 0, dy = 0;
		switch (direction)
		{
		case 0:
			dx += speed * Lintel::Time::deltaTime;
			break;
		case 1:
			dy -= speed * Lintel::Time::deltaTime;
			break;
		case 2:
			dx -= speed * Lintel::Time::deltaTime;
			break;
		case 3:
			dy += speed * Lintel::Time::deltaTime;
			break;
		}

		if (moveByAndCollideWith(dx, dy, "solid", true))
		{
			walkTime = maxWalkTime;
		}
		else
		{
			walkTime += Lintel::Time::deltaTime;
		}

		if (shootTime >= maxShootTime)
		{
			// Shoot in a different random direction
			//renderer->createThing<EnemyBullet>()->init(pos, Lintel::Random::intRange(0, 7));

			shootTime = 0;
		}
		shootTime += Lintel::Time::deltaTime;
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
