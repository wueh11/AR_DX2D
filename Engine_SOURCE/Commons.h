#pragma once
#include "yaEngine.h"

namespace ya
{
	static int random(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}

	static float updownMove(float width, float speed, float vertical = false)
	{
		float pos = 0.0f;

		return pos;
	}

}