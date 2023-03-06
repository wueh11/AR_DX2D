#pragma once
#include "yaEntity.h"
#include "yaLayer.h"
#include "yaGameObject.h"

namespace ya
{
	using namespace ya::enums;
	class Scene : public Entity
	{
	public:
		Scene(eSceneType type);
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		eSceneType GetSceneType() { return mType; }
		void AddGameObject(GameObject* gameObject, const eLayerType type);
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type];}
		std::vector<GameObject*> GetDontDestroyGameObjects();

	private:
		std::vector<Layer> mLayers;
		eSceneType mType;
	};
}

