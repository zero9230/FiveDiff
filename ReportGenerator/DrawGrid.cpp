/* ==========================================================================
	File :			DrawGrid.cpp
	
	Class :			CDrawGrid

	Date :			07/27/04

	Purpose :		"CDrawGrid" represents a simple drawable grid.

	Description :	The class contain attributes for the objects, as well 
					as members to load and draw.

	Usage :			Should be managed by a container class. Data should be 
					added by calling "AddData" with a "CStringArray" with 
					the data, one string for each row, the data for each 
					column delimited with '|'. "AddIndex" should be added 
					for each page, where the index is the starting line in 
					the data array.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "DrawGrid.h"
#include "BorderLine.h"
#include "Tokenizer.h"
#include "StringHelpers.h"
#include "UnitConversion.h"

CDrawGrid::CDrawGrid()
/* ============================================================
	Function :		CDrawGrid::CDrawGrid
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetFieldType( FIELD_TYPE_GRID );
	SetPageOffset( 0 );

}

////////////////////////////////////////////////////////////////////
// Public functions
//
void CDrawGrid::Draw( int page, CDC* dc )
/* ============================================================
	Function :		CDrawGrid::Draw
	Description :	Draws this object.
	Access :		Public
					
	Return :		void
	Parameters :	int page	-	Current page
					CDC* dc		-	CDC to draw to

	Usage :			Called by the generator to draw the object.

   ============================================================*/
{

	/////////////////////////////////
	// Get and convert grid position
	//

	int drawpage = page - GetPageOffset();
	CDoubleRect rect = GetPosition();
	CUnitConversion::InchesToPixels( rect );

	CRect r( static_cast< int >( rect.left ), static_cast< int >( rect.top ), static_cast< int >( rect.right ), static_cast< int >( rect.bottom ) );
	CUnitConversion::AdjustPixelsToPaper( dc, r );

	/////////////////////////////////
	// Create column widths and 
	// fonts 
	//

	int restWidth = 0;
	int sumWidth = 0;
	TContainer< CFont* > fonts;

	double lpi = static_cast< double >( GetLPI() );
	double inch = static_cast< double >( dc->GetDeviceCaps( LOGPIXELSY ) );
	int lineHeight = static_cast< int >( inch / lpi + .5 );

	int max = m_columns.GetSize();
	for( int t = 0 ; t < max ; t++ )
	{

		CColumn* column = m_columns.GetAt( t );
		if( column )
		{
			sumWidth += CUnitConversion::InchesToPixels( column->GetWidth() );
			fonts.Add( column->GetColumnFont() );
		}

	}

	// restWidth will be used for 
	// any 0-length field
	restWidth = r.Width() - sumWidth;

	/////////////////////////////////
	// Find start and end of data
	// 

	int start = m_pages.GetAt( drawpage )->m_startLine;
	int end = m_pages.GetAt( drawpage )->m_endLine;

	int mode = dc->SetBkMode( TRANSPARENT );
	COLORREF color = dc->GetTextColor();

	/////////////////////////////////
	// Border
	//

	const CBorderLine* borderline = GetBorder();
	CPen pen;
	CPen boldPen;

	if( borderline->GetVisible() )
	{
		// Draw a border around the grid
		int thickness = CUnitConversion::InchesToPixels( borderline->GetThickness() );
		pen.CreatePen( borderline->GetStyle(),
					   thickness,
					   borderline->GetColor() );

		dc->SelectObject( &pen );
		dc->SelectStockObject( NULL_BRUSH );
		dc->Rectangle( r );
		dc->SelectStockObject( NULL_PEN );
	}


	/////////////////////////////////
	// Line pens
	//

	const CBorderLine* columnline = GetColumnLine();
	const CBorderLine* rowline = GetRowLine();
	CPen* columnpen = NULL;
	CPen* rowpen = NULL;
	if( columnline->GetVisible() )
	{
		columnpen = new CPen;
		int thickness = CUnitConversion::InchesToPixels( columnline->GetThickness() );
		columnpen->CreatePen( columnline->GetStyle(),
					   thickness,
					   columnline->GetColor() );
	}

	if( rowline->GetVisible() )
	{
		rowpen = new CPen;
		int thickness = CUnitConversion::InchesToPixels( rowline->GetThickness() );
		rowpen->CreatePen( rowline->GetStyle(),
					   thickness,
					   rowline->GetColor() );
	}


	/////////////////////////////////
	// Column lines
	//

	if( columnpen )
	{

		dc->SelectObject( columnpen );
		int left = r.left;

		// Loop columns
		for( int i = 0 ; i < max - 1; i++ )
		{

			CColumn* column = m_columns.GetAt( i );
			if( column )
			{

				int pixelWidth = CUnitConversion::InchesToPixels( column->GetWidth() );
				if( pixelWidth == 0 )
					pixelWidth = restWidth;

				left += pixelWidth;

				dc->MoveTo( left, r.top );
				dc->LineTo( left, r.bottom );

			}

		}

		dc->SelectStockObject( NULL_PEN );

	}

	/////////////////////////////////
	// Loop and print column strings
	//

	int top = r.top;
	for( int t = start ; t < end ; t++ )
	{
		// Tokenize a line of data
		CString line( m_data[ t ] );
		int quarterHeight = lineHeight / 4;

		// Check if this is a separator 
		if( IsSeparator( line ) )
		{
			// Draw a line across the grid
			dc->SelectStockObject( BLACK_PEN );
			dc->MoveTo( r.left, top + quarterHeight );
			dc->LineTo( r.right, top + quarterHeight );
		}
		else if( IsDoubleSeparator( line ) )
		{
			// Draw a double line across the grid
			dc->SelectStockObject( BLACK_PEN );
			dc->MoveTo( r.left, top + quarterHeight );
			dc->LineTo( r.right, top + quarterHeight );
			dc->MoveTo( r.left, top + quarterHeight * 2 );
			dc->LineTo( r.right, top + quarterHeight * 2 );
		}
		else if( IsBoldSeparator( line ) )
		{
			// Draw a bold line across the grid
			boldPen.CreatePen( PS_SOLID, quarterHeight / 2, RGB( 0, 0, 0 ) );
			dc->SelectObject( boldPen );
			dc->MoveTo( r.left, top + quarterHeight );
			dc->LineTo( r.right, top + quarterHeight );
			dc->SelectStockObject( BLACK_PEN );
		}
		else
		{
			CTokenizer tok( line, _T( "|" ) );

			int left = r.left;
			// Loop columns
			for( int i = 0 ; i < max ; i++ )
			{
				CColumn* column = m_columns.GetAt( i );
				CRect drawRect( left, top, r.right, top + lineHeight );
				if( column )
				{
					// Get the data for this column
					CString data;
					tok.GetAt( i, data );

					// Get the width of the column
					int pixelWidth = CUnitConversion::InchesToPixels( column->GetWidth() );
					if( pixelWidth == 0 )
						pixelWidth = restWidth;

					// Set font
					CFont* font = fonts.GetAt( i );
					CFont* specialFont = NULL;

					if( font )
					{
						if( IsBold( data ) )
						{

							// Select a bold font 
							// here instead

							specialFont = new CFont;
							LOGFONT lf;

							font->GetLogFont( &lf );

							lf.lfWeight = FW_BOLD;
							specialFont->CreateFontIndirect( &lf );

						}

						if( IsItalic( data ))
						{

							// Select an italic font 
							// here instead

							specialFont = new CFont;
							LOGFONT lf;

							font->GetLogFont( &lf );

							lf.lfItalic = TRUE;
							specialFont->CreateFontIndirect( &lf );

						}
					}

					if( specialFont )
						dc->SelectObject( specialFont );
					else if( font )
						dc->SelectObject( font );

					// Create draw rect
					drawRect.SetRect( left, top, left + pixelWidth, top + lineHeight );

					// Add offsets for columns
					int offset = CUnitConversion::PointsToPixels( column->GetFontSize() / 40.0 );
					if( borderline->GetVisible() && i == 0 )
						offset += max( 1, CUnitConversion::InchesToPixels( borderline->GetThickness() ) );
					if( columnline->GetVisible() && i > 0 )
						offset += max( 1, CUnitConversion::InchesToPixels( columnline->GetThickness() ) );

					drawRect.left += offset;
					drawRect.right -= offset;

					// Draw data
					int justification = column->GetJustification();
					dc->DrawText( data, drawRect, DT_VCENTER | DT_NOPREFIX | DT_WORDBREAK | justification );

					if( specialFont )
						delete specialFont;

					// Increase x-coord
					left += pixelWidth;
				}


				/////////////////////////////////
				// Row dividers
				//

				if( rowpen && t < end )
				{

					dc->SelectObject( rowpen );
					dc->MoveTo( r.left, drawRect.bottom );
					dc->LineTo( r.right, drawRect.bottom );

				}

			}
		}

		// Increase y-coord
		top += lineHeight;

	}

	/////////////////////////////////
	// Restore everything
	//

	dc->SetBkMode( mode );
	dc->SetTextColor( color );
	dc->SelectStockObject( ANSI_VAR_FONT );
	dc->SelectStockObject( NULL_PEN );

	if( columnpen )
		delete columnpen;

	if( rowpen )
		delete rowpen;
	
}

