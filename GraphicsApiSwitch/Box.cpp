#include "Box.h"

Box::Box()
{
	m_Position = Windows::Foundation::Numerics::float3::zero();
}

Box::Box(
	const Box& rhs
)
{
	m_Position = rhs.m_Position;
}

Box& Box::operator=(
	const Box& rhs
)
{
	Box lhs;
	lhs.m_Position = rhs.m_Position;
	return lhs;
}

Box::~Box()
{

}

void Box::SetPosition(
	float x,
	float y,
	float z
)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
