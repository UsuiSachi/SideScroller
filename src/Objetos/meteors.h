#ifndef METEORS_H
#define METEORS_H

#include <raylib.h>

namespace app
{
	namespace meteors
	{
		struct Meteor
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			Color color;
		};

		void InitMeteors();
		void UpdateMeteors();
		void DrawMeteors();

		extern bool pauseSoundExplosion;
	}
}
#endif // !METEORS_H
