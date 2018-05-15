/* ==========================================================================
	File :			DrawField.cpp
	
	Class :			CDrawField

	Date :			07/27/04

	Purpose :		"CDrawField" represents a simple drawable field.

	Description :	The class contain attributes for the objects, as well 
					as members to load and draw.

	Usage :			Should be managed by a container class. Data for the 
					field should be set by calling "AddData".
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "DrawField.h"
#include "BorderLine.h"
#include "Tokenizer.h"
#include "StringHelpers.h"
#include "UnitConversion.h"

CDrawField::CDrawField()
/* ============================================================
	Function :		CDrawField::CDrawField
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetFieldType( FIELD_TYPE_FIELD );

}

////////////////////////////////////////////////////////////////////
// Public functions
//
void CDrawField::Draw( int page, CDC* dc )
/* ============================================================
	Function :		CDrawField::Draw
	Description :	Draws this object.
	Access :		Public
					
	Return :		void
	Parameters :	int page	-	Current page
					CDC* dc		-	CDC to draw to

	Usage :			Called by the generator to draw the object.

   ============================================================*/
{

	CString title = GetTitle();
	CDoubleRect rect = GetPosition();
	CUnitConversion::InchesToPixels( rect );

	CRect r( static_cast< int >( rect.left ), static_cast< int >( rect.top ), static_cast< int >( rect.right ), static_cast< int >( rect.bottom ) );
	CUnitConversion::AdjustPixelsToPaper( dc, r );

	LOGFONT	lf;
	ZeroMemory( &lf, sizeof( lf ) );

	lstrcpy( lf.lfFaceName, GetFontName() );
	lf.lfHeight = CUnitConversion::PointsToPixels( static_cast< double >( GetFontSize() ) / 10.0 );
	lf.lfItalic = static_cast< BYTE >( GetFontItalic() );
	lf.lfUnderline = static_cast< BYTE >( GetFontUnderline() );
	lf.lfStrikeOut = static_cast< BYTE >( GetFontStrikeout() );
	lf.lfCharSet = static_cast< BYTE >( GetFontCharset() );

	if( GetFontBold() )
		lf.lfWeight = FW_BOLD;
	else
		lf.lfWeight = FW_NORMAL;

	if( IsBold( title ) )
		lf.lfWeight = FW_BOLD;

	if( IsItalic( title ) )
		lf.lfItalic = TRUE;

	CFont	font;
	font.CreateFontIndirect( &lf );

	dc->SelectObject( &font );
	int color = dc->SetTextColor( GetFontColor() );
	int mode = dc->SetBkMode( TRANSPARENT );
	int justification = GetJustification();

	ReplaceFields( page, title );

	dc->DrawText( title, r, DT_NOPREFIX | DT_WORDBREAK | justification );

	dc->SetBkMode( mode );
	dc->SetTextColor( color );
	dc->SelectStockObject( ANSI_VAR_FONT );

}

CDrawObject* CDrawField::FromString( const CString & str )
/* ============================================================
	Function :		CDrawField::FromString
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

	CDrawField*	result = NULL;
	CTokenizer tok( str, _T( ":" ) );
	int size = tok.GetSize();
	if( size == 2 )
	{
		CString type;
		CString data;
		tok.GetAt( 0, type );
		if( type == _T( "report_field" ) )
		{
			tok.GetAt( 1, data );
			result = new CDrawField;
			int count = CDrawObject::FromStringCommon( result, data );

			CString		fontname;
			int			fontsize;
			BOOL		fontbold;
			BOOL		fontitalic;
			BOOL		fontunderline;
			BOOL		fontstrikeout;
			COLORREF	fontcolor;
			int			justification;
			int			charset;

			tok.Init( data );

			tok.GetAt( count++, fontname );
			tok.GetAt( count++, fontsize );
			tok.GetAt( count++, fontbold );
			tok.GetAt( count++, fontitalic );
			tok.GetAt( count++, fontunderline );
			tok.GetAt( count++, fontstrikeout );
			tok.GetAt( count++, fontcolor );
			tok.GetAt( count++, justification );
			tok.GetAt( count++, charset );

			result->SetFontName( fontname );
			result->SetFontSize( fontsize );
			result->SetFontBold( fontbold );
			result->SetFontItalic( fontitalic );
			result->SetFontUnderline( fontunderline );
			result->SetFontStrikeout( fontstrikeout );
			result->SetFontColor( fontcolor );
			result->SetJustification( justification );
			result->SetFontCharset( charset );

		}
	}

	return result;

}

void CDrawField::ReplaceFields( int page, CString & str ) const
/* ============================================================
	Function :		CDrawField::ReplaceFields
	Description :	Replaces the replaceable fields in "str".
	Access :		Private

	Return :		void
	Parameters :	int page		-	Current page
					CString & str	-	String to replace data in
					
	Usage :			Replaces fixed fields with the current data, 
					currently "[%page%]", "[%date%]" and "[%time%]".

   ============================================================*/
{

	CString pg;
	CString dt;
	CString tm;
	CTime time = CTime::GetCurrentTime();
	dt = time.Format( _T( "%x" ) );
	tm = time.Format( _T( "%X" ) );

	pg.Format( _T( "%d" ), page );

	str.Replace( _T( "[%page%]" ), pg );
	str.Replace( _T( "[%date%]" ), dt );
	str.Replace( _T( "[%time%]" ), tm );

}

void CDrawField::Clear()
/* ============================================================
	Function :		CDrawField::Clear
	Description :	Clears the data of the object.
	Access :		

	Return :		void
	Parameters :	none

	Usage :			Call to clear the object before setting 
					new data.

   ============================================================*/
{

	AddData( _T( "" ) );

}

BOOL CDrawField::IsBold( CString& text ) const
/* ============================================================
	Function :		CDrawField::IsBold
	Description :	Returns "TRUE" if "text" contains a bold 
					marker.
	Access :		Private

	Return :		BOOL			-	"TRUE" if "text" contains 
										the marker.
	Parameters :	CString& text	-	The text to check.

	Usage :			If "text" contains the string "[%bold%]", 
					the field will be set to bold. The marker 
					will be removed.

   ============================================================*/
{

	return ( BOOL ) ReplaceTag( text, _T( "[%bold%]" ) );
	
}

BOOL CDrawField::IsItalic( CString& text ) const
/* ============================================================
	Function :		CDrawField::IsItalic
	Description :	Returns "TRUE" if "text" contains an italic
					marker.
	Access :		Private

	Return :		BOOL			-	"TRUE" if "text" contains 
										the marker.
	Parameters :	CString& text	-	The text to check.

	Usage :			If "text" contains the string "[%italic%]", 
					the field will be set to italic. The marker 
					will be removed.

   ============================================================*/
{

	return ( BOOL ) ReplaceTag( text, _T( "[%italic%]" ) );

}

