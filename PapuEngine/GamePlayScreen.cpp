#include "GamePlayScreen.h"
#include "Game.h"

#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include "ScreenIndices.h"
#include <random>
#include <ctime>


GamePlayScreen::GamePlayScreen(Window* window) :
	_window(window)
{
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GamePlayScreen::~GamePlayScreen()
{
}


void GamePlayScreen::build() {
	_levels.push_back(new Level("Levels/level0.txt"));
	_player = new Player();
	_currenLevel = 0;
	_player->init(1.0f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager, &_camera);
	_humans.push_back(_player);
	_spriteBatch.init();
	background = new Background("Textures/Fondos/game.png");
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, _levels[_currenLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(
		1, _levels[_currenLevel]->getHeight() - 2);

}
void GamePlayScreen::destroy() {

}
void GamePlayScreen::onExit() {
}
void GamePlayScreen::onEntry() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();

	_camera.init(_window->getScreenWidth(),
		_window->getScreenHeight());

	spriteFont = new SpriteFont("Fonts/Fuente2.ttf", 20);
}
void GamePlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _texture.id);

	/*GLuint timeLocation =
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();
	background->draw(_spriteBatch);
	_player->draw(_spriteBatch);

	char buffer[256];
	Color color;
	color.r = 125;
	color.g = 0;
	color.b = 255;
	color.a = 255;
	sprintf_s(buffer, "Tiempo: %d", (int)tiempo);
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-360, 210), glm::vec2(1), 0.0f, color);
	sprintf_s(buffer, "Puntaje: %d", puntaje);
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(250, 210), glm::vec2(1), 0.0f, color);

	//Generar Enemigo
	if ((int)enemySpawner == 2) {
		int _generator = rand() % 3 + 1;
		int _randPosX = rand() % 700 - 380;
		int _randPosY = rand() % 417 - 250;
		_enemies.push_back(new Enemy());
		glm::vec2 pos(_randPosX, _randPosY);
		_enemies.back()->init(1.0f, pos, _generator);
		enemySpawner = 0;
	}


	
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->draw(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}
void GamePlayScreen::update() {
	lag++;
	if (lag == 5) {
		checkInput();
		draw();
		_camera.update();
		updateAgents();
		_inputManager.update();
		//_camera.setPosition(_player->getPosition());
		if (puntaje < 0) {
			_currentState = ScreenState::CHANGE_PREVIOUS;
		}
		lag = 0;
		tiempo += 0.002;
		enemySpawner += 0.002;
	}
}


void GamePlayScreen::updateAgents() {
	_player->update(_levels[_currenLevel]->getLevelData(),_humans, _zombies);

	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update(_levels[_currenLevel]->getLevelData(), _humans, _zombies);
		if (_enemies[i]->collideWithAgent(_player)) {
			//Q
			if (_inputManager.isKeyDown(SDLK_q)) {
				if (_enemies[i]->getTipoEnemigo() == 3)
					puntaje += 10;
				else if (_enemies[i]->getTipoEnemigo() == 1)
					puntaje -= 10;
				else if (_enemies[i]->getTipoEnemigo() == 2)
					puntaje -= 20;
				delete _enemies[i];
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
			}
			//W
			if (_inputManager.isKeyDown(SDLK_w)) {
				if (_enemies[i]->getTipoEnemigo() == 1)
					puntaje += 20;
				else
					puntaje -= 15;
				delete _enemies[i];
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
			}
			//E
			if (_inputManager.isKeyDown(SDLK_e)) {
				if (_enemies[i]->getTipoEnemigo() == 2)
					puntaje = puntaje * 2;
				else if (_enemies[i]->getTipoEnemigo() == 1)
					puntaje -= 5;
				else if (_enemies[i]->getTipoEnemigo() == 3)
					puntaje = puntaje / 2;
				delete _enemies[i];
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
			}
			if (puntaje > puntMax)
				puntMax = puntaje;
		}
	}
}

void GamePlayScreen::checkInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			//_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case  SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		}
		/*
		if (_inputManager.isKeyDown(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyDown(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
		*/
	}
}

int GamePlayScreen::getNextScreen() const {
	return SCREEN_INDEX_GAMEOVER;
};

int GamePlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_GAMEOVER;
}
