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
		// �浹ü�� ���� ������ŭ�� ������ �ȴ� /// �̸� ������ �浹ü ������ �ʿ��ϸ� transform ��ȯ�Ͽ� ����Ҽ� ����
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

		//�׸��� �������� �Ű���� �Ѵ�.
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

		tr->FixedUpdate(); /// �ٲﰪ ����

		Camera::SetGpuViewMatrix(renderer::mainCamera->GetViewMatrix()); /// ī�޶��� ������ matrix�� UI�� �ɷ��ֱ� ������ ������ matrix�� �ٽ� �����ִ� �۾�
		Camera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());

		debugObj->Render();
	}
}