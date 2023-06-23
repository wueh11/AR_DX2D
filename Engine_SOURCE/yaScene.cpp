#include "yaScene.h"
#include "yaObject.h"
#include "yaFadeScript.h"

namespace ya
{
	Scene::Scene(eSceneType type)
		: mType(type)
	{
		mLayers.resize((UINT)eLayerType::End);
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		{ // fade Object
			mFadeObject = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* fadeObjectTr = mFadeObject->GetComponent<Transform>();
			fadeObjectTr->SetPosition(Vector3(0.0f, 0.0f, -40.0f));
			fadeObjectTr->SetScale(Vector3(10.0f, 8.0f, 1.0f));
			mFadeObject->AddComponent<FadeScript>();
		}

		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destroy();
		}
	}

	void Scene::OnEnter()
	{
		FadeIn();
	}

	void Scene::OnExit()
	{
		FadeOut();
	}

	void Scene::FadeIn()
	{
		FadeScript* script = mFadeObject->GetScript<FadeScript>();

		if (script == nullptr)
			return;

		script->SetState(FadeScript::FadeIn);
	}

	void Scene::FadeOut()
	{
		FadeScript* script = mFadeObject->GetScript<FadeScript>();

		if (script == nullptr)
			return;

		script->SetState(FadeScript::FadeOut);
	}

	void Scene::AddGameObject(GameObject* gameObject, const eLayerType type)
	{
		mLayers[(UINT)type].AddGameObject(gameObject);
		gameObject->SetLayerType(type);
	}

	std::vector<GameObject*> Scene::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> gameObjects;
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*> dontGameObjs = layer.GetDontDestroyGameObjects();

			gameObjects.insert(gameObjects.end(), dontGameObjs.begin(), dontGameObjs.end());
		}

		return gameObjects;
	}

	const std::vector<GameObject*>& Scene::GetGameObjects(const eLayerType type)
	{
		return mLayers[(UINT)type].GetGameObjects();
	}
}