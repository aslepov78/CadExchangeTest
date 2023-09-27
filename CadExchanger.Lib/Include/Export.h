#include "CommonTypes.h"

#ifdef CADEXCHANGERLIB_EXPORTS
#define DECL_API __declspec(dllexport)
#else
#define DECL_API __declspec(dllimport)
#endif


namespace CadExchangerLib
{
	DECL_API void* createCurve(CurveType type, double* params);

	DECL_API void release(void* cadObj);

	DECL_API CurveType getType(const void* curvePtr);

	DECL_API Vector3d getPoint(const void* curvePtr, double t);

	DECL_API Vector3d getTangent(const void* curvePtr, double t);

	DECL_API PointAndTangent get(const void* curvePtr, double t);

	DECL_API void getParams(const void* curvePtr, void* outParams);

	DECL_API double getSumm(void** begin, unsigned stride, unsigned count);
}


