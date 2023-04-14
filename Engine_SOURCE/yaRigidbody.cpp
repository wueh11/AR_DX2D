#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaGameObject.h"

namespace ya
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mForce(Vector3::Zero)
		, mVelocity(Vector3::Zero)
		, mAccelation(Vector3::Zero)
		, mFriction(5.0f)
	{
		mGravity = Vector3(0.0f, 0.0f, 0.0f);
		mbGround = true;
		mLimitVelocity = Vector3(3.0f, 3.0f, 0.0f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::FixedUpdate()
	{
	}

	void Rigidbody::Update()
	{
		// F = M X A
		// A = F / M

		if (mMass == 0.0f)
			return;

		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� �����ش�.
		mVelocity += (mAccelation * Time::DeltaTime());

		if (mbGround)
		{ // ��
			Vector3 gravity = mGravity;
			gravity.Normalize();

			float dot = gravity.Dot(mVelocity);
			mVelocity -= gravity * dot;
		}
		else
		{ // ����
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �ִ� �ӵ� ����
		Vector3 gravity = mGravity;
		gravity.Normalize();
		float dot = gravity.Dot(mVelocity);
		gravity = gravity * dot;

		Vector3 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}

		mVelocity = gravity + sideVelocity;

		// ������ ���� : ����� ���� ����, �ӵ��� 0�� �ƴҶ�
		if (!(mVelocity == Vector3::Zero))
		{
			// �ӵ��� �ݴ� ����
			Vector3 friction = -mVelocity;
			friction.Normalize();
			friction = friction * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.Length() < friction.Length())
				// �ӵ��� 0 �� �����.
				mVelocity = Vector3::Zero;
			else
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				mVelocity += friction;
		}

		// �ӵ��� ���� ��ü�� �̵���Ų��.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos += mVelocity * Time::DeltaTime();

		tr->SetPosition(pos);

		ClearForce();
	}

	void Rigidbody::Render()
	{
	}

	void Rigidbody::AddForce(Vector3 force)
	{
		mForce += force;
	}
	void Rigidbody::ClearForce()
	{
		mForce = Vector3::Zero;
	}

	Vector3 Rigidbody::Bounce(Vector3 v1, Vector3 v2)
	{ /// v1 �ε������� ���, v2 �ε����� ����
		Vector3 newForce;
		
		// v2�� �븻
		Vector3 vl2 = Vector3(v2.y, -v2.x, 0.0f); 

		// v1, v2 ����
		float dot1 = v1.Dot(v2);

		// v2 ����� ����
		Vector3 proj1 = dot1 * v2;

		// v1, v2�븻 ����
		float dot2 = v1.Dot(vl2);

		// �븻�� ���� ����� ����
		vl2.Normalize();
		Vector3 proj2 = dot2 * vl2;

		// ���� ����
		proj2 *= -1;

		//���ο� ���� ���ϱ�
		newForce = proj1 + proj2;

		return newForce;
	}
}