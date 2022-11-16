#include "Game.h"
#include "iostream"
#include "Utility/KeyCodes.h"
#include "Utility/Color.h"

unsigned int spriteNum;
unsigned int keyFrameCooldown = 0;
 
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
    for (int i = 0; i < 4; i++)
    {
        sprite[i] = new Sprite("res/Wolfies.png", imageSize, 4, i);
        sprite[i]->Scale(100, 100);
        sprite[i]->UnBind();
    }

    sprite[spriteNum]->Bind();

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

    if (keyFrameCooldown > 0) keyFrameCooldown--;

    if (IsKeyPressed(KEY_SPACE))
    {
        if (keyFrameCooldown > 0) return;

        keyFrameCooldown = 1000;

        sprite[spriteNum]->UnBind();

        spriteNum++;
        if (spriteNum > 3) spriteNum = 0;

        sprite[spriteNum]->Bind();
        
        //sprite->ChangeSprite(4, 1);
        std::cout << spriteNum << std::endl;
        //squareScaleMod = 1;
    }
    else
    {
        squareScaleMod = 0;
    }
    if (IsKeyPressed(KEY_A))
    {
        squareMoveMod = -1;
    }
    else if (IsKeyPressed(KEY_D))
    {
        squareMoveMod = 1;
    }
    else
    {
        squareMoveMod = 0;
    }

    //if (square->GetScale().x < 10 && squareScaleMod > 0)
    //{
    //    squareScaleMod = 0;
    //}

    float squareScale = 0.5f * squareScaleMod;
    float squareMove = 1.0f * squareMoveMod;
    

    //triangle->Scale(squareScale, -squareScale);
    sprite[spriteNum]->Scale(-squareScale, -squareScale);
    sprite[spriteNum]->Translate(squareMove, 0);
}

void Game::Draw()
{
	sprite[spriteNum]->Draw();
	//square->Draw();
    //triangle->Draw();
}