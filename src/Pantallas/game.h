#ifndef GAME_H
#define GAME_H

namespace app
{
	namespace game
	{
		void InitValues();
		void UpdateFrame();
		void Draw();
		void ResetValues();

		extern bool victory;
		extern bool gameOver;
	}
}
#endif // !GAME_H