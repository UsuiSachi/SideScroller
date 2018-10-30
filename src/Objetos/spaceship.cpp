#include "spaceship.h"

#include <cmath>

#include "pause.h"
#include "game.h"
#include "app.h"

using namespace app;
using namespace game;
using namespace pause;

namespace app
{
	namespace spaceship
	{
		extern const int shipMaxShoots = 10;
		extern const int shipMaxBombs = 5;
		Spaceship ship;
		static float shipBaseSize = 20.0f;
		static float shipSpeed = 200.0f;
		static float shipAcc = 10.0f;
		static float shipHeight;
		static const float shipColliderZ = 24.0f;
		static const float speedBoost = 3.5f; //variable para que la velocidad se ajuste al GetFrameTime
		Shoot shoot[shipMaxShoots];
		Shoot bombs[shipMaxBombs];

		//Imagenes y texturas
		static Image shipImage;
		static Image shootImage;
		static Image bombImage;
		static Texture2D backTexture;
		static Texture2D shootTexture;
		static Texture2D bombTexture;
		static Texture2D shipTexture;
		static Rectangle sourceRect;
		static Rectangle destRec;

		//Escala las texturas
		static float shipScale;
		static float shootScale;
		static float bombScale;
		static Vector2 shootScalePos;
		static Vector2 bombScalePos;

		static Rectangle frameRec;
		static int currentFrame;

		static float framesCounter;
		static float framesSpeed;

		//Sonidos 
		/*static Sound shootSound;
		bool pauseSoundShoot = false;*/

		static Vector2 mousePoint;

		static bool init;
		static int scaleAux = 1600;

		void InitSpaceship()
		{
			//shootSound = LoadSound("res/assets/shoot.wav");
			shootImage = LoadImage("res/assets/shoot.png");
			shipImage = LoadImage("res/assets/spriteSheet.png");
			bombImage = LoadImage("res/assets/bomb.png");


			shipTexture = LoadTextureFromImage(shipImage);
			shootTexture = LoadTextureFromImage(shootImage);
			bombTexture = LoadTextureFromImage(bombImage);
			sourceRect.height = shipTexture.height;
			sourceRect.width = shipTexture.width;
			sourceRect.x = 0;
			sourceRect.y = 0;

			shipHeight = (shipBaseSize / 2) / tanf(20 * DEG2RAD);

			ship.position.x = GetScreenWidth()*0.1f;
			ship.position.y = GetScreenHeight() / 2 - shipHeight / 2;
			ship.acceleration = { 0, 0 };
			ship.speed = { 0, 0 };
			ship.rotation = 90;
			ship.collider = { ship.position.x + shipHeight * 1.5f , ship.position.y + shipHeight, shipColliderZ };
			ship.color = LIGHTGRAY;

			frameRec = { 0.0f, 0.0f, (float)shipTexture.width, (float)shipTexture.height / 4 };
			currentFrame = 0;

			framesCounter = 0;
			framesSpeed = 0.05f;

			for (int i = 0; i < shipMaxShoots; i++)
			{
				shoot[i].position = { 0, 0 };
				shoot[i].speed = { 0, 0 };
				shoot[i].radius = 3;
				shoot[i].active = false;
				shoot[i].color = WHITE;
			}
			for (int i = 0; i < shipMaxBombs; i++)
			{
				bombs[i].position = { 0, 0 };
				bombs[i].speed = { 0, 10 };
				bombs[i].radius = 20;
				bombs[i].active = false;
				bombs[i].color = WHITE;
			}
			shipScale = (GetScreenWidth()* 0.08f) / scaleAux;
			shootScale = (GetScreenWidth()* 1.0f) / scaleAux;
			shootScalePos = { (shootScale*shootImage.width) / 2 ,(shootScale*shootImage.height) / 2 };
			bombScale = (GetScreenWidth()* 1.0f) / scaleAux;
			bombScalePos = { (bombScale*bombImage.width) / 2 ,(bombScale*bombImage.height) / 2 };

			destRec.width = shipTexture.width;
			destRec.height = shipTexture.height;

		}

