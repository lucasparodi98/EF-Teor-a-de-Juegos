#pragma once
#include "Agent.h"
class Enemy : public Agent
{
protected:
	glm::vec2 _direction;
	int tipoEnemigo;
public:
	Enemy();
	~Enemy();

	void init(float speed, glm::vec2 position, int tipo);
	virtual void draw(SpriteBacth& spritebatch) override;
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	int getTipoEnemigo() { return tipoEnemigo; };
};

