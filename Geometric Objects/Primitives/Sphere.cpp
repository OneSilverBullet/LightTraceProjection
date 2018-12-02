// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class sphere

#include "Sphere.h"
#include "math.h"

const double Sphere::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

Sphere::Sphere(void)	
	: 	GeometricObject(),
		center(0.0),
		radius(1.0)
{}


// ---------------------------------------------------------------- constructor

Sphere::Sphere(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r)
{}


// ---------------------------------------------------------------- clone

Sphere* 
Sphere::clone(void) const {
	return (new Sphere(*this));
}


// ---------------------------------------------------------------- copy constructor

Sphere::Sphere (const Sphere& sphere)
	: 	GeometricObject(sphere),
		center(sphere.center),
		radius(sphere.radius)
{}



// ---------------------------------------------------------------- assignment operator

Sphere& 
Sphere::operator= (const Sphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Sphere::~Sphere(void) {}


//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	//依据当前球体的隐式方程与光线相碰撞来计算出对应的碰撞信息
	//球体的隐式方程：（p-c）*(p-c)=r*r  p为向量，c为球心，r为半径
 
	Vector3D	temp 	= ray.o - center;  
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;  //计算的依据量
	
	if (disc < 0.0)  //该值不存在，根号下不能为复数
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // 最终的计算结果，依据t的不同情况决定碰撞位置。
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	}
	
	return (false);
}








