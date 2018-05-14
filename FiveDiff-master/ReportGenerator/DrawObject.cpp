/* ==========================================================================
	File :			DrawObject.cpp
	
	Class :			CDrawObject

	Date :			07/27/04

	Purpose :		"CDrawObject" is the base class for drawable objects.

	Description :	The class contain attributes for the objects, as well 
					as members to load and draw. All drawing objects must 
					be derived from this class.

	Usage :			Don't use directly.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include "DrawObject.h"
#include "BorderLine.h"

#include "Tokenizer.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CDrawObject::CDrawObject() : m_fill( FALSE ),
m_fillcolor( RGB( 0, 0, 0 ) ),
m_fieldType( FIELD_TYPE_NONE )
/* ============================================================
	Function :		CDrawObject::CDrawObject
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

}

CDrawObject::~CDrawObject()
/* ============================================================
	Function :		CDrawObject::~CDrawObject
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

}

CDoubleRect CDrawObject::GetPosition() const
/* ============================================================
	Function :		CDrawObject::GetPosition
	Description :	Accessor. Getter for "m_position".
	Access :		Public
					
	Return :		CRect	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_position".
					"m_position" is the position of the object, 
					in inches.

   ============================================================*/
{

	return m_position;

}

void CDrawObject::SetPosition( CDoubleRect value )
/* ============================================================
	Function :		CDrawObject::SetPosition
	Description :	Accessor. Setter for "m_position".
	Access :		Public
					
	Return :		void
	Parameters :	CRect value	-	Value of the attribute

	Usage :			Call to set the value of "m_position".
					"m_position" is the position of the object, 
					in inches.

   ============================================================*/
{

	m_position = value;

}

CString CDrawObject::GetName() const
/* ============================================================
	Function :		CDrawObject::GetName
	Description :	Accessor. Getter for "m_name".
	Access :		Public
					
	Return :		CString	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_name".
					"m_name" is the name of the object, and is 
					used to find fields/grids.
   ============================================================*/
{

	return m_name;

}

void CDrawObject::SetName( CString value )
/* ============================================================
	Function :		CDrawObject::SetName
	Description :	Accessor. Setter for "m_name".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	Value of the attribute

	Usage :			Call to set the value of "m_name".
					"m_name" is the name of the object, and is 
					used to find fields/grids.

   ============================================================*/
{

	m_name = value;

}

const CBorderLine* CDrawObject::GetBorder() const
/* ============================================================
	Function :		CDrawObject::GetBorder
	Description :	Accessor. Getter for "m_border".
	Access :		Public
					
	Return :		CBorderLine*	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_border".
					"m_border" is the border around the object.

   ============================================================*/
{

	return &m_border;

}

void CDrawObject::SetBorder( const CBorderLine& value )
/* ============================================================
	Function :		CDrawObject::SetBorder
	Description :	Accessor. Setter for "m_border".
	Access :		Public
					
	Return :		void
	Parameters :	const CBorderLine& value	-	Value of the attribute

	Usage :			Call to set the value of "m_border".
					"m_border" is the border around the object.

   ============================================================*/
{

	m_border = value;

}

const CBorderLine* CDrawObject::GetColumnLine() const
/* ============================================================
	Function :		CDrawObject::GetColumnLine
	Description :	Accessor. Getter for "m_columnline".
	Access :		Public
					
	Return :		CBorderLine*	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_columnline".
					"m_columnline" is the lines between columns 
					in a grid.

   ============================================================*/
{

	return &m_columnline;

}

void CDrawObject::SetColumnLine( const CBorderLine& value )
/* ============================================================
	Function :		CDrawObject::SetColumnLine
	Description :	Accessor. Setter for "m_columnline".
	Access :		Public
					
	Return :		void
	Parameters :	const CBorderLine& value	-	Value of the attribute

	Usage :			Call to set the value of "m_columnline".
					"m_columnline" is the lines between columns 
					in a grid.

   ============================================================*/
{

	m_columnline = value;

}

const CBorderLine* CDrawObject::GetRowLine() const
/* ============================================================
	Function :		CDrawObject::GetRowline
	Description :	Accessor. Getter for "m_rowline".
	Access :		Public
					
	Return :		CBorderLine*	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_rowline".
					"m_rowline" is the line between rows in a 
					grid.

   ============================================================*/
{

	return &m_rowline;

}

void CDrawObject::SetRowLine( const CBorderLine& value )
/* ============================================================
	Function :		CDrawObject::SetRowlines
	Description :	Accessor. Setter for "m_rowline".
	Access :		Public
					
	Return :		void
	Parameters :	const CBorderLine& value	-	Value of the attribute

	Usage :			Call to set the value of "m_rowline".
					"m_rowline" is the line between rows in a 
					grid.

   ============================================================*/
{

	m_rowline = value;

}

BOOL CDrawObject::GetFill() const
/* ============================================================
	Function :		CDrawObject::GetFill
	Description :	Accessor. Getter for "m_fill".
	Access :		Public
					
	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_fill". "m_fill"
					is "TRUE" if the object should be filled.

   ============================================================*/
{

	return m_fill;

}

