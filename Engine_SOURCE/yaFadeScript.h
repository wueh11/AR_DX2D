#pragma once
#include "yaScript.h"
#include "yaCamera.h"

namespace ya
{
	class FadeScript : public Script
	{
	public:
		enum eState
		{
			None,
			FadeIn,
			FadeOut,
			Full,
		};

	public:
		FadeScript();
		virtual ~FadeScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { mCamera = camera; }

		void SetState(eState state) { mState = state; }
		
		float mAlpha;
	private:
		Camera* mCamera;

		eState mState;
	};
}
