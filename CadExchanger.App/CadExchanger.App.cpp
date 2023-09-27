#define _USE_MATH_DEFINES

#include <algorithm>
#include <iostream>
#include <vector>

#include "Export.h"
#include "ClientSide.h"

using namespace std;

using namespace CadExchangerLib;

ostream& operator << (ostream& os, const Vector3d& v) {
    return (os << "{" << v.X << ", " << v.Y << ", " << v.Z << "}");
}


double randDouble()
{
    return (double)std::rand() / RAND_MAX;
}

int main()
{
    std::cout << "2. Populate a container..\n";

    //2. Populate a container (e.g. vector or list) of objects of these types created in random manner with
    // random parameters.
    std::vector<CurvePtr> curves;
    {
	    for (unsigned i = 0; i < 100; i++)
	    {
            CurveType type = (CurveType)(std::rand() % 3);

            double params[2];
            
            //radius
            params[0] = randDouble();

            if (type != Circle)
            {
                params[1] = randDouble();
            }

	    	auto newCurve = CurveProxy::Create(type, params);
            curves.push_back(newCurve);
	    }
    }

    std::cout << "3. Print coordinates of points and derivatives of all curves in the container at t=PI/4\n";
    //3. Print coordinates of points and derivatives of all curves in the container at t=PI/4.
    auto t = M_PI / 4;
    for (const auto& curve : curves)
    {
        auto pointAndTangent = curve->get(t);

        std::cout << "Curve: " << curve->Type() << ", ";
        std::cout << "Point: " << pointAndTangent.Point << " Tangent: " << pointAndTangent.Tangent << std::endl;
    }

    //4. Populate a second container that would contain only circles from the first container. Make sure the
    //second container shares(i.e. not clones) circles of the first one, e.g.via pointers.
    {
        std::vector<CurvePtr> onlyCircles(curves.size());
        onlyCircles.clear();
        for (const auto curve : curves)
        {
            if (curve->Type() == CurveType::Circle)
            {
                onlyCircles.push_back(curve);
            }
        }
        
        //5. Sort the second container in the ascending order of circles’ radii.That is, the first element has the
        //   smallest radius, the last - the greatest.
        std::sort(onlyCircles.begin(), onlyCircles.end(), [](CurvePtr l, CurvePtr r)
            {
                double lR, rR;

                l->getParams(&lR);
                r->getParams(&rR);

                return lR < rR;
            });

        //6. Compute the total sum of radii of all curves in the second container

        //direct sum
    	double summRadius = 0;
    	for (const auto& circle : onlyCircles)
        {
            double r;
            circle->getParams(&r);
            summRadius += r;
        }

        double sumByServer = CurveProxy::getSum(onlyCircles.data(), onlyCircles.size());

        std::cout << "Circles count = " << onlyCircles.size() << std::endl;
        std::cout << "Circles radius sum = " << summRadius << std::endl;
    }
    
}


