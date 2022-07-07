#pragma once
#include "Agent.h"
class Zombie :public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 position);
	virtual void draw(SpriteBacth& spritebatch) override;
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	Human* getNearestHuman(std::vector<Human*>& humans);
};

