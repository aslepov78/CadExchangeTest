#pragma once

#include "../Include/CommonTypes.h"

namespace Domain
{
	class ICurve
	{
	public:

		virtual ~ICurve()
		{}

		virtual Vector3d getPoint(double t) = 0;

		virtual Vector3d getTangent(double t) = 0;

		virtual void getParams(void* outPrams)
		{}
	};
}
