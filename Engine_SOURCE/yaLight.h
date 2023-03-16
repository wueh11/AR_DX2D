#pragma once
#include "yaComponent.h"
#include "yaGraphics.h"

namespace ya
{
	class Light : public Component
	{
	public:
		Light();
		virtual ~Light();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		graphics::LightAttribute GetLightAttribute() { return mAttribute; }

		void SetDiffuse(Vector4 diffuse) { mAttribute.diffuse = diffuse; }
		void SetAmbient(Vector4 ambient) { mAttribute.ambient = ambient; }
		void SetLightType(eLightType type) { mAttribute.type = type; }
		void SetRadius(float radius) { mAttribute.radius = radius; }
		void SetAngle(float angle) { mAttribute.angle = angle; }

		Vector4 GetDiffuse() { return mAttribute.diffuse; }
		Vector4 GetAmbient() { return mAttribute.ambient; }
		eLightType GetLightType() { return mAttribute.type; }
		float GetRadius() { return mAttribute.radius; }
		float GetAngle() { return mAttribute.angle; }

	private:
		graphics::LightAttribute mAttribute;
	};
}