CDrawObject* CDrawGrid::FromString( const CString & str )
/* ============================================================
	Function :		CDrawGrid::FromString
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
	CDrawGrid*	result = NULL;
	CTokenizer tok( str, _T( ":" ) );
	int size = tok.GetSize();
	if( size == 2 )
	{
		CString type;
		CString data;
		tok.GetAt( 0, type );
		if( type == _T( "report_grid" ) )
		{
			tok.GetAt( 1, data );
			CTokenizer contents( data, _T( "," ) );
			result = new CDrawGrid;

			int count = CDrawObject::FromStringCommon( result, data );
			BOOL		border;
			double		borderthickness;
			int			borderstyle;
			COLORREF	bordercolor;

			BOOL		columnlines;
			double		columnlinethickness;
			int			columnlinestyle;
			COLORREF	columnlinecolor;

			BOOL		rowlines;
			double		rowlinethickness;
			int			rowlinestyle;
			COLORREF	rowlinecolor;

			int			lpi;

			contents.GetAt( count++, border );
			contents.GetAt( count++, borderthickness );
			contents.GetAt( count++, borderstyle );
			contents.GetAt( count++, bordercolor );

			contents.GetAt( count++, columnlines );
			contents.GetAt( count++, columnlinethickness );
			contents.GetAt( count++, columnlinestyle );
			contents.GetAt( count++, columnlinecolor );

			contents.GetAt( count++, rowlines );
			contents.GetAt( count++, rowlinethickness );
			contents.GetAt( count++, rowlinestyle );
			contents.GetAt( count++, rowlinecolor );
			contents.GetAt( count++, lpi );

			result->SetLPI( lpi );

			if( border )
			{
				CBorderLine line;
				line.SetVisible( TRUE );
				line.SetColor( bordercolor );
				line.SetThickness( borderthickness );
				line.SetStyle( borderstyle );
				result->SetBorder( line );
			}

			if( columnlines )
			{
				CBorderLine line;
				line.SetVisible( TRUE );
				line.SetThickness( columnlinethickness );
				line.SetStyle( columnlinestyle );
				line.SetColor( columnlinecolor );
				result->SetColumnLine( line );
			}

			if( rowlines )
			{
				CBorderLine line;
				line.SetVisible( TRUE );
				line.SetThickness( rowlinethickness );
				line.SetStyle( rowlinestyle );
				line.SetColor( rowlinecolor );
				result->SetRowLine( line );
			}

			// Read columns
			CString columns;
			contents.GetAt( count, columns );
			contents.Init( columns, _T( "|" ) );
			int max = contents.GetSize();
			for( int t = 0 ; t < max ; t++ )
			{
				CString line;
				contents.GetAt( t, line );
				tok.Init( line, _T( "#" ) );
				size = tok.GetSize();
				count = 0;
				CColumn* column = new CColumn;

				double		width;
				CString		font;
				int			fontSize;
				BOOL		fontItalic;
				BOOL		fontUnderline;
				BOOL		fontBold;
				BOOL		fontStrikeout;
				COLORREF	fontColor;
				int			justification;
				CString		name;
				int			charset;

				tok.GetAt( count++, width );
				tok.GetAt( count++, font );
				tok.GetAt( count++, fontSize );
				tok.GetAt( count++, fontItalic );
				tok.GetAt( count++, fontUnderline );
				tok.GetAt( count++, fontBold );
				tok.GetAt( count++, fontStrikeout );
				tok.GetAt( count++, fontColor );
				tok.GetAt( count++, justification );
				tok.GetAt( count++, name );
				tok.GetAt( count++, charset );

				column->SetWidth( width );
				column->SetFont( font );
				column->SetFontSize( fontSize );
				column->SetFontItalic( fontItalic );
				column->SetFontBold( fontBold );
				column->SetFontStrikeout( fontStrikeout );
				column->SetFontColor( fontColor );
				column->SetJustification( justification );
				column->SetName( name );
				column->SetFontCharset( charset );

				result->AddColumn( column );

			}
		}
	}

	return result;

}

void CDrawGrid::AddData( const CStringArray& arr )
/* ============================================================
	Function :		CDrawGrid::AddData
	Description :	Adds data to this grid.
	Access :		Public

	Return :		void
	Parameters :	const CStringArray& arr	-	The data to add
					
	Usage :			Each row in the grid is represented by a 
					single "CString" in the array. Each column 
					in the string is separated with a '|'.

   ============================================================*/
{

	m_data.Append( arr );

};