		void Input()
		{
			ship.rotation = 90;
			mousePoint = GetMousePosition();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				/*if (!pauseSoundShoot)
				{
					PlaySound(shootSound);
				}
				else
				{
					PauseSound(shootSound);
				}*/
				init = true;
				for (int i = 0; i < shipMaxShoots; i++)
				{
					if (!shoot[i].active)
					{
						shoot[i].position = { (ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight * 2)), (ship.position.y + shipHeight) };
						shoot[i].active = true;
						shoot[i].speed.x = speedBoost * sin(ship.rotation*DEG2RAD)*shipSpeed;
						shoot[i].speed.y = speedBoost * cos(ship.rotation*DEG2RAD)*shipSpeed;
						shoot[i].rotation = ship.rotation;
						break;
					}

				}
			}
			if (IsKeyDown(KEY_A))
			{
				ship.position.x -= GetFrameTime() * shipSpeed;
			}
			if (IsKeyDown(KEY_D))
			{
				ship.position.x += GetFrameTime() * shipSpeed;
			}
			if (IsKeyDown(KEY_W))
			{
				ship.position.y -= GetFrameTime() * shipSpeed;
			}
			if (IsKeyDown(KEY_S))
			{
				ship.position.y += GetFrameTime() * shipSpeed;
			}
			if (IsKeyPressed(KEY_F))
			{
				for (int i = 0; i < shipMaxBombs; i++)
				{
					if (!bombs[i].active)
					{
						bombs[i].position = { (ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight * 2)), (ship.position.y + shipHeight) };
						bombs[i].active = true;
						bombs[i].speed.x = speedBoost * sin(ship.rotation*DEG2RAD)*shipSpeed;
						bombs[i].speed.y = speedBoost * cos(ship.rotation*DEG2RAD)*shipSpeed;
						bombs[i].rotation = ship.rotation;
					}
				}
			}
		}



		void Update()
		{

			if (!gameOver)
			{
				framesCounter += GetFrameTime();

				if (framesCounter >= framesSpeed)
				{
					framesCounter = 0;
					currentFrame++;

					if (currentFrame > 4) currentFrame = 0;

					frameRec.y = (float)currentFrame*(float)shipTexture.height / 4;
				}

				// Player logic: movement
				destRec.x = ship.position.x;
				destRec.y = ship.position.y;

				// Collision logic: player vs walls
				if (ship.position.x >= GetScreenWidth() - shipHeight * 2)
				{
					ship.position.x = GetScreenWidth() - shipHeight * 2;
				}
				else if (ship.position.x < (shipHeight / 2))
				{
					ship.position.x = shipHeight / 2;
				}
				if (ship.position.y > (GetScreenHeight() - shipHeight * 2))
				{
					ship.position.y = GetScreenHeight() - shipHeight * 2;
				}
				else if (ship.position.y < (shipHeight / 2))
				{
					ship.position.y = shipHeight / 2;
				}

				// Shot logic
				for (int i = 0; i < shipMaxShoots; i++)
				{
					if (shoot[i].active)
					{
						// Movement
						shoot[i].position.x += shoot[i].speed.x*GetFrameTime();
						shoot[i].position.y -= shoot[i].speed.y*GetFrameTime();

						// Collision logic: shoot vs walls
						if (shoot[i].position.x > GetScreenWidth() + shoot[i].radius)
						{
							shoot[i].active = false;
						}
						else if (shoot[i].position.x < 0 - shoot[i].radius)
						{
							shoot[i].active = false;
						}
						if (shoot[i].position.y > GetScreenHeight() + shoot[i].radius)
						{
							shoot[i].active = false;
						}
						else if (shoot[i].position.y < 0 - shoot[i].radius)
						{
							shoot[i].active = false;
						}
					}
					//bomb logic
					if (bombs[i].active)
					{
						//Movement
						bombs[i].position.y -= bombs[i].speed.y*GetFrameTime();
						bombs[i].position.x += bombs[i].speed.x*GetFrameTime();

						//Bombs collission vs walls
						if (bombs[i].position.x > GetScreenWidth() + bombs[i].radius)
						{
							bombs[i].active = false;
						}
						else if (bombs[i].position.x < 0 - bombs[i].radius)
						{
							bombs[i].active = false;
						}
						if (bombs[i].position.y > GetScreenHeight() + bombs[i].radius)
						{
							bombs[i].active = false;
						}
						else if (bombs[i].position.y < 0 - bombs[i].radius)
						{
							bombs[i].active = false;
						}
					}
				}
				ship.collider = { ship.position.x + shipHeight * 1.5f, ship.position.y + shipHeight, shipColliderZ };
			}
		}

		void UpdateSpaceship()
		{
			Input();
			Update();
		}

		void DrawSpaceship()
		{
			Vector2 v1 = { ship.position.x + sinf(ship.rotation*DEG2RAD)*(shipHeight), ship.position.y - cosf(ship.rotation*DEG2RAD)*(shipHeight) };
			Vector2 v2 = { ship.position.x - cosf(ship.rotation*DEG2RAD)*(shipBaseSize / 2), ship.position.y - sinf(ship.rotation*DEG2RAD)*(shipBaseSize / 2) };
			Vector2 v3 = { ship.position.x + cosf(ship.rotation*DEG2RAD)*(shipBaseSize / 2), ship.position.y + sinf(ship.rotation*DEG2RAD)*(shipBaseSize / 2) };
			DrawTextureRec(shipTexture, frameRec, ship.position, WHITE);
			for (int i = 0; i < shipMaxShoots; i++)
			{
				if (shoot[i].active)
				{
					DrawTextureEx(shootTexture, { shoot[i].position.x - shootScalePos.x ,shoot[i].position.y - shootScalePos.y }, 0, shootScale, WHITE);
				}
				if (bombs[i].active)
				{
					DrawTextureEx(bombTexture, { bombs[i].position.x - bombScalePos.x ,bombs[i].position.y - bombScalePos.y }, 0, bombScale, WHITE);
				}
			}
		}

		void UnloadSpaceship()
		{
			//UnloadSound(shootSound);
			UnloadTexture(shipTexture);
			UnloadTexture(shootTexture);
			UnloadTexture(bombTexture);
			UnloadImage(shootImage);
			UnloadImage(bombImage);
			UnloadImage(shipImage);
		}

		void ResetSpaceship()
		{
			sourceRect.height = shipTexture.height;
			sourceRect.width = shipTexture.width;
			sourceRect.x = 0;
			sourceRect.y = 0;

			shipHeight = (shipBaseSize / 2) / tanf(20 * DEG2RAD);

			ship.position.x = GetScreenWidth()*0.1f;
			ship.position.y = GetScreenHeight() / 2 - shipHeight / 2;
			ship.acceleration = { 0, 0 };
			ship.speed = { 0, 0 };
			ship.rotation = 90;
			ship.collider = { ship.position.x + shipHeight * 1.5f , ship.position.y + shipHeight, shipColliderZ };
			ship.color = LIGHTGRAY;

			frameRec = { 0.0f, 0.0f, (float)shipTexture.width, (float)shipTexture.height / 4 };
			currentFrame = 0;

			framesCounter = 0;
			framesSpeed = 0.05f;

			for (int i = 0; i < shipMaxShoots; i++)
			{
				shoot[i].position = { 0, 0 };
				shoot[i].speed = { 0, 0 };
				shoot[i].radius = 3;
				shoot[i].active = false;
				shoot[i].color = WHITE;
			}
			for (int i = 0; i < shipMaxBombs; i++)
			{
				bombs[i].position = { 0, 0 };
				bombs[i].speed = { 0, 10 };
				bombs[i].radius = 20;
				bombs[i].active = false;
				bombs[i].color = WHITE;
			}
			shipScale = (GetScreenWidth()* 0.08f) / scaleAux;
			shootScale = (GetScreenWidth()* 1.0f) / scaleAux;
			shootScalePos = { (shootScale*shootImage.width) / 2 ,(shootScale*shootImage.height) / 2 };
			bombScale = (GetScreenWidth()* 1.0f) / scaleAux;
			bombScalePos = { (bombScale*bombImage.width) / 2 ,(bombScale*bombImage.height) / 2 };

			destRec.width = shipTexture.width;
			destRec.height = shipTexture.height;
		}
	}
}