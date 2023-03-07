#pragma once
class UIheart
{
};

#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MeshRenderer;
	class UIheart : public GameObject
	{
		struct Info
		{
			int heartMax;
			int heart;
			int soulHeart;
		};

	public:
		UIheart();
		virtual ~UIheart();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		MeshRenderer* mMr;
	};
}

