#pragma once

struct Vector3d
{
	double X;
	double Y;
	double Z;

	Vector3d()
	{}

	Vector3d(double x, double y, double z = 0) :X(x), Y(y), Z(z)
	{}
};

struct PointAndTangent
{
	Vector3d Point;
	Vector3d Tangent;
};

enum CurveType : unsigned
{
	Circle = 0,
	Elipse = 1,
	Helix = 2,
};