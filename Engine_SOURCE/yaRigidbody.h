#pragma once
#include "yaComponent.h"

using namespace ya::math;
namespace ya
{	/// ����
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void AddForce(Vector3 force);
		void ClearForce();
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		bool IsGround() { return mbGround; }
		Vector3 Bounce(Vector3 v1, Vector3 v2);

		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
		Vector3 GetVelocity() { return mVelocity; }

		void SetLimitVelocity(Vector3 limit) { mLimitVelocity = limit; }

	private:
		// ���� �������� �̿��� �̵�
		float mMass;		/// ����
		Vector3 mForce;		/// ��ü�� �̴� ��
		Vector3 mVelocity;	/// ������ ���� �ӵ�
		Vector3 mAccelation;/// ���ӵ�
		float mFriction;	/// ������

		// �߷��� �̿��� ����
		Vector3 mGravity;	/// �߷� ũ��
		bool mbGround;		/// ���鿡 �پ��ִ���
		Vector3 mLimitVelocity;	/// �������� �ӵ� �Ѱ谪
	};
}