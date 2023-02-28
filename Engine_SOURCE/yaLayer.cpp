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
			{
				int a = 0;
				continue;
			}

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

	void Layer::Destroy()
	{
		std::set<GameObject*> deleteObjects;
		// ������ ������Ʈ���� ���� ã�ƿ´�
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
			{
				deleteObjects.insert(gameObj);
			}
		}

		// �������� ������Ʈ�� ���� ������Ʈ�� ���� �ȿ��� ����
		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin(); iter < mGameObjects.end();)
		{
			std::set<GameObject*>::iterator deleteIter = deleteObjects.find(*iter);

			if (deleteIter != deleteObjects.end())
			{
				mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		// ������ ������Ʈ���� ���� �޸� ����
		for (GameObject* gameObj : mGameObjects)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}

	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> donts;

		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin(); iter < mGameObjects.end();)
		{
			if ((*iter)->IsDontDestroy() == true)
			{
				donts.push_back((*iter));
				mGameObjects.erase(iter); ///erase�� iterator�� ����Ѵ�
			}
			else
			{
				iter++; /// erase�� iterator�� erase�Ȱ��� �����ϴ°��� �������� 
			}
		}

		return donts;
	}


}