void CDrawGrid::AddData( const CString& line )
/* ============================================================
	Function :		CDrawGrid::AddData
	Description :	Adds data to this grid.
	Access :		Public

	Return :		void
	Parameters :	const CString& line	-	The string to add
					
	Usage :			Each row in the grid is represented by a 
					single "CString" in the array. Each column 
					in the string is separated with a '|'.

   ============================================================*/
{

	m_data.Add( line );

};

void CDrawGrid::AddColumn( CColumn* column )
/* ============================================================
	Function :		CDrawGrid::AddColumn
	Description :	Adds a column to the grid.
	Access :		

	Return :		void
	Parameters :	CColumn* column	-	Column to add
					
	Usage :			Call to add columns to the grid.

   ============================================================*/
{
	m_columns.Add( column );
}

int CDrawGrid::GetLinesPerPage()
/* ============================================================
	Function :		CDrawGrid::GetLinesPerPage
	Description :	Gets the number of lines in the grid for a 
					single page.
	Access :		

	Return :		int		-	Number of lines
	Parameters :	none
					
	Usage :			Call to get the lines fitting to a single 
					page.

   ============================================================*/
{

	CDoubleRect rect = GetPosition();
	return static_cast< int >( rect.Height() * static_cast< double >( GetLPI() ) );

}

