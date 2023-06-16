#pragma once
#include "yaGameObject.h"
#include "yaIsaacEnums.h"

namespace ya
{
	class Tear : public GameObject
	{
	public:
		Tear();
		virtual ~Tear();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		GameObject* GetTearOwner() { return mTearOwner; }
		//void SetTearOwner(GameObject* obj) { mTearOwner = obj; }

		Vector3 GetDirection() { return mDirection;}
		//void SetDirection(Vector3 dir) { mDirection = dir; }

		void InitTear(GameObject* tearOwner, Vector3 dir);

		isaac::Status GetStatus() { return mStatus; }

		void Parabola(bool parabola) { mbParabola = parabola; }
		bool IsParabola() { return mbParabola; }

	protected:
		GameObject* mTearOwner;
		Vector3 mDirection;

		isaac::Status mStatus;

		bool mbParabola;
	};
}
