#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MeshRenderer;
	class Isaac : public GameObject
	{
		struct Info
		{
			int heartMax;
			int heart;
			int soulHeart;
		};

	public:
		Isaac();
		virtual ~Isaac();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		MeshRenderer* mMr;
	};
}