void CDrawGrid::Clear()
/* ============================================================
	Function :		CDrawGrid::Clear
	Description :	Clears the data of the object.
	Access :		

	Return :		void
	Parameters :	none

	Usage :			Call to clear the object before setting 
					new data.

   ============================================================*/
{

	m_data.RemoveAll();

}

void CDrawGrid::SetLPI( int value )
/* ============================================================
	Function :		CDrawGrid::SetLPI
	Description :	Sets the lines-per-inch to show in this 
					grid.
	Access :		Public

	Return :		void
	Parameters :	int value	-	LPI for the grid
					
	Usage :			Call to set the lines per inch toshow for 
					this grid.

   ============================================================*/
{

	m_lpi = value;

}

int CDrawGrid::GetLPI() const
/* ============================================================
	Function :		CDrawGrid::GetLPI
	Description :	Gets the lines-per-inch to show in this 
					grid.
	Access :		Public

	Return :		int		-	The LPI
	Parameters :	none

	Usage :			Call to get the lines per inch toshow for 
					this grid.

   ============================================================*/
{

	return m_lpi;

}

int CDrawGrid::GetColumns() const
/* ============================================================
	Function :		CDrawGrid::GetColumns
	Description :	Returns the number of columns in this grid.
	Access :		Public

	Return :		int	-	Number of columns
	Parameters :	none

	Usage :			Call to get the number of columns in this 
					grid.

   ============================================================*/
{

	return m_columns.GetSize();

}

