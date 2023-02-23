#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject);
		const std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
	};

	typedef const std::vector<GameObject*>& GameObjects;
}
