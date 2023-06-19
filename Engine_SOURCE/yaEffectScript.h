#pragma once
#include "yaScript.h"

namespace ya
{
	class EffectScript : public Script
	{
	public:
		EffectScript();
		virtual ~EffectScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void OnTriggerEnter(Collider2D* collider) override;
		virtual void OnTriggerStay(Collider2D* collider) override;
		virtual void OnTriggerExit(Collider2D* collider) override;

	public:
		void Destroy();
		void SetAutoDestroy(std::wstring name);
		void SetAliveTime(float time);

	private:
		float mAliveTime;
		bool mbUseAliveTime;
	};
}
