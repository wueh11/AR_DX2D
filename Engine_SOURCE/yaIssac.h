#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MeshRenderer;
	class Issac : public GameObject
	{
		struct Info
		{
			int heartMax;
			int heart;
			int soulHeart;
		};

	public:
		Issac();
		virtual ~Issac();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		MeshRenderer* mMr;
	};
}