BOOL CDrawGrid::IsBold( CString& text ) const
/* ============================================================
	Function :		CDrawGrid::IsBold
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

BOOL CDrawGrid::IsItalic( CString& text ) const
/* ============================================================
	Function :		CDrawGrid::IsItalic
	Description :	Returns "TRUE" if "text" contains an italic 
					marker.
	Access :		Private

	Return :		BOOL			-	"TRUE" if "text" contains 
										the marker.
	Parameters :	CString& text	-	The text to check.

	Usage :			If "text" contains the string "[%italic%]", 
					the field will be set to italic.The marker 
					will be removed.

   ============================================================*/
{
	return ( BOOL ) ReplaceTag( text, _T( "[%italic%]" ) );
}

BOOL CDrawGrid::IsBoldSeparator( CString& text ) const
/* ============================================================
	Function :		CDrawGrid::IsBoldSeparator
	Description :	Returns "TRUE" if "text" contains a bold 
					separator marker.
	Access :		Private

	Return :		BOOL			-	"TRUE" if "text" contains 
										the marker.
	Parameters :	CString& text	-	The text to check.

	Usage :			If "text" contains the string "[%bold-separator%]", 
					the row will just draw a bold line.The marker 
					will be removed.

   ============================================================*/
{
	return ( BOOL ) ReplaceTag( text, _T( "[%bold-separator%]" ) );
}

BOOL CDrawGrid::IsSeparator( CString& text ) const
/* ============================================================
	Function :		CDrawGrid::IsSeparator
	Description :	Returns "TRUE" if "text" contains a 
					separator marker.
	Access :		Private

	Return :		BOOL			-	"TRUE" if "text" contains 
										the marker.
	Parameters :	CString& text	-	The text to check.

	Usage :			If "text" contains the string "[%separator%]", 
					the row will just draw a line.The marker 
					will be removed.

   ============================================================*/
{
	return ( BOOL ) ReplaceTag( text, _T( "[%separator%]" ) );
}

BOOL CDrawGrid::IsDoubleSeparator( CString& text ) const
/* ============================================================
	Function :		CDrawGrid::IsDoubleSeparator
	Description :	Returns "TRUE" if "text" contains a double 
					separator marker.
	Access :		Private

	Return :		BOOL			-	"TRUE" if "text" contains 
										the marker.
	Parameters :	CString& text	-	The text to check.

	Usage :			If "text" contains the string "[%double-separator%]", 
					the row will just draw a double line.The marker 
					will be removed.

   ============================================================*/
{
	return ( BOOL ) ReplaceTag( text, _T( "[%double-separator%]" ) );
}

int CDrawGrid::GetPageOffset() const
/* ============================================================
	Function :		CDrawGrid::GetPageOffset
	Description :	Gets the page where this starts. 
	Access :		Public

	Return :		int	-	Start page
	Parameters :	none

	Usage :			The grid must know on what page it starts 
					to be able to furnish the correct data, as 
					the Draw function gets the true printing 
					page, and this grid might not be located on 
					a template starting on the first page.

   ============================================================*/
{

	return m_offset;
	
}

void CDrawGrid::SetPageOffset( int offset )
/* ============================================================
	Function :		CDrawGrid::SetPageOffset
	Description :	Sets the page on which this grid starts
	Access :		Public

	Return :		void
	Parameters :	int offset	-	Start page

	Usage :			The grid must know on what page it starts 
					to be able to furnish the correct data, as 
					the Draw function gets the true printing 
					page, and this grid might not be located on 
					a template starting on the first page.

   ============================================================*/
{

	m_offset = offset;

}

