#pragma once
#include "yaGameObject.h"

namespace ya
{
	class EffectObject : public GameObject
	{
	public:
		EffectObject();
		virtual ~EffectObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
	/*	void Init();
		void Play();*/

	protected:
		GameObject* mEffectObjectOwner;
		Animator* mAnimator;

		bool mbAutoDestroy;
	};
}
