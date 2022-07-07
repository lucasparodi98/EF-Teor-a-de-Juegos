#include "Player.h"
#include "ResourceManager.h"
#include <SDL\SDL.h>


void Player::init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera) {
	_speed = speed;
	_position = position;
	_camera = camera;
	_inputManager = inputManager;
	color.set(255, 255, 255, 255);
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies
	) {
	if (_inputManager->isKeyDown(SDLK_UP) && _position.y < 167) {
		_position.y += _speed;
	}
	if (_inputManager->isKeyDown(SDLK_DOWN) && _position.y > -250) {
		_position.y -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_LEFT) && _position.x > -380) {
		_position.x -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_RIGHT) && _position.x < 320) {
		_position.x += _speed;
	}
	collideWithLevel(levelData);
}

void Player::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Textures/player.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, 60, 83);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

Player::Player():_currentGun(-1)
{
}


Player::~Player()
{
}
