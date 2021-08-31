#pragma once

#include "Vec3.h"
#include "Color.h"
#include <iostream>
#include "ConvertToScreen.h"

Vec3f clamp(Vec3f vec) {
	return Vec3f(vec.x > 1.0 ? 1.0 : vec.x, vec.y > 1.0 ? 1.0 : vec.y, vec.z > 1.0 ? 1.0 : vec.z);
}

Vec3f calculateIntensity(const Vec3f& Ka, const Vec3f& Kd, const Vec3f& Ks, const float ns, Vec3f& point,Vec3f& light, const Vec3f& view, const Vec3f& normal, const Vec3f& Ia, const Vec3f& Il)
{
	const Vec3f ambientColor = Ka * Ia;
	Vec3f lightVec = light - point;
	const Vec3f unitLight = lightVec.Normalize(lightVec);
	const Vec3f diffuseColor = Kd * Il * normal.dot(unitLight);
	const Vec3f reflection = (normal * 2.0 * normal.dot(unitLight)) - unitLight;
	//HERE IS THE MISTAKE
	float power = pow(view.dot(reflection), ns);
	const Vec3f specularColor = Ks * Il * power;
	const Vec3f intensity = clamp(ambientColor + diffuseColor + specularColor);
	//Color intensityColor = { intensity.x, intensity.y, intensity.z };
	return intensity;
}
