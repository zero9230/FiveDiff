/* ==========================================================================
	File :			Column.cpp
	
	Class :			CColumn

	Date :			02/20/05

	Purpose :		"CColumn" represents a single column in a grid.

	Description :	The class is a simple data container.

	Usage :			Instances are created and added in "CDrawGrid".
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "Column.h"
#include "UnitConversion.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CColumn::CColumn() : width( 0.0 ),
fontSize( 0 ),
fontItalic( FALSE ),
fontUnderline( FALSE ),
fontBold( FALSE ),
fontStrikeout( FALSE ),
fontColor( RGB( 0, 0, 0 ) ),
justification( 0 ),
charset( 0 )
/* ============================================================
	Function :		CColumn::CColumn
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

}

CColumn::~CColumn()
/* ============================================================
	Function :		CColumn::~CColumn
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

}

double CColumn::GetWidth() const
/* ============================================================
	Function :		CColumn::GetWidth
	Description :	Accessor. Getter for "width".
	Access :		Public
					
	Return :		double	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "width".

   ============================================================*/
{

	return width;

}

void CColumn::SetWidth( double value )
/* ============================================================
	Function :		CColumn::SetWidth
	Description :	Accessor. Setter for "width".
	Access :		Public
					
	Return :		void
	Parameters :	double value	-	Value of the attribute
	Usage :			Call to set the value of "width".

   ============================================================*/
{

	width = value;

}

CString CColumn::GetFont() const
/* ============================================================
	Function :		CColumn::GetFont
	Description :	Accessor. Getter for "font".
	Access :		Public
					
	Return :		CString	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "font".

   ============================================================*/
{

	return font;

}

void CColumn::SetFont( CString value )
/* ============================================================
	Function :		CColumn::SetFont
	Description :	Accessor. Setter for "font".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	Value of the attribute
	Usage :			Call to set the value of "font".

   ============================================================*/
{

	font = value;

}

int CColumn::GetFontSize() const
/* ============================================================
	Function :		CColumn::GetFontSize
	Description :	Accessor. Getter for "fontSize".
	Access :		Public
					
	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "fontSize".

   ============================================================*/
{

	return fontSize;

}

void CColumn::SetFontSize( int value )
/* ============================================================
	Function :		CColumn::SetFontSize
	Description :	Accessor. Setter for "fontSize".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	Value of the attribute
	Usage :			Call to set the value of "fontSize".

   ============================================================*/
{

	fontSize = value;

}

int CColumn::GetFontCharset() const
/* ============================================================
	Function :		CColumn::GetFontCharset
	Description :	Accessor. Getter for "charset".
	Access :		Public
					
	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "charset".

   ============================================================*/
{

	return charset;

}

void CColumn::SetFontCharset( int value )
/* ============================================================
	Function :		CColumn::SetFontCharset
	Description :	Accessor. Setter for "charset".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	Value of the attribute
	Usage :			Call to set the value of "charset".

   ============================================================*/
{

	charset = value;

}

BOOL CColumn::GetFontItalic() const
/* ============================================================
	Function :		CColumn::GetFontItalic
	Description :	Accessor. Getter for "fontItalic".
	Access :		Public
					
	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "fontItalic".

   ============================================================*/
{

	return fontItalic;

}

