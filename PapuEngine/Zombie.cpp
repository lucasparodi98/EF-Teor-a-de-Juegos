#include "Zombie.h"
#include "Human.h"
#include "ResourceManager.h"

Zombie::Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position) {
	_speed = speed;
	_position = position;
	color.set(0, 255, 0, 255);
}

void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {
	collideWithLevel(levelData);

	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
				closeHuman->getPosition() - _position);
		_position += direction*_speed;
	}
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
	Human* closestHuman = nullptr;

	float smallestDistance = 88888888888.0f;

	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - _position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	return closestHuman;

}

void Zombie::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Textures/circle.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

Zombie::~Zombie()
{
}
