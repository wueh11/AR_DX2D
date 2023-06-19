#pragma once
#include "yaEngine.h"

namespace ya
{
	static int Random(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}

	static float SinByTime(float speed, float scale = 1.0f)
	{
		float pos = 0.0f;

		auto time = std::chrono::system_clock::now();
		auto mill = duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
		int msc = mill.count() % 10000;
		pos = sin(msc * speed) * scale;

		return pos;
	}

	static float CosByTime(float speed, float scale = 1.0f)
	{
		float pos = 0.0f;

		auto time = std::chrono::system_clock::now();
		auto mill = duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
		int msc = mill.count() % 10000;
		pos = cos(msc * speed) * scale;

		return pos;
	}

	/// <summary>
	/// y축에따라 z값 조정
	/// </summary>
	/// <param name="posY">y 값</param>
	/// <returns></returns>
	static float PositionZ(float posY)
	{
		return -80.0f + (posY * 0.1f);
	}

}