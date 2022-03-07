#ifndef _RG_INTSECIMPLICIT4_H
#define _RG_INTSECIMPLICIT4_H
		  
#include "rg_Const.h"
#include "rg_BzCurve2D.h"
#include "rg_Polynomial.h"
#include "rg_ImplicitEquation.h"
#include "rg_dList.h"
#include "rg_Point2D.h"
#include "rg_ComplexNumber.h"

class rg_IntsecImplicit4
{
public:
	rg_IntsecImplicit4();
	~rg_IntsecImplicit4();

	rg_dList<rg_Point2D>   intersectBzCurveVsBzCurve(const rg_BzCurve2D &curve_s, 
											   const rg_BzCurve2D &curve_t, 
											   rg_REAL &time);
	rg_dList<rg_Point2D>   intersectBzCurveVsBzCurve(const rg_BzCurve2D &curve_s, 
											   const rg_BzCurve2D &curve_t, 
											   rg_Polynomial  &poly);
	rg_ImplicitEquation implicitize(const rg_BzCurve2D &curve);
	rg_REAL           inversion(const rg_BzCurve2D &curve, 
							   const rg_Point2D &point);
};

#endif // rg_IntsecImplicit4 class


