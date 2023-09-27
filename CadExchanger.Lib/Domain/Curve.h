#pragma once

#define _USE_MATH_DEFINES

#include <cmath>

#include "Include/CommonTypes.h"


namespace Domain
{
	class ICurve
	{
	public:

		virtual Vector3d getPoint(double t) = 0;

		virtual Vector3d getTangent(double t) = 0;

		virtual void getParams(void* outPrams)
		{}
	};

	class Elipse : public ICurve
	{
	public:

		const double A, B;

		Elipse(double a = 1, double b = 1) :A(a), B(b)
		{}

		Vector3d getPoint(double t) override
		{
			return Vector3d(A * cos(t), B * sin(t), 0);
		}

		Vector3d getTangent(double t) override
		{
			return Vector3d(-A * sin(t), B * cos(t), 0);
		}

		void getParams(void* outPrams) override
		{
			double* dParams = (double*)outPrams;
			dParams[0] = A;
			dParams[1] = B;
		}
	};

	class Circle : public Elipse
	{
	public:

		Circle(double radius = 1) :Elipse(radius, radius)
		{}

		void getParams(void* outPrams) override
		{
			double* dParams = (double*)outPrams;
			dParams[0] = A;			
		}
	};

	class Helix : public ICurve
	{
		const double Radius;
		const double Step;
		const double StepDiv2PI;

	public:

		Helix(double radius = 1, double step = 1) : Radius(radius), Step(step), StepDiv2PI(step / (2 * M_PI))
		{
			
		}

		void getParams(void* outPrams) override
		{
			double* dParams = (double*)outPrams;
			dParams[0] = Radius;
			dParams[1] = Step;
		}

		Vector3d getPoint(double t) override
		{
			return Vector3d(Radius * cos(t), Radius * sin(t), StepDiv2PI * t);
		}

		Vector3d getTangent(double t) override
		{
			return Vector3d(-Radius * sin(t), Radius * cos(t), StepDiv2PI);
		}
	};
}
