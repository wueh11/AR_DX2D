#pragma once
#include "yaGameObject.h"

namespace ya
{
	class DropBomb : public GameObject
	{
	public:
		DropBomb(Vector3 pos);
		virtual ~DropBomb();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
