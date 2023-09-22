#include "cyclone/force/AeroControl.h"

using namespace cyclone;

AeroControl::AeroControl(const Matrix3& base, const Matrix3& min, const Matrix3& max,
	const Vector3& position, const Vector3* windspeed)
	:
	Aero(base, position, windspeed)
{
	AeroControl::minTensor = min;
	AeroControl::maxTensor = max;
	controlSetting = 0.0f;
}

Matrix3 AeroControl::getTensor()
{
	if (controlSetting <= -1.0f) return minTensor;
	else if (controlSetting >= 1.0f) return maxTensor;
	else if (controlSetting < 0)
	{
		return Matrix3::linearInterpolate(minTensor, tensor, controlSetting + 1.0f);
	}
	else if (controlSetting > 0)
	{
		return Matrix3::linearInterpolate(tensor, maxTensor, controlSetting);
	}
	else return tensor;
}

void AeroControl::setControl(real value)
{
	controlSetting = value;
}

void AeroControl::updateForce(RigidBody* body, real duration)
{
	updateForceFromTensor(body, duration, getTensor());
}