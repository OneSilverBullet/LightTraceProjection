// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Plane.h"

const double Plane::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Plane::Plane(void)	
	: 	GeometricObject(),
		a(0.0),
		n(0, 1, 0)						
{}


// ----------------------------------------------------------------------  constructor

Plane::Plane(const Point3D& point, const Normal& normal)
	:	GeometricObject(),
		a(point),
		n(normal)
{
		n.normalize();
}


// ---------------------------------------------------------------- copy constructor

Plane::Plane(const Plane& plane) 
	:	GeometricObject(plane),
		a(plane.a),
		n(plane.n) 				
{}


// ---------------------------------------------------------------- clone

Plane* 
Plane::clone(void) const {
	return (new Plane(*this));
}


// ---------------------------------------------------------------- assignment operator

Plane& 
Plane::operator= (const Plane& rhs)	{
	
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	a = rhs.a;
	n = rhs.n;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Plane::~Plane(void)				
{}


// ----------------------------------------------------------------- hit

bool 															 
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	float t = (a - ray.o) * n / (ray.d * n);  //依据公式计算出唯一的碰撞点参数t
	//注意：如果光线与平面平行的话，那么ray.d*n会为0。C++/0操作为INF，因此不会导致渲染器崩溃。

	//如果t>kEpsilon，那么更新ShadeRec的信息，将光线碰撞信息写入其中。
	if (t > kEpsilon) {
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t * ray.d;
		
		return (true);	
	}

	return(false);
}


