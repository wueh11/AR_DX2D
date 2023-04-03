#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Tear : public GameObject
	{
	public:
		Tear(GameObject* owner, Vector3 direction);
		virtual ~Tear();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		Vector3 GetDirection() { return mDirection;}
		GameObject* GetProjectileOwner() { return mProjectileOwner; }

	private:
		GameObject* mProjectileOwner;
		Vector3 mDirection;
	};
}