void CDrawObject::SetFill( BOOL value )
/* ============================================================
	Function :		CDrawObject::SetFill
	Description :	Accessor. Setter for "m_fill".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	Value of the attribute

	Usage :			Call to set the value of "m_fill". "m_fill"
					is "TRUE" if the object should be filled.

   ============================================================*/
{

	m_fill = value;

}

COLORREF CDrawObject::GetFillColor() const
/* ============================================================
	Function :		CDrawObject::GetFillColor
	Description :	Accessor. Getter for "m_fillcolor".
	Access :		Public
					
	Return :		COLORREF	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_fillcolor".
					"m_fillcolor" is the color to fill with if 
					"m_fill" is "TRUE".

   ============================================================*/
{

	return m_fillcolor;

}

void CDrawObject::SetFillColor( COLORREF value )
/* ============================================================
	Function :		CDrawObject::SetFillColor
	Description :	Accessor. Setter for "m_fillcolor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	Value of the attribute

	Usage :			Call to set the value of "m_fillcolor".
					"m_fillcolor" is the color to fill with if 
					"m_fill" is "TRUE".

   ============================================================*/
{

	m_fillcolor = value;

}

int CDrawObject::FromStringCommon( CDrawObject* obj, const CString & data )
/* ============================================================
	Function :		CDrawObject::FromStringCommon
	Description :	Parses the object-common header in "data".
	Access :		Protected

	Return :		int						-	The position in "data" 
												after the parse.
	Parameters :	CDrawObject* obj		-	Object to set data to.
					const CString & data	-	Data to set
					
	Usage :			Call to parse the common first part of "data" 
					when loading objects from string.

   ============================================================*/
{
	CTokenizer contents( data, _T( "," ) );
	double		left;
	double		top;
	double		right;
	double		bottom;
	CString		title;
	CString		name;
	int			group;
	int			count = 0;

	contents.GetAt( count++, left );
	contents.GetAt( count++, top );
	contents.GetAt( count++, right );
	contents.GetAt( count++, bottom );
	contents.GetAt( count++, title );
	contents.GetAt( count++, name );
	contents.GetAt( count++, group );

	title.Replace( _T( "\\colon" ), _T( ":" ) );
	title.Replace( _T( "\\semicolon" ), _T( ";" ) );
	title.Replace( _T( "\\comma" ), _T( "," ) );
	title.Replace( _T( "\\newline" ), _T( "\r\n" ) );

	name.Replace( _T( "\\colon" ), _T( ":" ) );
	name.Replace( _T( "\\semicolon" ), _T( ";" ) );
	name.Replace( _T( "\\comma" ), _T( "," ) );
	name.Replace( _T( "\\newline" ), _T( "\r\n" ) );

	obj->SetName( name );
	obj->SetTitle( title );

	obj->SetPosition( CDoubleRect( left, top, right, bottom ) );

	return count;

}

CString CDrawObject::GetFontName() const
/* ============================================================
	Function :		CDrawObject::GetFontName
	Description :	Accessor. Getter for "m_fontName"
	Access :		Public

	Return :		CString	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_fontName;
}

void CDrawObject::SetFontName( CString value )
/* ============================================================
	Function :		CDrawObject::SetFontName
	Description :	Accessor. Setter for "m_fontName"
	Access :		Public

	Return :		void
	Parameters :	CString value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_fontName = value;
}

int CDrawObject::GetFontSize() const
/* ============================================================
	Function :		CDrawObject::GetFontSize
	Description :	Accessor. Getter for "m_fontSize"
	Access :		Public

	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_fontSize;
}

void CDrawObject::SetFontSize( int value )
/* ============================================================
	Function :		CDrawObject::SetFontSize
	Description :	Accessor. Setter for "m_fontSize"
	Access :		Public

	Return :		void
	Parameters :	int value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_fontSize = value;
}

int CDrawObject::GetFontCharset() const
/* ============================================================
	Function :		CDrawObject::GetFontCharset
	Description :	Accessor. Getter for "m_charset"
	Access :		Public

	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_charset;
}

void CDrawObject::SetFontCharset( int value )
/* ============================================================
	Function :		CDrawObject::SetFontCharset
	Description :	Accessor. Setter for "m_charset"
	Access :		Public

	Return :		void
	Parameters :	int value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_charset = value;
}

BOOL CDrawObject::GetFontBold() const
/* ============================================================
	Function :		CDrawObject::GetFontBold
	Description :	Accessor. Getter for "m_fontBold"
	Access :		Public

	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_fontBold;
}

void CDrawObject::SetFontBold( BOOL value )
/* ============================================================
	Function :		CDrawObject::SetFontBold
	Description :	Accessor. Setter for "m_fontBold"
	Access :		Public

	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_fontBold = value;
}

BOOL CDrawObject::GetFontItalic() const
/* ============================================================
	Function :		CDrawObject::GetFontItalic
	Description :	Accessor. Getter for "m_fontItalic"
	Access :		Public

	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_fontItalic;
}

void CDrawObject::SetFontItalic( BOOL value )
/* ============================================================
	Function :		CDrawObject::SetFontItalic
	Description :	Accessor. Setter for "m_fontItalic"
	Access :		Public

	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_fontItalic = value;
}

BOOL CDrawObject::GetFontUnderline() const
/* ============================================================
	Function :		CDrawObject::GetFontUnderline
	Description :	Accessor. Getter for "m_fontUnderline"
	Access :		Public

	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_fontUnderline;
}

void CDrawObject::SetFontUnderline( BOOL value )
/* ============================================================
	Function :		CDrawObject::SetFontUnderline
	Description :	Accessor. Setter for "m_fontUnderline"
	Access :		Public

	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_fontUnderline = value;
}

BOOL CDrawObject::GetFontStrikeout() const
/* ============================================================
	Function :		CDrawObject::GetFontStrikeout
	Description :	Accessor. Getter for "m_fontStrikeout"
	Access :		Public

	Return :		BOOL	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_fontStrikeout;
}

void CDrawObject::SetFontStrikeout( BOOL value )
/* ============================================================
	Function :		CDrawObject::SetFontStrikeout
	Description :	Accessor. Setter for "m_fontStrikeout"
	Access :		Public

	Return :		void
	Parameters :	BOOL value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_fontStrikeout = value;
}

COLORREF CDrawObject::GetFontColor() const
/* ============================================================
	Function :		CDrawObject::GetFontColor
	Description :	Accessor. Getter for "m_fontColor"
	Access :		Public

	Return :		COLORREF	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	return m_fontColor;
}

void CDrawObject::SetFontColor( COLORREF value )
/* ============================================================
	Function :		CDrawObject::SetFontColor
	Description :	Accessor. Setter for "m_fontColor"
	Access :		Public

	Return :		void
	Parameters :	COLORREF value	-	Value of the attribute
					
	Usage :			Accessor for the font attribute used to 
					draw the content of the object.

   ============================================================*/
{
	m_fontColor = value;
}

