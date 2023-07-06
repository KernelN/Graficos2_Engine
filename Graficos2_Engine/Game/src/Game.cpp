#include "Game.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
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
        {YELLOW},
        {YELLOW},
        {YELLOW},
        {YELLOW}
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

    float pColors[8][4] =
    {
        {CYAN},
        {CYAN},
        {CYAN},
        {CYAN},
        {CYAN},
        {CYAN},
        {CYAN},
        {CYAN}
    };

    //player = new Square(s1Colors, true);
    player = new Cube(s1Colors);
    //player->Scale(1, 1);
    //player->Translate(100, 0);

    enemy = new Cube(s2Colors);
    enemy->Scale(25, 25, 25);
    enemy->Translate(0, 0, 50);

    floor = new Cube(floorColors);
    floor->Scale(75, 0, 75);
    floor->Translate(0, -10, 0);

    pointer = new Cube(pColors);
    pointer->SetScale(0.5f, 0.5f, 0.5f);

    
    firstPerson = false;
    SetCameraOffset();

    camera = GetActiveCamera();
    camera->SetFollow(player, cameraOffset);
    camera->FollowTarget(firstPerson);
    camera->LookAtTarget();

    scaleMod = 1;
}

Game::~Game()
{
    delete player;
    delete enemy;
    delete floor;
    delete pointer;
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
    //static_cast<Sprite*>(enemy)->UpdateFrame();

    MovePlayer();

    RotatePlayer();

    camera->FollowTarget(firstPerson);

    Vector3 pointerPos;
    pointerPos = player->GetTranslation() + player->GetForward() * 1;
    pointer->SetTranslation(pointerPos);
    pointer->SetRotation(player->GetRotation());

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
    //static_cast<Cube*>(pointer)->Draw();
}

void Game::SetCameraOffset()
{
    cameraOffset = player->GetForward() * -10 + player->GetUp() * 2.5f;
}

void Game::MoveCamera()
{
    if (firstPerson) return;

    bool changed = false;

    Vector3 camForward = camera->GetForward() * 25.0f * time->GetDelta();
    if (IsKeyPressed(KEY_Z))
    {
        camera->Translate(camForward);
        changed = true;
    }
    else if (IsKeyPressed(KEY_X))
    {
        camera->Translate(camForward * -1);
        changed = true;
    }


    float speed = 10.0f * time->GetDelta();

    if (IsKeyPressed(KEY_LEFT))
    {
        camera->Translate(camera->GetRight() * -speed);
        changed = true;
    }
    else if (IsKeyPressed(KEY_RIGHT))
    {
        camera->Translate(camera->GetRight() * speed);
        changed = true;
    }

    if (IsKeyPressed(KEY_UP))
    {
        camera->Translate(camera->GetUp() * speed);
        changed = true;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        camera->Translate(camera->GetUp() * -speed);
        changed = true;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        camera->LookAtTarget();
        changed = true;
    }

	if (IsKeyPressed(KEY_Q))
	{
		camera->Rotate(0, 25 * time->GetDelta(), 0);
		changed = true;
	}
	else if (IsKeyPressed(KEY_E))
	{
		camera->Rotate(0, -25 * time->GetDelta(), 0);
		changed = true;
	}

    if (!changed) return;


    Vector3 cPos = camera->GetTranslation();
    Vector3 cRot = camera->GetRotation();

    system("cls");
    std::cout
        << "Pos " << cPos.x << " " << cPos.y << " " << cPos.z <<
        std::endl;
    std::cout
        << "Rot " << cRot.x << " " << cRot.y << " " << cRot.z <<
        std::endl;
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

    player->Translate(player->GetForward() * verticalMove);
    player->Translate(player->GetRight() * horizontalMove);
}

void Game::RotatePlayer()
{
    if (!firstPerson) return;

    if (IsKeyPressed(KEY_Q))
        player->Rotate(0, 50.0f * time->GetDelta(), 0);
    else if (IsKeyPressed(KEY_E))
        player->Rotate(0, -50.0f * time->GetDelta(), 0);
}