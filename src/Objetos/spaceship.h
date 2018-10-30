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
		void UnloadSpaceship();
		void ResetSpaceship();

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
		extern Shoot bombs[];
		//extern bool pauseSoundShoot;
	}
}
#endif // !SPACESHIP_H
/*
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
*/
