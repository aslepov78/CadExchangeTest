// CadExchanger.Lib.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Include/Export.h"

#include "Domain/Curves.h"

using namespace Domain;
using namespace CadExchangerLib;

inline Domain::ICurve* curve(const void* curvePtr)
{
	return (Domain::ICurve*)(curvePtr);
}

DECL_API void* CadExchangerLib::createCurve(CurveType type, double* params)
{
	switch (type)
	{
	case CurveType::Circle:
		return new Domain::Circle(params[0]);

	case CurveType::Elipse:
		return new Domain::Elipse(params[0], params[1]);

	case CurveType::Helix:
		return new Domain::Helix(params[0], params[1]);
	}

	return nullptr;
}

DECL_API void CadExchangerLib::release(void* cadObj)
{
	delete curve(cadObj);
}

DECL_API CurveType CadExchangerLib::getType(const void* curvePtr)
{
	auto* icuve = curve(curvePtr);

	if (dynamic_cast<Domain::Circle*>(icuve))
	{
		return CurveType::Circle;
	}
	else if (dynamic_cast<Domain::Elipse*>(icuve))
	{
		return CurveType::Elipse;
	}
	else if (dynamic_cast<Domain::Helix*>(icuve))
	{
		return CurveType::Helix;
	}

	throw;
}

DECL_API Vector3d CadExchangerLib::getPoint(const void* curvePtr, double t)
{
	return curve(curvePtr)->getPoint(t);
}

DECL_API Vector3d CadExchangerLib::getTangent(const void* curvePtr, double t)
{
	return curve(curvePtr)->getTangent(t);
}

DECL_API PointAndTangent CadExchangerLib::get(const void* curvePtr, double t)
{
	auto* cur = curve(curvePtr);

	PointAndTangent result;
	result.Point = cur->getPoint(t);
	result.Tangent = cur->getTangent(t);

	return result;
}

DECL_API void CadExchangerLib::getParams(const void* curvePtr, void* outParams)
{
	curve(curvePtr)->getParams(outParams);
}

DECL_API double CadExchangerLib::getSumm(void** begin, unsigned stride, unsigned count)
{
	double sum = 0;

	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < count; i++)
	{
		ICurve* curvePtr = *(ICurve**)((unsigned char*)begin + stride * i);

		auto* circle = dynamic_cast<Domain::Circle*>(curvePtr);
		if (circle)
		{
			sum += circle->A;
		}		
	}


	return sum;
}

