#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <raylib.h>

namespace app
{
	namespace spaceship
	{
		void InitSpaceship();
		void UpdateSpaceship();
		void DrawSpaceship();

		struct Spaceship
		{
			Vector2 position;
			Vector2 speed;
			Vector2 acceleration;
			float rotation;
			Vector3 collider;
			Color color;
		};

		struct Shoot
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			float rotation;
			bool active;
			Color color;
		};
		
		extern Spaceship ship;
		extern const int shipMaxShoots;
		extern Shoot shoot[];
		extern bool pauseSoundShoot;
	}
}
#endif // !SPACESHIP_H
