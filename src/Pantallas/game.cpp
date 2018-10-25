#include "game.h"

#include <raylib.h>

#include "meteors.h"
#include "spaceship.h"
#include "app.h"

using namespace app;
using namespace	spaceship;
using namespace	meteors;

namespace app
{
	namespace game
	{
		extern bool victory = false;
		extern bool gameOver = false;
		static char text[] = "W A S D : movimiento, CLICK IZQ: Disparar";
		static int sizeText;
		static float textPositionX;
		static float textPositionY;

		//Imagenes y texturas

		static Image backImage;
		static Texture2D backTexture;
		static Image backImage2;
		static Texture2D backTexture2;

		Rectangle frameRec;
		float currentFrame;

		int framesCounter;
		int framesSpeed;

		Rectangle frameRec2;
		float currentFrame2;

		int framesCounter2;
		int framesSpeed2;

		//Boton pausa

		static Rectangle botonPausa1;
		static Rectangle botonPausa2;
		static Color colorRect;
		static Vector2 mousePoint;

		static bool init;

		void InitValues()
		{
			sizeText = (GetScreenWidth() * 20) / 1600;
			textPositionX = GetScreenWidth()*0.01f;
			textPositionY = GetScreenHeight() * 0.97f;

			backImage = LoadImage("res/parallax.png");
			backImage2 = LoadImage("res/parallax2.png");

			//init boton pausa
			botonPausa1.x = GetScreenWidth()*0.96f;
			botonPausa1.y = GetScreenHeight()*0.02f;
			botonPausa1.height = (GetScreenWidth() * 40) / 1600;
			botonPausa1.width = (GetScreenWidth() * 15) / 1600;
			botonPausa2.x = GetScreenWidth()*0.975f;
			botonPausa2.y = GetScreenHeight()*0.02f;
			botonPausa2.height = (GetScreenWidth() * 40) / 1600;
			botonPausa2.width = (GetScreenWidth() * 15) / 1600;
			colorRect = GRAY;

			backTexture = LoadTextureFromImage(backImage);
			backTexture2 = LoadTextureFromImage(backImage2);

			frameRec = { 0.0f, 0.0f, (float)backTexture.width, (float)backTexture.height };
			currentFrame = 0;

			framesCounter = 0;
			framesSpeed = 1;

			frameRec2 = { 0.0f, 0.0f, (float)backTexture2.width, (float)backTexture2.height };
			currentFrame2 = 0;

			framesCounter2 = 0;
			framesSpeed2 = 1;
			
			InitSpaceship();
			InitMeteors();
		}
		

		static void Input()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, botonPausa1))
			{
				colorRect.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}
			else colorRect.a = 255;

			if (CheckCollisionPointRec(mousePoint, botonPausa2))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}

		}

		

		static void Update()
		{
			framesCounter++;

			if (framesCounter >= (60 / framesSpeed))
			{
				framesCounter = 0;
				currentFrame+=0.2;

				if (currentFrame > 1600) currentFrame = 0;

				frameRec.x = (float)currentFrame;
			}
			framesCounter2++;

			if (framesCounter2 >= (60 / framesSpeed2))
			{
				framesCounter2 = 0;
				currentFrame2 += 1;

				if (currentFrame2 > 1280) currentFrame2 = 0;

				frameRec2.x = (float)currentFrame2;
			}

			UpdateSpaceship();
			UpdateMeteors();
		}

		void UpdateFrame()
		{
			Input();
			Update();
		}

		void Draw()
		{
			ClearBackground(BLANK);
			DrawTextureRec(backTexture, frameRec, { 0,0 }, WHITE);
			DrawTextureRec(backTexture2, frameRec2, { 0,0 }, WHITE);

			DrawSpaceship();
			DrawMeteors();

			DrawRectangleRec(botonPausa1, colorRect);
			DrawRectangleRec(botonPausa2, colorRect);
			DrawText(text, textPositionX, textPositionY, sizeText, PURPLE);
		}

		void ResetValues()
		{
			InitValues();
			gameOver = false;
		}
	}
}