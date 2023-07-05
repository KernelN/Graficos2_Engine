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

    float floorColors[8][4] =
    {
        {WHITE},
        {WHITE},
        {WHITE},
        {WHITE},
        {WHITE},
        {WHITE},
        {WHITE},
        {WHITE}
    };

    //player = new Square(s1Colors, true);
    player = new Cube(s1Colors);
    //player->Scale(1, 1);
    //player->Translate(100, 0);

    enemy = new Cube(s2Colors);
    enemy->Scale(25, 25, 25);
    enemy->Translate(0, 0, 75);

    floor = new Cube(floorColors);
    floor->Scale(100, 0, 100);
    floor->Translate(0, -10, 0);

    camera = GetActiveCamera();
    camera->SetFollow(player, {0, 0, 50});


    firstPerson = false;
    scaleMod = 1;
}

Game::~Game()
{
    delete player;
    delete enemy;
    delete floor;
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
    if (IsKeyPressed(KEY_ENTER))
    {
        firstPerson = !firstPerson;
        if (firstPerson)
			camera->SetFollow(player, { 0,0, player->GetScale().z});
        else
        {
            camera->SetFollow(player, { 0,0,50 });
            camera->LookAtTarget();
        }
    }

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
    static_cast<Cube*>(floor)->Draw();
}

void Game::MoveCamera()
{
    Vector3 camForward = camera->GetForward() * 25.0f * time->GetDelta();
    if (IsKeyPressed(KEY_Z))
        camera->Translate(camForward);
    else if (IsKeyPressed(KEY_X))
        camera->Translate(camForward * -1);

    float speed = 10.0f * time->GetDelta();

    if (IsKeyPressed(KEY_LEFT))
        camera->Translate(camera->GetRight() * -speed);
    else if (IsKeyPressed(KEY_RIGHT))
        camera->Translate(camera->GetRight() * speed);

    if (IsKeyPressed(KEY_UP))
        camera->Translate(camera->GetUp() * speed);
    else if (IsKeyPressed(KEY_DOWN))
        camera->Translate(camera->GetUp() * -speed);

    if (IsKeyPressed(KEY_SPACE))
        camera->LookAtTarget();

    if (firstPerson) return;

    if (IsKeyPressed(KEY_Q))
        camera->Rotate(0, 5.0f * time->GetDelta(), 0);
    else if (IsKeyPressed(KEY_E))
        camera->Rotate(0, -5.0f * time->GetDelta(), 0);
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



    if (verticalMoveMod == 0 && horizontalMoveMod == 0) return;

    float verticalMove = 100.0f * verticalMoveMod * time->GetDelta();
    float horizontalMove = 100.0f * horizontalMoveMod * time->GetDelta();

    //static_cast<Sprite*>(player)->UpdateFrame();

    player->Translate(0, verticalMove);
    player->Translate(horizontalMove, 0);
}

void Game::RotatePlayer()
{
    if (!firstPerson) return;

    if (IsKeyPressed(KEY_Q))
        player->Rotate(0, 50.0f * time->GetDelta(), 0);
    else if (IsKeyPressed(KEY_E))
        player->Rotate(0, -50.0f * time->GetDelta(), 0);
}