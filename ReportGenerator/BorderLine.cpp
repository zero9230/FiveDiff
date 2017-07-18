/* ==========================================================================
	File :			BorderLine.cpp
	
	Class :			CBorderLine

	Date :			07/27/04

	Purpose :		"CBorderLine" represents a drawable line and is used 
					for borders and row/column dividers by the drawing 
					objects.

	Description :	The class is a simple container for line attributes.

	Usage :			Used as a part of another drawing object.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "BorderLine.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CBorderLine::CBorderLine() : m_visible( FALSE ),
m_style( 0 ),
m_color( RGB( 0, 0, 0 ) ),
m_thickness( 0 )
/* ============================================================
	Function :		CBorderLine::CBorderLine
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

CBorderLine::~CBorderLine()
/* ============================================================
	Function :		CBorderLine::~CBorderLine
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

}

BOOL CBorderLine::GetVisible() const
/* ============================================================
	Function :		CBorderLine::GetVisible
	Description :	Accessor. Getter for "m_visible".
	Access :		Public
					
	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_visible".

   ============================================================*/
{

	return m_visible;

}

void CBorderLine::SetVisible( BOOL value )
/* ============================================================
	Function :		CBorderLine::SetVisible
	Description :	Accessor. Setter for "m_visible".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	Value of the attribute

	Usage :			Call to set the value of "m_visible".

   ============================================================*/
{

	m_visible = value;

}

int CBorderLine::GetStyle() const
/* ============================================================
	Function :		CBorderLine::GetStyle
	Description :	Accessor. Getter for "m_style".
	Access :		Public
					
	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_style".

   ============================================================*/
{

	return m_style;

}

void CBorderLine::SetStyle( int value )
/* ============================================================
	Function :		CBorderLine::SetStyle
	Description :	Accessor. Setter for "m_style".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	Value of the attribute

	Usage :			Call to set the value of "m_style".

   ============================================================*/
{

	m_style = value;

}

COLORREF CBorderLine::GetColor() const
/* ============================================================
	Function :		CBorderLine::GetColor
	Description :	Accessor. Getter for "m_color".
	Access :		Public
					
	Return :		COLORREF	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_color".

   ============================================================*/
{

	return m_color;

}

void CBorderLine::SetColor( COLORREF value )
/* ============================================================
	Function :		CBorderLine::SetColor
	Description :	Accessor. Setter for "m_color".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	Value of the attribute

	Usage :			Call to set the value of "m_color".

   ============================================================*/
{

	m_color = value;

}

double CBorderLine::GetThickness() const
/* ============================================================
	Function :		CBorderLine::GetThickness
	Description :	Accessor. Getter for "m_thickness".
	Access :		Public
					
	Return :		double	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_thickness".

   ============================================================*/
{

	return m_thickness;

}

void CBorderLine::SetThickness( double value )
/* ============================================================
	Function :		CBorderLine::SetThickness
	Description :	Accessor. Setter for "m_thickness".
	Access :		Public
					
	Return :		void
	Parameters :	double value	-	Value of the attribute. 

	Usage :			Call to set the value of "m_thickness".

   ============================================================*/
{

	m_thickness = value;

}

