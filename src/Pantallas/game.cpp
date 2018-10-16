#include "game.h"

#include <raylib.h>

#include "spaceship.h"
#include "app.h"

using namespace app;
using namespace	spaceship;

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

			backImage = LoadImage("res/fondo.png");

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
			
			InitSpaceship();
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
			UpdateSpaceship();
			
		}

		void UpdateFrame()
		{
			Input();
			Update();
		}

		void Draw()
		{
			ClearBackground(BLANK);
			DrawTexture(backTexture,0,0,WHITE);
			
			DrawSpaceship();

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