BOOL CDrawGrid::IsPagebreak( CString& text ) const
/* ============================================================
	Function :		CDrawGrid::IsPagebreak
	Description :	Returns "TRUE" if "text" contains a 
					pagebreak.
	Access :		Private

	Return :		BOOL			-	"TRUE" if "text" contains 
										a pagebreak.
	Parameters :	CString& text	-	The text to check.

	Usage :			If "text" contains the string "[%pagebreak%]", 
					the row will be used to create a pagebreak.
					The marker will be kept

   ============================================================*/
{
	return ( BOOL ) ( text == _T( "[%pagebreak%]" ) );
}

void CDrawGrid::CalcPages()
/* ============================================================
	Function :		CDrawGrid::CalcPages
	Description :	Calculates the start and end line for each 
					page of the grid. Normally, this is just
					calculated from the number of line that fits 
					on each page, but as the grid can contain 
					page breaks as well, we need to do it this way.

	Access :		Private

	Return :		void
	Parameters :	none

	Usage :			The function is only called internally.

   ============================================================*/
{

	int max = GetLines();
	int pagelength = GetLinesPerPage();
	int pagecounter = 0;
	int oldEndLine = 0;

	m_pages.RemoveAll();

	for( int t = 0 ; t < max ; t++ )
	{

		// We walk through each line, checking if we have reached 
		// the end of the page, or if the line contains a page 
		// break in any column.

		pagecounter++;

		if( IsPagebreak( m_data[ t ] ) )
		{
			CPageLength* pgl = new CPageLength;
			pgl->m_startLine = oldEndLine;
			pgl->m_endLine = t;
			m_pages.Add( pgl );

			oldEndLine = t + 1;
			pagecounter = 0;
		}
		else if( pagecounter > pagelength )
		{
			CPageLength* pgl = new CPageLength;
			pgl->m_startLine = oldEndLine;
			pgl->m_endLine = t + 1;
			m_pages.Add( pgl );

			oldEndLine = t + 1;
			pagecounter = 0;
		}

	}

	if( pagecounter )
	{

		// If we have some lines of data 
		// left for the last page...

		CPageLength* pgl = new CPageLength;
		pgl->m_startLine = oldEndLine;
		pgl->m_endLine = max;
		m_pages.Add( pgl );

	}
}

BOOL CDrawGrid::ReplaceCell( int row, int col, const CString & cell )
/* ============================================================
	Function :		CDrawGrid::ReplaceCell
	Description :	Replaces data in a specific cell in the grid.

	Access :		Public

	Return :		BOOL					-	TRUE if the data was
												replaced
	Parameters :	int row					-	Row with cell to replace
					int col					-	Column to replace
					const CString & cell	-	New data

	Usage :			Call to change data in a specific cell.

   ============================================================*/
{

	BOOL result = FALSE;

	if( row < m_data.GetSize() )
	{

		CString newdata;
		CString newline;
		CString line = m_data.GetAt( row );
		CTokenizer tok( line, _T( "|" ) );
		int max = tok.GetSize();

		for( int t = 0 ; t < max ; t++ )
		{
			if( t == col )
				newdata = cell;
			else
				tok.GetAt( t, newdata );
			newline += newdata;

			if( t < max - 1 )
				newline += _T( "|" );
		}

		m_data.RemoveAt( row );
		m_data.InsertAt( row, newline );
		result = TRUE;
	}

	return result;

}

void CDrawGrid::FillGrid( int rows, int cols, const CString & cell )
/* ============================================================
	Function :		CDrawGrid::FillGrid
	Description :	Fills the grid with data

	Access :		Public

	Return :		nothing
	Parameters :	int row					-	Rows to fill
					int col					-	Columns to fill
					const CString & cell	-	Data to put in the cells

	Usage :			Call to fill the grid with data

   ============================================================*/
{

	Clear();

	for( int row = 0 ; row < rows ; row++ )
	{
		CString line( _T( "" ) );
		for( int col = 0 ; col < cols ; col++ )
		{
			line += cell;
			if( col < cols - 1 )
				line += _T( "|" );
		}
	}

}
