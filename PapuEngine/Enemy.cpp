#include "Enemy.h"
#include "Zombie.h"
#include "Human.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(float speed, glm::vec2 position, int tipo)
{
	_speed = speed;
	color.set(255, 255, 255, 255);
	_position = position;
	tipoEnemigo = tipo;
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);

	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (_direction.length() == 0) {
		_direction = glm::vec2(1.0f, 1.0f);
	}
	_direction = glm::vec2(_direction);
}

void Enemy::draw(SpriteBacth& spritebatch)
{
	static int textureIDR = ResourceManager::getTexture("Textures/rojo.png").id;
	static int textureIDV = ResourceManager::getTexture("Textures/verde.png").id;
	static int textureIDA = ResourceManager::getTexture("Textures/amarillo.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, 60, 83);
	switch (tipoEnemigo)
	{
	case 1:
		spritebatch.draw(destRect, uvRect, textureIDR, 0.0f, color);
		break;
	case 2:
		spritebatch.draw(destRect, uvRect, textureIDV, 0.0f, color);
		break;
	case 3:
		spritebatch.draw(destRect, uvRect, textureIDA, 0.0f, color);
		break;
	}
	
}

void Enemy::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
	_position += _direction * _speed;
	if (_position.y > 167 || _position.y < -250 || _position.x < -380 || _position.x > 320) {
		_direction = glm::rotate(_direction, 20.0f);
	}
}