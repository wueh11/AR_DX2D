#include "yaEditor.h"

#include "yaResources.h"
#include "yaMesh.h"
#include "yaMaterial.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaGridScript.h"
#include "yaDebugObject.h"
#include "yaObject.h"

namespace ya
{
	void Editor::Initialize()
	{
		// 충돌체의 종류 갯수만큼만 있으면 된다 /// 미리 만들어둔 충돌체 종류를 필요하면 transform 변환하여 사용할수 잇음
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"DebugMaterial");

		{ /// rect
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"DebugRectMesh");

			mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
			MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();

			renderer->SetMaterial(material);
			renderer->SetMesh(rectMesh);
		}

		{ /// circle
			std::shared_ptr<Mesh> circleMesh = Resources::Find<Mesh>(L"CircleMesh");

			mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
			MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();

			renderer->SetMaterial(material);
			renderer->SetMesh(circleMesh);
		}

		//그리드 이쪽으로 옮겨줘야 한다.
		{ // Grid Object
			EditorObject* gridObject = new EditorObject();
			MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
			gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridScript = gridObject->AddComponent<GridScript>();
			gridScript->SetCamera(mainCamera);

			mEditorObjects.push_back(gridObject);
		}
	}
	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::FixedUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->FixedUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (DebugMesh& mesh : renderer::debugMeshes)
		{
			DebugRender(mesh);
		}
		renderer::debugMeshes.clear();
	}

	void Editor::Release()
	{
		for (auto obj : mWidgets)
		{
			delete obj;
			obj = nullptr;
		}

		for (EditorObject* obj : mEditorObjects)
		{
			delete obj;
			obj = nullptr;
		}

		delete mDebugObjects[(UINT)eColliderType::Rect];
		delete mDebugObjects[(UINT)eColliderType::Circle];
	}

	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		Transform* tr = debugObj->GetComponent<Transform>();
		tr->SetPosition(mesh.position);
		tr->SetRotation(mesh.rotation);

		if (mesh.type == eColliderType::Rect)
			tr->SetScale(mesh.scale);
		else
			tr->SetScale(Vector3(mesh.radius));

		BaseRenderer* renderer = debugObj->GetComponent<BaseRenderer>();

		tr->FixedUpdate(); /// 바뀐값 적용

		Camera::SetGpuViewMatrix(renderer::mainCamera->GetViewMatrix()); /// 카메라의 마지막 matrix가 UI에 걸려있기 때문에 메인의 matrix로 다시 돌려주는 작업
		Camera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());

		debugObj->Render();
	}
}