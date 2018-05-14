/* ==========================================================================
	Class :			CUnitConversion

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CUnitConversion" contains static functions to convert 
					different kinds of length units.

	Description :	The class contains some function to convert between 
					inches and pixels, for example, based on the current 
					resolution set with "Init".

	Usage :			The class must be initialized with "CUnitConversion::Init" 
					before use.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "UnitConversion.h"

void CUnitConversion::Init( int resolution )
/* ============================================================
	Function :		CUnitConversion::Init
	Description :	Initializes the class.
	Access :		Public

	Return :		void
	Parameters :	int resolution	-	Resolution to use for 
										the conversions.
					
	Usage :			Must be called to initialize the resolution 
					used for the conversions.

   ============================================================*/
{

	CUnitConversion::s_resolution = resolution;

}

double CUnitConversion::PixelsToInches( int pixels )
/* ============================================================
	Function :		CUnitConversion::PixelsToInches
	Description :	Converts "pixels" from pixels to inches.
	Access :		Public

	Return :		double		-	Resulting inches
	Parameters :	int pixels	-	Pixels to convert
					
	Usage :			Call to convert between pixels and inches.

   ============================================================*/
{

	return static_cast< double >( pixels ) / static_cast< double >( CUnitConversion::s_resolution );

}

double CUnitConversion::PixelsToCentimeters( int pixels )
/* ============================================================
	Function :		CUnitConversion::PixelsToCentimeters
	Description :	Convert "pixels" pixels to centimeters
	Access :		Public

	Return :		double		-	Resulting centimeters
	Parameters :	int pixels	-	Pixels to convert
					
	Usage :			Call to convert from pixels to centimeters.

   ============================================================*/
{

	double pixelspercentimeter = static_cast< double >( CUnitConversion::s_resolution ) / 2.54;
	return pixelspercentimeter / static_cast< double >( pixels );

}

int CUnitConversion::InchesToPixels( double inches )
/* ============================================================
	Function :		CUnitConversion::InchesToPixels
	Description :	Converts "inches" inches to pixels
	Access :		Public

	Return :		int				-	Resulting pixels
	Parameters :	double inches	-	Inches to convert
					
	Usage :			Call to convert from inches to pixels

   ============================================================*/
{

	return static_cast< int >( static_cast< double >( CUnitConversion::s_resolution ) * inches + .5 );

}

void CUnitConversion::InchesToPixels( CDoubleRect& rect )
/* ============================================================
	Function :		CUnitConversion::InchesToPixels
	Description :	Convert "rect" from inches to pixels.
	Access :		Public

	Return :		void
	Parameters :	CDoubleRect& rect	-	Rectangle to convert.
					
	Usage :			Call to convert a rectangle from inches to 
					pixels.

   ============================================================*/
{

	rect.top = InchesToPixels( rect.top );
	rect.bottom = InchesToPixels( rect.bottom );
	rect.left = InchesToPixels( rect.left );
	rect.right = InchesToPixels( rect.right );

}

int CUnitConversion::CentimeterToPixels( double centimeters )
/* ============================================================
	Function :		CUnitConversion::CentimeterToPixels
	Description :	Converts "centimeters" centimeters to pixels.
	Access :		Public

	Return :		int					-	Resulting pixels
	Parameters :	double centimeters	-	Centimeters to convert
					
	Usage :			Call to convert from centimeters to pixels

   ============================================================*/
{

	double pixelspercentimeter = static_cast< double >( CUnitConversion::s_resolution ) / 2.54;
	return static_cast< int >( pixelspercentimeter * centimeters + .5 );

}

int CUnitConversion::PointsToPixels( double points )
/* ============================================================
	Function :		CUnitConversion::PointsToPixels
	Description :	Converts "points" typographical points to 
					pixels.
	Access :		Public

	Return :		int				-	Resulting pixels
	Parameters :	double points	-	Points to convert
					
	Usage :			Call to convert between typographical points 
					and pixels.

   ============================================================*/
{

	double pixelsperpoint = static_cast< double >( CUnitConversion::s_resolution ) / 72;
	return static_cast< int >( pixelsperpoint * points + .5 );

}

void CUnitConversion::AdjustPixelsToPaper( CDC* dc, CRect& rect )
/* ============================================================
	Function :		CUnitConversion::AdjustPixelsToPaper
	Description :	The function adjusts a paper, taking the 
					hardware margin of the printer into account
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	CDC to adjust for
					CRect& rect	-	Rectangle to adjust
					
	Usage :			Will work on a screen CDC as well.

   ============================================================*/
{
	int topOffset = dc->GetDeviceCaps( PHYSICALOFFSETY );
	int leftOffset = dc->GetDeviceCaps( PHYSICALOFFSETX );
	rect.OffsetRect( -leftOffset, -topOffset );

}

int CUnitConversion::s_resolution = 0;
