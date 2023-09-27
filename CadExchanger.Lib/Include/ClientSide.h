#pragma once

#include "CommonTypes.h"
#include "Export.h"

namespace CadExchangerLib
{
	class CurveProxy;

	typedef std::shared_ptr<CurveProxy> CurvePtr;

	class CurveProxy
	{
		
		CurveProxy()
		{}		

	public:

		static CurvePtr Create(CurveType type, double* params)
		{
			auto* ptr = createCurve(type, params);
			return CurvePtr((CurveProxy*)ptr, CadExchangerLib::release);
		}

		static double getSum(CurveProxy** begin, unsigned count)
		{
			return getSumm((void**)begin, sizeof(CurveProxy*), count);
		}

		static double getSum(CurvePtr* begin, unsigned count)
		{
			return getSumm((void**)begin, sizeof(CurvePtr), count);
		}

		inline CurveType Type() const
		{
			return getType(this);
		}

		inline Vector3d getPoint(double t) const
		{
			return CadExchangerLib::getPoint(this, t);
		}

		inline Vector3d getTangent(double t) const
		{
			return CadExchangerLib::getTangent(this, t);
		}

		inline PointAndTangent get(double t) const
		{
			return CadExchangerLib::get(this, t);
		}

		inline void getParams(void* outParams) const
		{
			return CadExchangerLib::getParams(this, outParams);
		}
	};
	
}