void CDrawObject::SetJustification( int value )
/* ============================================================
	Function :		CDrawObject::SetJustification
	Description :	Accessor. Getter for "m_justification"
	Access :		Public

	Return :		void
	Parameters :	int value	-	Value of the attribute
					
	Usage :			Accessor for the justification of the text.

   ============================================================*/
{
	m_justification = value;
}

int CDrawObject::GetJustification() const
/* ============================================================
	Function :		CDrawObject::GetJustification
	Description :	Accessor. Setter for "m_justification"
	Access :		Public

	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the justification of the text.

   ============================================================*/
{
	return m_justification;
}

CString CDrawObject::GetTitle() const
/* ============================================================
	Function :		CDrawObject::GetTitle
	Description :	Accessor. Getter for "m_title"
	Access :		Public

	Return :		CString	-	Value of the attribute
	Parameters :	none

	Usage :			Accessor for the title of the object.

   ============================================================*/
{

	return m_title;

}

void CDrawObject::SetTitle( CString value )
/* ============================================================
	Function :		CDrawObject::SetTitle
	Description :	Accessor. Getter for "m_title"
	Access :		Public

	Return :		void
	Parameters :	CString value	-	Value of the attribute
					
	Usage :			Accessor for the title of the object.

   ============================================================*/
{
	m_title = value;
}

void CDrawObject::Clear()
/* ============================================================
	Function :		CDrawObject::Clear
	Description :	Clears the data in this object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Does nothing in the default implementation.

   ============================================================*/
{

	// Empty

}

int CDrawObject::GetFieldType() const
/* ============================================================
	Function :		CDrawObject::GetFieldType
	Description :	Returns the field type of the object.
	Access :		Public

	Return :		int		-	The field type
	Parameters :	none

	Usage :			Field types are defined in DrawObject.h, 
					and it can be one of the following:
						"FIELD_TYPE_NONE"
						"FIELD_TYPE_GRID"
						"FIELD_TYPE_FIELD"
						"FIELD_TYPE_LABEL"
						"FIELD_TYPE_BOX"
						"FIELD_TYPE_ELLIPSE"
						"FIELD_TYPE_LINE"
						"FIELD_TYPE_PICTURE"

   ============================================================*/
{

	return m_fieldType;

}

void CDrawObject::SetFieldType( int value )
/* ============================================================
	Function :		CDrawObject::SetFieldType
	Description :	Sets the field type of the object.
	Access :		Public

	Return :		void
	Parameters :	int value	-	The field type.
					
	Usage :			Field types are defined in DrawObject.h, 
					and it can be one of the following:
						"FIELD_TYPE_NONE"
						"FIELD_TYPE_GRID"
						"FIELD_TYPE_FIELD"
						"FIELD_TYPE_LABEL"
						"FIELD_TYPE_BOX"
						"FIELD_TYPE_ELLIPSE"
						"FIELD_TYPE_LINE"
						"FIELD_TYPE_PICTURE"

   ============================================================*/
{

	m_fieldType = value;

}
