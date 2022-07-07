#include "Human.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

Human::Human()
{
}

void Human::init(float speed, glm::vec2 position) {
	_speed = speed;
	color.set(185, 0, 0, 255);
	_position = position;
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);

	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (_direction.length() == 0) {
		_direction = glm::vec2(1.0f, 1.0f);
	}
	_direction = glm::vec2(_direction);
}

void Human::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randRotate(-40.0f, 40.0f);
	_position += _direction * _speed;
	if (collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}

void Human::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Textures/circle.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

Human::~Human()
{
}
