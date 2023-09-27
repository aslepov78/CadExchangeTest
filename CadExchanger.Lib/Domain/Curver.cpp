#include "pch.h"

#include "Curves.h"

using namespace Domain;

Vector3d Elipse::getPoint(double t)
{
	return Vector3d(A * cos(t), B * sin(t), 0);
}

Vector3d Elipse::getTangent(double t)
{
	return Vector3d(-A * sin(t), B * cos(t), 0);
}

void Elipse::getParams(void* outPrams)
{
	double* dParams = (double*)outPrams;
	dParams[0] = A;
	dParams[1] = B;
}


void Circle::getParams(void* outPrams)
{
	double* dParams = (double*)outPrams;
	dParams[0] = A;
}


void Helix::getParams(void* outPrams)
{
	double* dParams = (double*)outPrams;
	dParams[0] = Radius;
	dParams[1] = Step;
}

Vector3d Helix::getPoint(double t)
{
	return Vector3d(Radius * cos(t), Radius * sin(t), StepDiv2PI * t);
}

Vector3d Helix::getTangent(double t)
{
	return Vector3d(-Radius * sin(t), Radius * cos(t), StepDiv2PI);
}