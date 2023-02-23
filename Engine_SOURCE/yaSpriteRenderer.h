#pragma once
#include "yaBaseRenderer.h"
#include "yaMesh.h"
#include "yaMaterial.h"

using namespace ya::graphics;
namespace ya
{
	class SpriteRenderer : public BaseRenderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
	};
}
