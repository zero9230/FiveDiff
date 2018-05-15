/* ==========================================================================
	File :			DrawLine.cpp
	
	Class :			CDrawLine

	Date :			07/27/04

	Purpose :		"CDrawLine" represents a simple drawable line.

	Description :	The class contain attributes for the objects, as well 
					as members to load and draw.

	Usage :			Should be managed by a container class.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "DrawLine.h"
#include "BorderLine.h"
#include "UnitConversion.h"
#include "Tokenizer.h"
#include "StringHelpers.h"

CDrawLine::CDrawLine()
/* ============================================================
	Function :		CDrawLine::CDrawLine
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetFieldType( FIELD_TYPE_LINE );

}

////////////////////////////////////////////////////////////////////
// Public functions
//
void CDrawLine::Draw( int /*page*/, CDC* dc )
/* ============================================================
	Function :		CDrawLine::Draw
	Description :	Draws this object.
	Access :		Public
					
	Return :		void
	Parameters :	int page	-	Current page (not used)
					CDC* dc		-	CDC to draw to

	Usage :			Called by the generator to draw the object.

   ============================================================*/
{

	const CBorderLine* line = GetBorder();
	int thickness = CUnitConversion::InchesToPixels( line->GetThickness() );
	CPen pen;
	pen.CreatePen( line->GetStyle(),
				   thickness,
				   line->GetColor() );

	dc->SelectObject( &pen );

	CDoubleRect rect = GetPosition();
	CUnitConversion::InchesToPixels( rect );
	CRect r( static_cast< int >( rect.left ), static_cast< int >( rect.top ), static_cast< int >( rect.right ), static_cast< int >( rect.bottom ) );
	CUnitConversion::AdjustPixelsToPaper( dc, r );

	dc->MoveTo( r.TopLeft() );
	dc->LineTo( r.BottomRight() );

	dc->SelectStockObject( BLACK_PEN );

}

CDrawObject* CDrawLine::FromString( const CString & str )
/* ============================================================
	Function :		CDrawLine::FromString
	Description :	Creates and returns an object of this type 
					from the string "str".
	Access :		Public
					
	Return :		CDrawObject*		-	Object represented by 
											"str" or "NULL" is "str" 
											is not of this type.
	Parameters :	const CString & str	-	String representation 
											of an object of this 
											type.
	
	Usage :			Called by the generator loading mechanism.

   ============================================================*/
{

	CDrawLine*	result = NULL;
	CTokenizer tok( str, _T( ":" ) );
	int size = tok.GetSize();
	if( size == 2 )
	{
		CString type;
		CString data;
		tok.GetAt( 0, type );
		if( type == _T( "report_line" ) )
		{
			tok.GetAt( 1, data );
			CTokenizer contents( data, _T( "," ) );
			result = new CDrawLine;
			int count = CDrawObject::FromStringCommon( result, data );

			double		borderthickness;
			int			borderstyle;
			COLORREF	bordercolor;

			contents.GetAt( count++, borderthickness );
			contents.GetAt( count++, borderstyle );
			contents.GetAt( count++, bordercolor );

			CBorderLine line;
			line.SetColor( bordercolor );
			line.SetThickness( borderthickness );
			line.SetStyle( borderstyle );
			result->SetBorder( line );

		}
	}

	return result;

}

