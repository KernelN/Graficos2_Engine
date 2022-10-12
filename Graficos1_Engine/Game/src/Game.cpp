#include "Game.h"
#include "iostream"
#include "Utility/KeyCodes.h"

Game::Game()
{
    float tVertices[6] =
    {
        1, 0,
        -1, 0,
        0, 1
    };

    float sVertices[8] =
    {
        -10, -10,
        10, -10,
        10, 10,
        -10, 10
    };
    
    //square = new Square(sVertices, true);

    squareScaleMod = 1;
    squareMoveMod = 1;

    triangle = new Triangle(tVertices, true);
    triangle->Scale(100, 100);
    triangle->Translate(0, 0);
}

Game::~Game()
{
    //delete square;
    delete triangle;
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
    //triangle->Rotate(1);
    /*if (triangle->GetScale().x > 5.0f && squareScaleMod > 0)
    {
        squareScaleMod = -1;
    }
    else if (triangle->GetScale().x < 0.5f && squareScaleMod < 0)
    {
        squareScaleMod = 1;
    }

    if (triangle->GetTranslation().x > 200.0f && squareMoveMod > 0)
    {
        squareMoveMod = -1;
    }
    else if (triangle->GetTranslation().x < -200.0f && squareMoveMod < 0)
    {
        squareMoveMod = 1;
    }*/

    if (IsKeyPressed(KEY_SPACE))
    {
        squareScaleMod = 1;
    }
    else
    {
        squareScaleMod = 0;
    }

    if (triangle->GetScale().x < 10 && squareScaleMod > 0)
    {
        squareScaleMod = 0;
    }

    float squareScale = 0.5f * squareScaleMod;
    float squareMove = 1.0f * squareMoveMod;
    

    //triangle->Scale(squareScale, -squareScale);
    triangle->Scale(-squareScale, -squareScale);
    //square->Translate(squareMove, 0);
}

void Game::Draw()
{
	//square->Draw();
    triangle->Draw();
}