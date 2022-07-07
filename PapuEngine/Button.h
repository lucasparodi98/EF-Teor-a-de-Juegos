#pragma once
#include <glm/glm.hpp>
#include <string>
#include "SpriteBacth.h"
#include "GLTexture.h"

class Button
{
private:
	std::string path;
	int _textureID;
	glm::vec4 _buttonPosition;
public:
	Button(std::string _path);
	~Button();
	void draw(SpriteBacth& spriteBatch, glm::vec4 positionB);
	bool click(glm::vec2 position);
};

