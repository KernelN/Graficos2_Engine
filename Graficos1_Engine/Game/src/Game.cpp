#include "Game.h"


Game::Game() { }

Game::~Game()
{
    delete square;
    delete triangle;
}

void Game::Init()
{

    float tVertices[6] =
    {
        0.5, 0.5,
        -0.5, 0.5,
        0, 1
    };

    float sVertices[8] =
    {
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5
    };

    square = new Square(sVertices, true);
    triangle = new Triangle(tVertices, true);
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
    triangle->Draw();
}