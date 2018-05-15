/* ==========================================================================
	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-06-21

	Purpose :		Misc string-related functions

	Description :	Contains several string-related function.

	Usage :			Call as needed.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/
#include "stdafx.h"
#include "StringHelpers.h"
#include "Tokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void MakeSaveString( CString& str )
{

	// This function replaces some non-alphanumeric 
	// character with tag-codes, as the characters 
	// are used for delimiting different kind of 
	// substrings.

	str.Replace( _T( ":" ), _T( "\\colon" ) );
	str.Replace( _T( ";" ), _T( "\\semicolon" ) );
	str.Replace( _T( "," ), _T( "\\comma" ) );
	str.Replace( _T( "|" ), _T( "\\bar" ) );
	str.Replace( _T( "#" ), _T( "\\hash" ) );
	str.Replace( _T( "\r\n" ), _T( "\\newline" ) );

}

void UnmakeSaveString( CString& str )
{

	// The function replaces some tag-strings 
	// with the corresponding characters after 
	// loading the string from file.

	str.Replace( _T( "\\colon" ), _T( ":" ) );
	str.Replace( _T( "\\semicolon" ) , _T( ";" ) );
	str.Replace( _T( "\\comma" ), _T( "," ) );
	str.Replace( _T( "\\bar" ), _T( "|" ) );
	str.Replace( _T( "\\hash" ), _T( "#" ) );
	str.Replace( _T( "\\newline" ), _T( "\r\n" ) );

}

HANDLE DDBToDIB( HBITMAP bitmap )
/*
	Utility function to convert device 
	dependent bitmaps to device independent ones.
	*/
{

	BITMAP				bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER	lpbi;
	DWORD				length;
	HANDLE				dib = NULL;
	HANDLE				handle;
	HDC					dc;
	HPALETTE			palette = ( HPALETTE ) ::GetStockObject( DEFAULT_PALETTE );
	BOOL				success = FALSE;
	int					colors = 0;

	// Get bitmap information
	::GetObject( bitmap, sizeof( bm ),( LPSTR ) &bm );

	// Initialize the bitmapinfoheader
	memset( &bi, 0, sizeof( BITMAPINFOHEADER ) );

	bi.biSize			= sizeof( BITMAPINFOHEADER );
	bi.biWidth			= bm.bmWidth;
	bi.biHeight			= bm.bmHeight;
	bi.biPlanes			= 1;
	bi.biBitCount		= ( unsigned short )( bm.bmPlanes * bm.bmBitsPixel ) ;
	bi.biCompression	= BI_RGB;

    // Compute the size of the  infoheader and the color table
	if(bi.biBitCount <= 8)
		colors = (1 << bi.biBitCount);

	length = bi.biSize + colors * sizeof( RGBQUAD );

	dc = ::GetDC(NULL);
	palette = SelectPalette( dc, palette, FALSE );
	RealizePalette( dc );

	dib = GlobalAlloc( GMEM_FIXED, length );
	if( dib )
	{
		lpbi = ( LPBITMAPINFOHEADER ) GlobalLock( dib );

		*lpbi = bi;

		GetDIBits( dc, bitmap, 0, ( DWORD ) bi.biHeight, ( LPBYTE ) NULL, ( LPBITMAPINFO ) lpbi, ( DWORD ) DIB_RGB_COLORS );
		bi = *lpbi;

		if (bi.biSizeImage == 0)
			bi.biSizeImage = ( ( ( ( bi.biWidth * bi.biBitCount ) + 31 ) & ~31 ) / 8 ) * bi.biHeight;
		length += bi.biSizeImage;

		handle = GlobalReAlloc( dib, length, GMEM_MOVEABLE );
		if( handle != NULL )
		{
			dib = handle;

			// Get the bitmap bits
			lpbi = (LPBITMAPINFOHEADER) dib;

			// FINALLY get the DIB
			success = GetDIBits( dc, bitmap,
								0,
								( DWORD ) bi.biHeight,
								( LPBYTE ) lpbi + ( bi.biSize + colors * sizeof( RGBQUAD ) ),
								( LPBITMAPINFO ) lpbi,
								( DWORD ) DIB_RGB_COLORS );
		}

		if( !success )
		{
			GlobalFree( dib );
			dib = NULL;
		}
	}

	SelectPalette( dc, palette, FALSE );
    ::ReleaseDC( NULL, dc );

    return dib;

}

int ReplaceTag( CString& text, const CString& tag )
{

	// Removes "tag" from "text", returning
	// the number of removals

	return text.Replace( tag, _T( "" ) );

}

void Tokenize( const CString& data, CStringArray& arr )
{

	// Chops "data" into a "CStringArray" at 
	// new lines (either \r\n or just \n)

	CString block( data );
	block.Replace( _T( "\r" ), _T( "" ) );

	CTokenizer tok( block, _T( "\n" ) );
	int max = tok.GetSize();
	for( int t = 0 ; t < max ; t++ )
	{
		CString value;
		tok.GetAt( t, value );
		if( value.GetLength() )
			arr.Add( value );
	}

}
