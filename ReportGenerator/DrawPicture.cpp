/* ==========================================================================
	File :			DrawPicture.cpp
	
	Class :			CDrawPicture

	Date :			07/27/04

	Purpose :		"CDrawPicture" represents a simple drawable picture.

	Description :	The class contain attributes for the objects, as well 
					as members to load and draw.

	Usage :			Should be managed by a container class.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "DrawPicture.h"
#include "Tokenizer.h"
#include "StringHelpers.h"
#include "UnitConversion.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CDrawPicture::CDrawPicture()
/* ============================================================
	Function :		CDrawPicture::CDrawPicture
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetFieldType( FIELD_TYPE_PICTURE );
	m_bitmap = NULL;

}

CDrawPicture::~CDrawPicture()
/* ============================================================
	Function :		CDrawPicture::~CDrawPicture
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	if( m_bitmap )
	{
		GlobalUnlock( m_bitmap );
		GlobalFree( m_bitmap );
	}

}

CString CDrawPicture::GetFilename() const
/* ============================================================
	Function :		CDrawPicture::GetFilename
	Description :	Accessor. Getter for "m_filename".
	Access :		Public
					
	Return :		CString	-	Name of the file
	Parameters :	none

	Usage :			Call to get the value of "m_filename".
					"m_filename" is the name of the bitmap 
					file to draw from.

   ============================================================*/
{

	return m_filename;

}

void CDrawPicture::SetFilename( CString value )
/* ============================================================
	Function :		CDrawPicture::SetFilename
	Description :	Accessor. Setter for "m_filename".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	Name of the file

	Usage :			Call to set the value of "m_filename".
					"m_filename" is the name of the bitmap 
					file to draw from.

   ============================================================*/
{

	m_filename = value;

	if( m_bitmap )
	{
		GlobalUnlock( m_bitmap );
		GlobalFree( m_bitmap );
	}

	m_bitmap = NULL;
	HBITMAP bmp;
	if( m_filename.GetLength() )
	{
		bmp = ( HBITMAP ) ::LoadImage( NULL, m_filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION );
		if( bmp )
			m_bitmap = DDBToDIB( bmp );
	}

}

void CDrawPicture::Draw( int /*page*/, CDC* dc )
/* ============================================================
	Function :		CDrawPicture::Draw
	Description :	Draws this object.
	Access :		Public
					
	Return :		void
	Parameters :	int page	-	Current page (not used)
					CDC* dc		-	CDC to draw to

	Usage :			Called by the generator to draw the object.

   ============================================================*/
{

	CPen pen;
	CDoubleRect rect = GetPosition();
	CUnitConversion::InchesToPixels( rect );

	CRect r( static_cast< int >( rect.left ), static_cast< int >( rect.top ), static_cast< int >( rect.right ), static_cast< int >( rect.bottom ) );
	CUnitConversion::AdjustPixelsToPaper( dc, r );

	const CBorderLine* line = GetBorder();

	if( line->GetVisible() )
	{
		int thickness = CUnitConversion::InchesToPixels( line->GetThickness() );
		pen.CreatePen( line->GetStyle(),
					   thickness,
					   line->GetColor() );

		dc->SelectObject( &pen );
		dc->Rectangle( r );
	}
	else
		dc->SelectStockObject( NULL_PEN );

	if( m_bitmap )
	{
		r.InflateRect( -1, -1 );

		BITMAPINFOHEADER* bmi = ( BITMAPINFOHEADER* ) GlobalLock( m_bitmap );
		int colors = 0;
		if( bmi->biBitCount <= 8 )
			colors = ( 1 << bmi->biBitCount );

		::StretchDIBits( dc->m_hDC,
						r.left, 
						r.top, 
						r.Width(), 
						r.Height(),
						0, 
						0, 
						bmi->biWidth,
						bmi->biHeight,
						( LPBYTE ) bmi + ( bmi->biSize + colors * sizeof( RGBQUAD ) ),
						( BITMAPINFO* ) bmi,
						DIB_RGB_COLORS, 
						SRCCOPY );

	}

	dc->SelectStockObject( BLACK_PEN );
	dc->SelectStockObject( WHITE_BRUSH );
	
}

CDrawObject* CDrawPicture::FromString( const CString & str )
/* ============================================================
	Function :		CDrawPicture::FromString
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

	CDrawPicture*	result = NULL;
	CTokenizer tok( str, _T( ":" ) );
	int size = tok.GetSize();
	if( size == 2 )
	{
		CString type;
		CString data;
		tok.GetAt( 0, type );
		if( type == _T( "report_picture" ) )
		{
			tok.GetAt( 1, data );

			while( data[ data.GetLength() - 1 ] == _TCHAR( ';' ) )
				data = data.Left( data.GetLength() - 1 );

			CTokenizer contents( data, _T( "," ) );

			double		left;
			double		top;
			double		right;
			double		bottom;
			CString		title;
			CString		name;
			int			group;

			BOOL		b;
			double		borderthickness;
			int			borderstyle;
			COLORREF	bordercolor;
			
			int count = 0;

			contents.GetAt( count++, left );
			contents.GetAt( count++, top );
			contents.GetAt( count++, right );
			contents.GetAt( count++, bottom );
			contents.GetAt( count++, title );
			contents.GetAt( count++, name );
			contents.GetAt( count++, group );

			contents.GetAt( count++, b );
			contents.GetAt( count++, borderthickness );
			contents.GetAt( count++, borderstyle );
			contents.GetAt( count++, bordercolor );

			result = new CDrawPicture;

			if( b )
			{
				CBorderLine border;
				border.SetVisible( b );
				border.SetStyle( borderstyle );
				border.SetColor( bordercolor );
				border.SetThickness( borderthickness );

				result->SetBorder( border );
			}

			result->SetPosition( CDoubleRect( left, top, right, bottom ) );
			result->SetName( name );
			result->SetFilename( title );

		}
	}

	return result;

}

void CDrawPicture::SetHDIB( HANDLE hdib )
/* ============================================================
	Function :		CDrawPicture::SetHDIB
	Description :	Accessor for "m_bitmap".
	Access :		Public
					
	Return :		void
	Parameters :	HANDLE hdib	-	A handle to the picture to set.

	Usage :			Call to set the value of "m_bitmap". "hdib" 
					is assumed to be the handle to a hdib.

   ============================================================*/
{

	if( m_bitmap )
	{
		GlobalUnlock( m_bitmap );
		GlobalFree( m_bitmap );
	}

	m_bitmap = hdib;

}

void CDrawPicture::SetHBITMAP( HBITMAP hbmp )
/* ============================================================
	Function :		CDrawPicture::SetHBITMAP
	Description :	Accessor for "m_bitmap".
	Access :		Public
					
	Return :		void
	Parameters :	HBITMAP hbmp	-	A handle to the picture 
										to set.

	Usage :			Call to set the value of "m_bitmap". 

   ============================================================*/
{

	if( m_bitmap )
	{
		GlobalUnlock( m_bitmap );
		GlobalFree( m_bitmap );
	}

	if( hbmp )
		m_bitmap = DDBToDIB( hbmp );

}
