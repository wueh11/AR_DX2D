#pragma once
#include "yaBaseRenderer.h"
#include "yaMesh.h"
#include "yaMaterial.h"

using namespace ya::graphics;
namespace ya
{
	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
	};
}
