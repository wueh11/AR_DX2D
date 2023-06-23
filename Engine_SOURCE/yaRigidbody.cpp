#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaGameObject.h"

#include "yaInput.h"

namespace ya
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mForce(Vector3::Zero)
		, mVelocity(Vector3::Zero)
		, mAccelation(Vector3::Zero)
		, mFriction(10.0f)
		, mbHeight(false)
		, mbHeightGround(true)
		, mHeightGravity(-5.0f)
		, mHeightVelocity(0.0f)
		, mHeightLimitVelocity(10.0f)
		, mHeightForce(0.0f)
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

		Transform* tr = GetOwner()->GetComponent<Transform>();

		mAccelation = mForce / mMass;

		// 속도에 가속도를 더해준다.
		mVelocity += (mAccelation * Time::DeltaTime());

		if (!mbHeightGround)
		{
			mHeightVelocity += ((mHeightForce / mMass) * Time::DeltaTime());
		}

		if (mbGround)
		{ // 땅
			Vector3 gravity = mGravity;
			gravity.Normalize();

			float dot = gravity.Dot(mVelocity);
			mVelocity -= gravity * dot;
		}
		else
		{ // 공중
			mVelocity += mGravity * Time::DeltaTime();
		}

		if (!mbHeightGround)
		{
			mHeightVelocity += mHeightGravity * Time::DeltaTime();
		}

		// 최대 속도 제한
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


		if (mHeightLimitVelocity < abs(mHeightVelocity))
		{
			mHeightVelocity = mHeightLimitVelocity * (mHeightVelocity /abs(mHeightVelocity));
		}


		// 마찰력 조건 : 적용된 힘이 없고, 속도가 0이 아닐때
		if (!(mVelocity == Vector3::Zero))
		{
			// 속도에 반대 방향
			Vector3 friction = -mVelocity;
			friction.Normalize();
			friction = friction * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.Length() < friction.Length())
				// 속도를 0 로 만든다.
				mVelocity = Vector3::Zero;
			else
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
		}

		// 속도에 맞춰 물체를 이동시킨다.
		Vector3 pos = tr->GetPosition();
		pos += mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);

		// height
		//if(!mbHeightGround)
		{
			float height = tr->GetHeight();

			if (height < 0.0f)
			{
				height = 0.0f;
				mHeightVelocity = 0.0f;
			}
			else
				height += mHeightVelocity * Time::DeltaTime();

			tr->SetHeight(height);
		}

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
		mHeightForce = 0.0f;
	}

	Vector3 Rigidbody::Bounce(Vector3 v1, Vector3 v2)
	{ /// v1 부딪혀오는 대상, v2 부딪히는 벽면
		Vector3 newForce;
		
		// v2의 노말
		Vector3 vl2 = Vector3(v2.y, -v2.x, 0.0f); 

		// v1, v2 내적
		float dot1 = v1.Dot(v2);

		// v2 운동벡터 투영
		Vector3 proj1 = dot1 * v2;

		// v1, v2노말 내적
		float dot2 = v1.Dot(vl2);

		// 노말에 대한 운동벡터 투영
		vl2.Normalize();
		Vector3 proj2 = dot2 * vl2;

		// 투영 반전
		proj2 *= -1;

		//새로운 벡터 구하기
		newForce = proj1 + proj2;

		return newForce;
	}
	void Rigidbody::UseHeight(bool use)
	{
		SetVelocity(Vector3::Zero);
		SetHeightGround(true);
	}
}