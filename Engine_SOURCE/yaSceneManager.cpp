#include "yaSceneManager.h"

#include "yaPlayScene.h"
#include "yaTitleScene.h"
#include "yaWorkScene.h"
#include "yaBasement1.h"

namespace ya
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::vector<Scene*> SceneManager::mScenes = {};

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Work] = new WorkScene();
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Basement1] = new Basement1();

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr) continue;

			mActiveScene = scene;
			scene->Initialize();
		}

		mActiveScene = mScenes[(UINT)eSceneType::Title];
		//mActiveScene = mScenes[(UINT)eSceneType::Work];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		// �ٲ�� dontDestroy ������Ʈ�� ���������� ���� �Ѱ�����Ѵ�.
		std::vector<GameObject*> gameObjs = mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mScenes[(UINT)type];

		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}

		mActiveScene->OnEnter();
	}
}