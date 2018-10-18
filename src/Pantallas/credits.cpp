#include "credits.h"

#include <raylib.h>

#include "game.h"
#include "app.h"

using namespace app;
using namespace game;

namespace app
{
	namespace credits
	{
		static char text1[] = "Usando libreria raylib";
		static char text2[] = "Musica realizada con Bosca Ceoil";
		static char text3[] = "Creado por Mariano Martinez";
		static char text4[] = "MENU";
		static char text5[] = "GRAD10S V 0.2";
		static char text6[] = "Sonidos realizados con Bfxr";
		static int sizeText = 0;
		static int sizeText2 = 0;
		static int textPositionX = 0;
		static int textPositionY = 0;
		static int text2PositionX = 0;
		static int text2PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text4PositionX = 0;
		static int text4PositionY = 0;
		static int text5PositionX = 0;
		static int text5PositionY = 0;
		static int text6PositionX = 0;
		static int text6PositionY = 0;

		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;

		static Vector2 mousePoint;
		static Rectangle rect1;
		static Color colorRect1;

		void InitCredits()
		{
			sizeText = (GetScreenWidth() * 30) / scaleAux1;
			sizeText2 = (GetScreenWidth() * 15) / scaleAux1;
			textPositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText) / 2;
			textPositionY = GetScreenHeight() * 0.2452;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText) / 2;
			text2PositionY = GetScreenHeight() * 0.388571;
			text6PositionX = GetScreenWidth() / 2 - MeasureText(text6, sizeText) / 2;
			text6PositionY = GetScreenHeight() * 0.528571;
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, sizeText) / 2;
			text3PositionY = GetScreenHeight() * 0.661428;
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() * 0.80;
			text5PositionX = GetScreenWidth() / 2 - MeasureText(text5, sizeText) / 2;
			text5PositionY = GetScreenHeight() * 0.102857;

			colorRect1 = PURPLE;

			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 170) / scaleAux2;
			rect1.x = GetScreenWidth() / 2 - rect1.width / 2;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.275;
		}

		void UpdateCredits()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Menu;
					ResetValues();
				}
			}
			else colorRect1.a = 255;
		}

		void DrawCredits()
		{
			ClearBackground(BLACK);
			DrawRectangleRec(rect1, colorRect1);
			DrawText(text1, textPositionX, textPositionY, sizeText, GRAY);
			DrawText(text2, text2PositionX, text2PositionY, sizeText, GRAY);
			DrawText(text3, text3PositionX, text3PositionY, sizeText, GRAY);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, BLACK);
			DrawText(text5, text5PositionX, text5PositionY, sizeText, GRAY);
			DrawText(text6, text6PositionX, text6PositionY, sizeText, GRAY);
		}
	}
}