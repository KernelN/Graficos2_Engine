#include "Game.h"
#include <iostream>
#include "Utility/KeyCodes.h"
#include "Utility/Color.h"
#include "Utility/TimeSingleton.h"

unsigned int spriteNum = 0;
float timer = 0;

Game::Game()
{
    float s1Colors[4][4] =
    {
        {WHITE},
        {RED},
        {RED},
        {WHITE}
    };

    float s2Colors[4][4] =
    {
        {YELLOW},
        {GREEN},
        {GREEN},
        {YELLOW}
    };

    square1 = new Square(s1Colors, true);
    square1->Scale(100, 100);
    square1->Translate(100, 0);

    square2 = new Square(s2Colors, true);
    square2->Scale(100, 100);
    square2->Translate(-100, 0);

    //sprite1 = new Sprite("res/WolfiesWalk.png", 1, 0);
    //sprite1->Scale(25, 25);
    //sprite1->Translate(150, 0);
    
    //sprite2 = new Sprite("res/WolfiesGrowl.png", 1, 0);
    //sprite2->Scale(25, 25);
    //sprite2->Translate(-150, 0);

    //WITH A LENGTH OF LESS THAN 0.83 SECONDS 
      //THE ANIMATION STOPS WORKING
    Animation* wolfieWalkAnim = new Animation(1, 1);
    Animation* wolfieGrowlAnim = new Animation(1, 1);
    //sprite1->SetAnim(wolfieWalkAnim);
    //sprite2->SetAnim(wolfieGrowlAnim);

    scaleMod = 1;
}

Game::~Game()
{
    //delete sprite1;
    //delete sprite2;
    delete square1;
    delete square2;
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
    //sprite2->UpdateFrame();

    if (timer > 0) timer -= time->GetDelta();

    if (IsKeyPressed(KEY_SPACE))
    {
        if (timer > 0) return;

        timer = .1f;

        ////spriteNum++;
        //if (//spriteNum > 3) //spriteNum = 0;
        //
        ////sprite1->ChangeSprite(4, //spriteNum);
    }
    else
    {
        scaleMod = 0;
    }

    if (IsKeyPressed(KEY_W))
    {
        verticalMoveMod = 1;
    }
    else if (IsKeyPressed(KEY_S))
    {
        verticalMoveMod = -1;
    }
    else
    {
        verticalMoveMod = 0;
    }

    if (IsKeyPressed(KEY_A))
    {
        horizontalMoveMod = -1;
    }
    else if (IsKeyPressed(KEY_D))
    {
        horizontalMoveMod = 1;
    }
    else
    {
        horizontalMoveMod = 0;
    }

    if (IsKeyPressed(KEY_Q))
    {
        //sprite1->Rotate(1);
    }
    else if (IsKeyPressed(KEY_E))
    {
        //sprite1->Rotate(-1);
    }

    //if (square->GetScale().x < 10 && squareScaleMod > 0)
    //{
    //    squareScaleMod = 0;
    //}

    if (verticalMoveMod == 0 && horizontalMoveMod == 0) return;

    //float squareScale = 0.5f * scaleMod * time->GetDelta();
    float verticalMove = 100.0f * verticalMoveMod * time->GetDelta();
    float horizontalMove = 100.0f * horizontalMoveMod * time->GetDelta();


    //triangle->Scale(squareScale, -squareScale);
    ////sprite1->Scale(-squareScale, -squareScale);

    //sprite1->UpdateFrame();

    //sprite1->Translate(0, verticalMove);
    //sprite1->Translate(horizontalMove, 0);
    square1->Translate(0, verticalMove);
    square1->Translate(horizontalMove, 0);

    // Colisionan //sprite1 y //sprite2
    //while (collisionManager->CheckCollision(sprite1, sprite2))
    while (collisionManager->CheckCollision(square1, square2))
    {
        square1->Translate(0, -verticalMove);
        square1->Translate(-horizontalMove, 0);
        //sprite1->Translate(0, -verticalMove);
        //sprite1->Translate(-horizontalMove, 0);
    }
}

void Game::Draw()
{
	//sprite1->Draw();
	//sprite2->Draw();
    square1->Draw();
    square2->Draw();
    //triangle->Draw();
}