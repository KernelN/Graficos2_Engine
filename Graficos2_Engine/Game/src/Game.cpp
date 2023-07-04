#include "Game.h"
#include <iostream>
#include "Utility/KeyCodes.h"
#include "Utility/Color.h"
#include "Utility/TimeSingleton.h"

unsigned int spriteNum = 0;
float timer = 0;

Game::Game()
{
    float s1Colors[8][4] =
    {
        {RED},
        {RED},
        {RED},
        {RED},
        {RED},
        {RED},
        {RED},
        {RED}
    };

    float s2Colors[8][4] =
    {
        {GREEN},
        {GREEN},
        {GREEN},
        {GREEN},
        {GREEN},
        {GREEN},
        {GREEN},
        {GREEN}
    };

    //player = new Square(s1Colors, true);
    player = new Cube(s1Colors);
    //player->Scale(1, 1);
    //player->Translate(100, 0);

    enemy = new Cube(s2Colors);
    enemy->Scale(25, 25, 25);
    enemy->Translate(-100, 0);

    camera = GetActiveCamera();
    camera->SetFollow(player, {0, 0, 50});


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
    camera->FollowTarget();
    
    //static_cast<Sprite*>(enemy)->UpdateFrame();

    MovePlayer();

    MoveCamera();

    // Colisionan player y enemy
    //while (collisionManager->CheckCollision(player, enemy))
    //{
    //    player->Translate(0, -verticalMove);
    //    player->Translate(-horizontalMove, 0);
    //}
}

void Game::Draw()
{
    static_cast<Cube*>(player)->Draw();
    static_cast<Cube*>(enemy)->Draw();
}

void Game::MoveCamera()
{
    Vector3 camForward = camera->GetForward() * 25.0f * time->GetDelta();
    if (IsKeyPressed(KEY_Z))
        camera->Translate(camForward.x, camForward.y, camForward.z);
    else if (IsKeyPressed(KEY_X))
        camera->Translate(-camForward.x, -camForward.y, -camForward.z);

    if (IsKeyPressed(KEY_LEFT))
        camera->Translate(-50.0f * time->GetDelta(), 0, 0);
    else if (IsKeyPressed(KEY_RIGHT))
        camera->Translate(50.0f * time->GetDelta(), 0, 0);

    if (IsKeyPressed(KEY_UP))
        camera->Translate(0, 50.0f * time->GetDelta(), 0);
    else if (IsKeyPressed(KEY_DOWN))
        camera->Translate(0, -50.0f * time->GetDelta(), 0);

    if(IsKeyPressed(KEY_Q))
        camera->Rotate(0, 50.0f * time->GetDelta(), 0);
    else if(IsKeyPressed(KEY_E))
        camera->Rotate(0, -50.0f * time->GetDelta(), 0);


    if (IsKeyPressed(KEY_SPACE))
        camera->LookAtTarget();
}

void Game::MovePlayer()
{
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


    //if (IsKeyPressed(KEY_Q))
    //    player->Rotate(0, 50.0f * time->GetDelta(), 0);
    //else if (IsKeyPressed(KEY_E))
    //    player->Rotate(0, -50.0f * time->GetDelta(), 0);


    if (verticalMoveMod == 0 && horizontalMoveMod == 0) return;

    float verticalMove = 100.0f * verticalMoveMod * time->GetDelta();
    float horizontalMove = 100.0f * horizontalMoveMod * time->GetDelta();

    //static_cast<Sprite*>(player)->UpdateFrame();

    player->Translate(0, verticalMove);
    player->Translate(horizontalMove, 0);
}