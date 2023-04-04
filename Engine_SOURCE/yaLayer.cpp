#include "yaLayer.h"
#include "yaRenderer.h"
#include "yaTransform.h"
namespace ya
{
	/* // z값 정렬
	static bool compareGameObjectByZAxis(GameObject& a, GameObject& b)
	{
		Transform* aTr = a.GetComponent<Transform>();
		Transform* bTr = b.GetComponent<Transform>();
		
		if (aTr->GetPosition().z <= bTr->GetPosition().z)
			return true;
		
		return false;
	}*/
	
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
		/*for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;

			gameObject->Initialize();
		}*/
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

		// sort z axis
		//std::sort(mGameObjects.begin(), mGameObjects.end(), compareGameObjectByZAxis);
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
		// 삭제할 오브젝트들을 전부 찾아온다.
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
			{
				deleteObjects.insert(gameObj);
			}
		}

		// 지워야할 오브젝트들 게임 오브젝트 모음안에서 삭제
		for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end(); )
		{
			std::set<GameObject*>::iterator deleteIter = deleteObjects.find(*iter);

			if (deleteIter != deleteObjects.end())
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		// 삭제할 오브젝트들을 실제 램(메모리)에서 삭제
		for (GameObject* gameObj : deleteObjects)
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
				iter = mGameObjects.erase(iter); ///erase는 iterator를 사용한다
			}
			else
			{
				iter++; /// erase시 iterator가 erase된곳을 참조하는것을 막기위해 
			}
		}

		return donts;
	}
}