#pragma once
#include "Human.h"
#include "InputManager.h"
#include <vector>
#include "Camera2D.h"

class Player: public Human
{
private:
	InputManager* _inputManager;
	int _currentGun;
	Camera2D* _camera;
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera);
	virtual void draw(SpriteBacth& spritebatch) override;
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies );
};

