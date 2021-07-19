#include "Camera.h"

Camera::Camera()
	:
	m_fRadius(5.0f),
	m_fTheta(1.5f*MathHelper::Pi),
	m_fPhi(MathHelper::Pi / 4.0f)
{
}

Camera::Camera(
	const Camera& rhs
)
{
	m_fRadius = rhs.m_fRadius;
	m_fPhi = rhs.m_fPhi;
	m_fTheta = rhs.m_fTheta;
}

Camera& Camera::operator=(
	const Camera& rhs
)
{
	Camera lhs;
	lhs.m_fRadius = rhs.m_fRadius;
	lhs.m_fPhi = rhs.m_fPhi;
	lhs.m_fTheta = rhs.m_fTheta;
	return lhs;
}

Camera::~Camera()
{
}

void Camera::Update(
	float fRadiusDiff,
	float fThetaDiff,
	float fPhiDiff
)
{
	m_fRadius += fRadiusDiff;
	m_fTheta += fThetaDiff;
	m_fPhi += fPhiDiff;

	m_fPhi = MathHelper::Clamp(m_fPhi, 0.1f, MathHelper::Pi - 0.1f);
	m_fRadius = MathHelper::Clamp(m_fRadius, 3.0f, 15.0f);
}
