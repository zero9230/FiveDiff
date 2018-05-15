#ifndef _UNITCONVERSION_H_
#define _UNITCONVERSION_H_

#include "DrawObject.h"

class CUnitConversion {
public:
	static void Init( int resolution );
	static double PixelsToInches( int pixels );
	static double PixelsToCentimeters( int pixels );
	static int InchesToPixels( double inches );
	static void InchesToPixels( CDoubleRect& rect );
	static int CentimeterToPixels( double centimeters );
	static int PointsToPixels( double points );
	static void AdjustPixelsToPaper( CDC* dc, CRect& rect );

	static int s_resolution;

};

#endif //_UNITCONVERSION_H_