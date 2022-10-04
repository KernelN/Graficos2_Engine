#include "Game.h"


Game::Game()
{
    float tVertices[6] =
    {
        0.5, 0.5,
        -0.5, 0.5,
        0, 1
    };

    float sVertices[8] =
    {
        -10, -10,
        10, -10,
        10, 10,
        -10, 10
    };
    
    square = new Square(sVertices, true);

    //triangle = new Triangle(tVertices, true);
}

Game::~Game()
{
    delete square;
    //delete triangle;
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
    //triangle->Draw();
}