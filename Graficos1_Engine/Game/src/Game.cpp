#include "Game.h"


Game::Game()
{
    float tVertices[8] =
    {
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5
    };
    
    square = new Square(tVertices, true);
}

Game::~Game()
{
    delete square;
}

bool Game::IsRunning()
{
	return BaseEngine::IsRunning();
}

void Game::Loop()
{
	BaseEngine::Loop();
}

void Game::Draw()
{
	square->Draw();
}