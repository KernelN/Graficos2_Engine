#include "Game.h"
#include "iostream"

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

    squareScaleMod = 1;
    squareMoveMod = 1;

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

void Game::OnLoop()
{
    square->Rotate(1);
    if (square->GetScale().x > 5.0f && squareScaleMod > 0)
    {
        squareScaleMod = -1;
    }
    else if (square->GetScale().x < 0.5f && squareScaleMod < 0)
    {
        squareScaleMod = 1;
    }

    if (square->GetTranslation().x > 200.0f && squareMoveMod > 0)
    {
        squareMoveMod = -1;
    }
    else if (square->GetTranslation().x < -200.0f && squareMoveMod < 0)
    {
        squareMoveMod = 1;
    }

    int squareScale = 1.0f * squareScaleMod;
    int squareMove = 1.0f * squareMoveMod;
    
    square->Scale(squareScale, -squareScale);
    //square->Translate(squareMove, 0);
}

void Game::Draw()
{
	square->Draw();
    //triangle->Draw();
}