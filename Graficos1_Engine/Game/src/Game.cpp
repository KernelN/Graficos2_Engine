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

    //player = new Square(s1Colors, true);
    //player->Scale(25, 25);
    //player->Translate(100, 0);

    //enemy = new Square(s2Colors, true);
    //enemy->Scale(25, 25);
    //enemy->Translate(-100, 0);

    player = new Sprite("res/WolfiesWalk.png", 5, 0);
    player->Scale(25, 25);
    player->Translate(150, 0);

    enemy = new Sprite("res/WolfiesGrowl.png", 5, 0);
    enemy->Scale(25, 25);
    enemy->Translate(-150, 0);


    //WITH A LENGTH OF LESS THAN 0.83 SECONDS 
      //THE ANIMATION STOPS WORKING
    Animation* wolfieWalkAnim = new Animation(1, 5);
    Animation* wolfieGrowlAnim = new Animation(1, 5);
    static_cast<Sprite*>(player)->SetAnim(wolfieWalkAnim);
    static_cast<Sprite*>(enemy)->SetAnim(wolfieGrowlAnim);

    scaleMod = 1;
}

Game::~Game()
{
    delete player;
    delete enemy;
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
    static_cast<Sprite*>(enemy)->UpdateFrame();

    if (timer > 0) timer -= time->GetDelta();

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

    if (verticalMoveMod == 0 && horizontalMoveMod == 0) return;

    float verticalMove = 100.0f * verticalMoveMod * time->GetDelta();
    float horizontalMove = 100.0f * horizontalMoveMod * time->GetDelta();

    static_cast<Sprite*>(player)->UpdateFrame();

    player->Translate(0, verticalMove);
    player->Translate(horizontalMove, 0);

    // Colisionan player y enemy
    while (CollisionManager::CheckCollision(player, enemy))
    {
        player->Translate(0, -verticalMove);
        player->Translate(-horizontalMove, 0);
    }
}

void Game::Draw()
{
    static_cast<Sprite*>(player)->Draw();
    static_cast<Sprite*>(enemy)->Draw();
}