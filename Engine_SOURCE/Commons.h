#pragma once
#include "yaEngine.h"

namespace ya
{
	int random(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}

	float updownMove(float width, float speed, float vertical = false)
	{
		float pos = 0.0f;



		return pos;
	}

	float GetZAxis(float y, float base = 5.0f)
	{
		return base + y * 0.1f;
	}

}