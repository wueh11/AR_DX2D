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
		, mFriction(10.0f)
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
			//float dot = math::Dot(mVelocity, gravity); /// ���⿡ ���� �߷� ũ�� ������
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
		//float dot = math::Dot(mVelocity, gravity);
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

		mForce = Vector3::Zero; // clear
	}

	void Rigidbody::Render()
	{
	}

	void Rigidbody::AddForce(Vector3 force)
	{
		mForce += force;
		int a = 0;
	}
}