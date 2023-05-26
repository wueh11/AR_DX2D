#pragma once
#include "yaLand.h"

namespace ya
{
	class Rock : public Land
	{
	public:
		enum class eRockType
		{
			None,
			Rock,
			RockItem,
			Rock2x1,
			Rock1x2,
			Rock2x2,
			Iron,
			Jar,
		}; 

	public:
		Rock();
		virtual ~Rock();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		eRockType GetRockType() { return mRockType; }
		void SetRockType(eRockType rockType);

	private:
		eRockType mRockType;
	};
}
