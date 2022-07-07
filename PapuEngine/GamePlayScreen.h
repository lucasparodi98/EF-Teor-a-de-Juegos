#pragma once

#include <SDL\SDL.h>
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "GLTexture.h"
#include "SpriteBacth.h"
#include "Level.h"
#include "Zombie.h"
#include "Player.h"
#include "Human.h"
#include "Background.h"
#include "Button.h"
#include "SpriteFont.h"
#include "Enemy.h"
#include <time.h>
class GamePlayScreen : public IGameScreen
{
private:
	GLS_Program _program;
	Camera2D _camera;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	GLTexture _texture;
	InputManager _inputManager;
	vector<Level*> _levels;
	vector<Human*>  _humans;
	vector<Zombie*> _zombies;
	vector<Enemy*> _enemies;
	Background* background;
	Player* _player;
	Button* button;
	int _currenLevel;
	void updateAgents();
	SpriteFont* spriteFont;
	//Relantizador
	int lag = 0;

	float tiempo = 0;
	int puntaje = 0;
	float enemySpawner = 0;
public:
	int puntMax = 0;
	GamePlayScreen(Window* window);
	~GamePlayScreen();

	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void draw()override;
	virtual void update()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;

	void checkInput();
};

