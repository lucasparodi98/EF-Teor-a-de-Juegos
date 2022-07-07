#include "GameOverScreen.h"
#include "ScreenIndices.h"
#include <iostream>

void GameOverScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(event.button.button);
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		}

		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			std::cout << "Para el otro a�o ser� :D" << std::endl;
		}
	}
}

GameOverScreen::GameOverScreen(Window* window) :_window(window)
{
    _screenIndex = SCREEN_INDEX_MENU;
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::build()
{
    background = new Background("Textures/Fondos/gam-over.png");
}

void GameOverScreen::destroy()
{
    background = nullptr;
}

void GameOverScreen::onExit()
{
    destroy();
}

void GameOverScreen::onEntry()
{
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
	_spriteBatch.init();
	_camera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	spriteFont = new SpriteFont("Fonts/Fuente2.ttf", 40);
}

void GameOverScreen::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBatch.begin();

	background->draw(_spriteBatch);
	char buffer[256];
	sprintf_s(buffer, "PUNTAJE MAXIMO OBTENIDO: F");
	Color color;
	color.r = 0;
	color.g = 0;
	color.b = 255;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-280, 150), glm::vec2(1), 0.0f, color);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}

void GameOverScreen::update()
{
	draw();
	_camera.update();
	inputManager.update();
	checkInput();
}

int GameOverScreen::getNextScreen() const
{
    return -1;
}

int GameOverScreen::getPreviousScreen() const
{
    return -1;
}
