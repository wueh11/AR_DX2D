#include "yaLayer.h"



namespace ya
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;

			delete gameObject;
			gameObject = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;

			gameObject->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;
			if (gameObject->GetState() != GameObject::eState::Active)
				continue;

			gameObject->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;
			if (gameObject->GetState() != GameObject::eState::Active)
				continue;

			gameObject->FixedUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;
			if (gameObject->GetState() != GameObject::eState::Active)
				continue;

			gameObject->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}
}