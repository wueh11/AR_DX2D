#include "yaCollisionManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			for (UINT column = 0; column < (UINT)eLayerType::End; column++)
			{
				if (mLayerCollisionMatrix[row][column])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)column);
				}
			}
		}
	}

	void CollisionManager::FixedUpdate()
	{
	}

	void CollisionManager::Render()
	{
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int column = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			column = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			column = (UINT)left;
		}

		mLayerCollisionMatrix[row][column] = enable;
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if (left->GetState() != GameObject::eState::Active)
				continue;
			if (left->GetComponent<Collider2D>() == nullptr)
				continue;
			if (!left->GetComponent<Collider2D>()->IsActive())
				continue;

			for (GameObject* right : rights)
			{
				if (right->GetState() != GameObject::eState::Active)
					continue;
				if (right->GetComponent<Collider2D>() == nullptr)
					continue;
				if (!right->GetComponent<Collider2D>()->IsActive())
					continue;
				if (left == right)
					continue;

				ColliderCollision(left->GetComponent<Collider2D>(), right->GetComponent<Collider2D>());
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체 레이어로 구성된 ID 확인
		ColliderID colliderID;
		colliderID.left = (UINT)left->GetID();
		colliderID.right = (UINT)right->GetID();

		// 이전 충돌 정보를 검색한다.
		// 만약에 충돌정보가 없는 상태라면 충돌정보를 생성해준다.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// 충돌 체크를 해준다.
		if (Intersect(left, right)) // 충돌을 한 상태
		{
			// 충돌 Enter
			if (iter->second == false)
			{
				if (left->IsTrigger())
					left->OnTriggerEnter(right);
				else
					left->OnCollisionEnter(right);

				if (right->IsTrigger())
					right->OnTriggerEnter(left);
				else
					right->OnCollisionEnter(left);

				iter->second = true;
			}
			else // 충돌 Stay
			{
				if (left->IsTrigger())
					left->OnTriggerStay(right);
				else
					left->OnCollisionStay(right);

				if (right->IsTrigger())
					right->OnTriggerStay(left);
				else
					right->OnCollisionStay(left);
			}
		}
		else // 충돌하지 않은 상태
		{
			// 충돌 Exit
			if (iter->second == true)
			{
				if (left->IsTrigger())
					left->OnTriggerExit(right);
				else
					left->OnCollisionExit(right);

				if (right->IsTrigger())
					right->OnTriggerExit(left);
				else
					right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		if (left->GetColliderType() == eColliderType::Circle && right->GetColliderType() == eColliderType::Circle)
		{ // hw Circle vs Circle
			float dist2 = (left->GetSize().x / 2.0f) + (right->GetSize().x / 2.0f);

			Vector3 leftPos = left->GetPosition();
			Vector3 rightPos = right->GetPosition();

			float dist = sqrt(pow(leftPos.x - rightPos.x, 2) + pow(leftPos.y - rightPos.y, 2));

			if (dist2 < dist)
			{
				return false;
			}
		}
		else
		{ // Rect
			// Rect vs Rect
			// 0 --- 1
			// |     | 
			// 3 --- 2   => index 순서

			static const Vector3 arrLocalPos[4] =
			{
				Vector3{ -0.5f,  0.5f,  0.0f },
				Vector3{  0.5f,  0.5f,  0.0f },
				Vector3{  0.5f, -0.5f,  0.0f },
				Vector3{ -0.5f, -0.5f,  0.0f }
			};

			Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
			Transform* rightTr = right->GetOwner()->GetComponent<Transform>();
			
			if (leftTr->GetHeight() > 1.0f || rightTr->GetHeight() > 1.0f)
				return false;


			Matrix leftMat = leftTr->GetWorldMatrix();
			Matrix rightMat = rightTr->GetWorldMatrix();

			// 분리축 벡터 4개 구하기 (투영벡터)
			Vector3 Axis[4] = {};

			Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
			Matrix finalLeft = Matrix::CreateScale(leftScale);
			finalLeft *= leftMat;

			Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
			Matrix finalRight = Matrix::CreateScale(rightScale);
			finalRight *= rightMat;

			Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
			Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
			Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
			Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

			Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
			Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

			for (size_t i = 0; i < 4; i++)
				Axis[i].z = 0.0f; /// 2D

			Vector3 leftPos = left->GetPosition();
			Vector3 rightPos = right->GetPosition();

			//Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
			Vector3 vc = leftPos - rightPos;
			vc.z = 0.0f;

			Vector3 centerDir = vc; /// centerDir : 사각형 중심사이의 거리를 내적한 값

			for (size_t i = 0; i < 4; i++)
			{
				Vector3 vA = Axis[i];
				vA.Normalize(); /// 방향만 사용

				float projDist = 0.0f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vA) / 2.0f); /// 투영벡터 -> 내적의 스칼라 값
				}

				if (projDist < fabsf(centerDir.Dot(vA))) /// 사각형 중심끼리의 내적 값보다 사각형 각각의 내적값의 합이 더 작은경우 -> 충돌 X
				{
					return false;
				}
			}
		}

		return true;
	}
}