#include "yaTear.h"
#include "yaIsaacEnums.h"

#include "yaIsaacObject.h"
#include "yaRigidbody.h"

namespace ya
{
	Tear::Tear()
		: GameObject()
		, mTearOwner(nullptr)
		, mDirection(Vector3::Zero)
		, mbParabola(false)
	{
		SetName(L"Tear");

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetColliderType(eColliderType::Rect);

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		//rigidbody->SetHeightGround(false);
	}
	Tear::~Tear()
	{
	}
	void Tear::Initialize()
	{
		GameObject::Initialize();
	}
	void Tear::Update()
	{
		GameObject::Update();
	}
	void Tear::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Tear::Render()
	{
		GameObject::Render();
	}

	/// <summary>
	/// tear Initialize
	/// </summary>
	/// <param name="tearOwner">눈물 주체</param>
	/// <param name="dir">방향</param>
	void Tear::InitTear(GameObject* tearOwner, Vector3 dir)
	{
		mTearOwner = tearOwner;
		Transform* ownerTr = mTearOwner->GetComponent<Transform>();

		mDirection = dir;

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(ownerTr->GetPosition() + Vector3(0.0f, -0.32f, 0.0f) + (dir * 0.2f));
		tr->SetScale(Vector3(0.8f, 0.8f, 1.0f));
		tr->SetHeight(0.4f);
		
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		rigidbody->SetHeightGround(!mbParabola);

		IsaacObject* obj = dynamic_cast<IsaacObject*>(tearOwner);
		if(obj != nullptr)
		{
			isaac::Status status = obj->GetStatus();
			mStatus.range = status.range / 2.0f;
			mStatus.tearSpeed = 2.0f + status.tearSpeed;
		}
	}
}