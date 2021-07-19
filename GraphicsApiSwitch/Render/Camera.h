#pragma once

#include "../CommonUtils.h"
#include "MathHelper.h"

class Camera
{
private:
	float m_fTheta;
	float m_fPhi;
	float m_fRadius;

public:
	Camera();

	Camera(
		const Camera& rhs
	);

	Camera& operator=(
		const Camera& rhs
		);

	~Camera();

	inline float GetRadius() { return m_fRadius; }
	inline float GetTheta() { return m_fTheta; }
	inline float GetPhi() { return m_fPhi; }

	void Update(
		float fRadiusDiff,
		float fThetaDiff,
		float fPhiDiff
	);
};