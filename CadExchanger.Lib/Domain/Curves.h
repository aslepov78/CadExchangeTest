#pragma once

#define _USE_MATH_DEFINES

#include <cmath>

#include "../Include/CommonTypes.h"
#include "ICurve.h"

namespace Domain
{
	class Elipse : public ICurve
	{
	public:

		const double A, B;

		Elipse(double a = 1, double b = 1) :A(a), B(b)
		{}

		Vector3d getPoint(double t) override;
		Vector3d getTangent(double t) override;
		void getParams(void* outPrams) override;
	};

	class Circle : public Elipse
	{
	public:

		Circle(double radius = 1) :Elipse(radius, radius)
		{}

		void getParams(void* outPrams) override;
	};

	class Helix : public ICurve
	{
		const double Radius;
		const double Step;
		const double StepDiv2PI;

	public:

		Helix(double radius = 1, double step = 1) : Radius(radius), Step(step), StepDiv2PI(step / (2 * M_PI))
		{}

		void getParams(void* outPrams) override;
		Vector3d getPoint(double t) override;
		Vector3d getTangent(double t) override;
	};
}
