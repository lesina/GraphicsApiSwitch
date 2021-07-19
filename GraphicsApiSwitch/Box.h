#pragma once

#include <Windowsnumerics.h>

#include "CommonUtils.h"

class Box
{
private:
	Windows::Foundation::Numerics::float3 m_Position;

public:
	Box();

	Box(
		const Box& rhs
	);

	Box& operator=(
		const Box& rhs
	);

	~Box();

	void SetPosition(
		float x,
		float y,
		float z
	);

	float x() { return m_Position.x; }
	float y() { return m_Position.y; }
	float z() { return m_Position.z; }
};

