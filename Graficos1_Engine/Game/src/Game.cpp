#include "Game.h"
#include "iostream"
#include "Utility/KeyCodes.h"
#include "Utility/Color.h"


Game::Game()
{
    float tVertices[6] =
    {
        1, 0,
        -1, 0,
        0, 1
    };

    float sColors[4][4] =
    {
        {WHITE},
        {RED},
        {RED},
        {WHITE}
    };
    
    //square = new Square(sColors, true);
    int imageSize[] = {260,64};
    //sprite = new Sprite("res/Wolfies.png");
    //sprite = new Sprite("res/Wolfies.png", imageSize);
    sprite = new Sprite("res/Wolfies.png", imageSize, 4, 1);
    sprite->Scale(100, 100);

    squareScaleMod = 1;
    squareMoveMod = 1;

    //triangle = new Triangle(tVertices, true);
    //square->Scale(100, 100);
    //square->Translate(0, 0);
}

Game::~Game()
{
    delete sprite;
    //delete square;
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
    //sprite->Rotate(1);
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

    //if (square->GetScale().x < 10 && squareScaleMod > 0)
    //{
    //    squareScaleMod = 0;
    //}

    float squareScale = 0.5f * squareScaleMod;
    float squareMove = 1.0f * squareMoveMod;
    

    //triangle->Scale(squareScale, -squareScale);
    sprite->Scale(-squareScale, -squareScale);
    //square->Translate(squareMove, 0);
}

void Game::Draw()
{
	sprite->Draw();
	//square->Draw();
    //triangle->Draw();
}