void CColumn::SetFontItalic( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontItalic
	Description :	Accessor. Setter for "fontItalic".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
	Usage :			Call to set the value of "fontItalic".

   ============================================================*/
{

	fontItalic = value;

}

BOOL CColumn::GetFontUnderline() const
/* ============================================================
	Function :		CColumn::GetFontUnderline
	Description :	Accessor. Getter for "fontUnderline".
	Access :		Public
					
	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "fontUnderline".

   ============================================================*/
{

	return fontUnderline;

}

void CColumn::SetFontUnderline( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontUnderline
	Description :	Accessor. Setter for "fontUnderline".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
	Usage :			Call to set the value of "fontUnderline".

   ============================================================*/
{

	fontUnderline = value;

}

BOOL CColumn::GetFontBold() const
/* ============================================================
	Function :		CColumn::GetFontBold
	Description :	Accessor. Getter for "fontBold".
	Access :		Public
					
	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "fontBold".

   ============================================================*/
{

	return fontBold;

}

void CColumn::SetFontBold( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontBold
	Description :	Accessor. Setter for "fontBold".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
	Usage :			Call to set the value of "fontBold".

   ============================================================*/
{

	fontBold = value;

}

BOOL CColumn::GetFontStrikeout() const
/* ============================================================
	Function :		CColumn::GetFontStrikeout
	Description :	Accessor. Getter for "fontStrikeout".
	Access :		Public
					
	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "fontStrikeout".

   ============================================================*/
{

	return fontStrikeout;

}

void CColumn::SetFontStrikeout( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontStrikeout
	Description :	Accessor. Setter for "fontStrikeout".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
	Usage :			Call to set the value of "fontStrikeout".

   ============================================================*/
{

	fontStrikeout = value;

}

COLORREF CColumn::GetFontColor() const
/* ============================================================
	Function :		CColumn::GetFontColor
	Description :	Accessor. Getter for "fontColor".
	Access :		Public
					
	Return :		COLORREF	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "fontColor".

   ============================================================*/
{

	return fontColor;

}

void CColumn::SetFontColor( COLORREF value )
/* ============================================================
	Function :		CColumn::SetFontColor
	Description :	Accessor. Setter for "fontColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	Value of the attribute
	Usage :			Call to set the value of "fontColor".

   ============================================================*/
{

	fontColor = value;

}

int CColumn::GetJustification() const
/* ============================================================
	Function :		CColumn::GetJustification
	Description :	Accessor. Getter for "justification".
	Access :		Public
					
	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "justification".

   ============================================================*/
{

	return justification;

}

void CColumn::SetJustification( int value )
/* ============================================================
	Function :		CColumn::SetJustification
	Description :	Accessor. Setter for "justification".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	Value of the attribute
	Usage :			Call to set the value of "justification".

   ============================================================*/
{

	justification = value;

}

CString CColumn::GetName() const
/* ============================================================
	Function :		CColumn::GetName
	Description :	Accessor. Getter for "name".
	Access :		Public
					
	Return :		CString	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "name".

   ============================================================*/
{

	return name;

}

void CColumn::SetName( CString value )
/* ============================================================
	Function :		CColumn::SetName
	Description :	Accessor. Setter for "name".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	Value of the attribute
	Usage :			Call to set the value of "name".

   ============================================================*/
{

	name = value;

}

CFont* CColumn::GetColumnFont() const
/* ============================================================
	Function :		CColumn::GetColumnFont
	Description :	Returns a "CFont" pointer to the font of 
					the column
	Access :		Public

	Return :		CFont*	-	The column font
	Parameters :	none

	Usage :			Call to get a "CFont" pointer to the column 
					font. Memory must be deleted by the caller.

   ============================================================*/
{

	LOGFONT	lf;
	ZeroMemory( &lf, sizeof( lf ) );

	lstrcpy( lf.lfFaceName, GetFont() );
	lf.lfHeight = CUnitConversion::PointsToPixels( static_cast< double >( GetFontSize() ) / 10.0 );
	lf.lfItalic = static_cast< BYTE >( GetFontItalic() );
	lf.lfUnderline = static_cast< BYTE >( GetFontUnderline() );
	lf.lfStrikeOut = static_cast< BYTE >( GetFontStrikeout() );
	lf.lfCharSet = static_cast< BYTE >( GetFontCharset() );
	if( GetFontBold() )
		lf.lfWeight = FW_BOLD;
	else
		lf.lfWeight = FW_NORMAL;

	CFont*	font = new CFont;
	if( font )
		font->CreateFontIndirect( &lf );

	return font;

}

