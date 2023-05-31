#include "yaCollectibleScript.h"

#include "yaObject.h"
#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaImageRenderer.h"

#include "yaResources.h"
#include "yaRigidbody.h"

namespace ya
{
	CollectibleScript::CollectibleScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mAltar(nullptr)
		, mItemType(eItemType::None)
		, mCollideVelocity(Vector3::Zero)
	{
	}
	CollectibleScript::~CollectibleScript()
	{
	}
	void CollectibleScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();

		mAltar = object::Instantiate<GameObject>(eLayerType::Land, mTransform);
		Transform* altarTr = mAltar->GetComponent<Transform>();
		altarTr->SetPosition(Vector3(0.1f, -0.4f, 1.0f));
		altarTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"itemaltarMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		ImageRenderer* rd = mAltar->AddComponent<ImageRenderer>();
		rd->SetMesh(mesh);
		rd->SetMaterial(material);
		rd->SetImageSize(texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetCenter(Vector2(0.06f, -0.24f));
		collider->SetSize(Vector2(0.4f, 0.32f));

	}
	void CollectibleScript::Update()
	{
	}
	void CollectibleScript::FixedUpdate()
	{
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(Vector3(pos.x, pos.y, -80.0f + (pos.y * 0.1f)));
	}
	void CollectibleScript::Render()
	{
	}

	void CollectibleScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			Transform* otherTr = other->GetComponent<Transform>();
			Vector3 otherPos = collider->GetPosition();

			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();
			Transform* ownerTr = GetOwner()->GetComponent<Transform>();

			Vector3 dist = Vector3(
				ownerCollider->GetSize().x * ownerTr->GetScale().x / 2.0f + collider->GetSize().x * otherTr->GetScale().x / 2.0f 
				, ownerCollider->GetSize().y * ownerTr->GetScale().y / 2.0f + collider->GetSize().y * otherTr->GetScale().y / 2.0f
				, 0.0f);

			if (otherPos.x >= ownerCollider->GetPosition().x + dist.x - 0.01f
				|| otherPos.x <= ownerCollider->GetPosition().x - dist.x + 0.01f)
			{
				if (collider->GetPosition().x > ownerCollider->GetPosition().x)
					otherPos.x = ownerCollider->GetPosition().x + dist.x + 0.002f;
				else
					otherPos.x = ownerCollider->GetPosition().x - dist.x - 0.002f;
			}

			if (otherPos.y >= ownerCollider->GetPosition().y + dist.y - 0.01f
				|| otherPos.y <= ownerCollider->GetPosition().y - dist.y + 0.01f)
			{
				if (collider->GetPosition().y > ownerCollider->GetPosition().y)
					otherPos.y = ownerCollider->GetPosition().y + dist.y + 0.002f;
				else
					otherPos.y = ownerCollider->GetPosition().y - dist.y - 0.002f;
			}

			otherPos.x -= collider->GetCenter().x;
			otherPos.y -= collider->GetCenter().y;

			otherTr->SetPosition(otherPos);

			Rigidbody* objRigidbody = other->GetComponent<Rigidbody>();
			if (objRigidbody != nullptr)
				objRigidbody->SetVelocity(Vector3::Zero);
		}
	}

	void CollectibleScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Transform* otherTr = other->GetComponent<Transform>();
		Vector3 otherPos = collider->GetPosition();

		Rigidbody* objRigidbody = other->GetComponent<Rigidbody>();

		if (objRigidbody == nullptr)
			return;

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
		}
		else
		{
			Collider2D* ownerCollider = other->GetComponent<Collider2D>();

			Vector3 target = Vector3(0.0f, 0.0f, 0.0f);
			if (collider->GetPosition().x > ownerCollider->GetPosition().x - (ownerCollider->GetSize().x / 2)
				|| collider->GetPosition().x < ownerCollider->GetPosition().x + (ownerCollider->GetSize().x / 2))
				target.y = 1.0f;
			else if (collider->GetPosition().y > ownerCollider->GetPosition().y - (ownerCollider->GetSize().y / 2)
				|| collider->GetPosition().y < ownerCollider->GetPosition().y + (ownerCollider->GetSize().y / 2))
				target.x = 1.0f;

			Vector3 force = objRigidbody->Bounce(-mCollideVelocity, target);
			objRigidbody->AddForce(force * 100.0f);
		}
	}
	void CollectibleScript::OnCollisionExit(Collider2D* collider)
	{
		mCollideVelocity = Vector3::Zero;
	}
	void CollectibleScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void CollectibleScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void CollectibleScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void CollectibleScript::Pause()
	{
		GetOwner()->Pause();
	}
	void CollectibleScript::Death()
	{
		GetOwner()->Death();
	}
}