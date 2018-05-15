#ifndef _CDRAWOBJECT_H_1C0C1458_5F37_423F_BAECFA571AA0
#define _CDRAWOBJECT_H_1C0C1458_5F37_423F_BAECFA571AA0

///////////////////////////////////////////////////////////
// File :		DrawObject.h
// Created :	07/27/04
//

#include "BorderLine.h"
#include "DoubleRect.h"
#include "DoublePoint.h"

#define FIELD_TYPE_NONE		0
#define FIELD_TYPE_GRID		1
#define FIELD_TYPE_FIELD	2
#define FIELD_TYPE_LABEL	3
#define FIELD_TYPE_BOX		4
#define FIELD_TYPE_ELLIPSE	5
#define FIELD_TYPE_LINE		6
#define FIELD_TYPE_PICTURE	7

class CDrawObject : public CObject
{
public:
// Construction/destruction
	CDrawObject();
	virtual ~CDrawObject();

// Operations
	CDoubleRect GetPosition() const;
	void SetPosition( CDoubleRect value );
	CString GetName() const;
	void SetName( CString value );
	CString GetTitle() const;
	void SetTitle( CString value );
	const CBorderLine* GetBorder() const;
	void SetBorder( const CBorderLine& value );
	const CBorderLine* GetColumnLine() const;
	void SetColumnLine( const CBorderLine& value );
	const CBorderLine* GetRowLine() const;
	void SetRowLine( const CBorderLine& value );
	BOOL GetFill() const;
	void SetFill( BOOL value );
	COLORREF GetFillColor() const;
	void SetFillColor( COLORREF value );
	virtual void Draw( int page, CDC* dc ) = 0;

	CString GetFontName() const;
	void SetFontName( CString value );
	int GetFontSize() const;
	void SetFontSize( int value );
	BOOL GetFontBold() const;
	void SetFontBold( BOOL value );
	BOOL GetFontItalic() const;
	void SetFontItalic( BOOL value );
	BOOL GetFontUnderline() const;
	void SetFontUnderline( BOOL value );
	BOOL GetFontStrikeout() const;
	void SetFontStrikeout( BOOL value );
	void SetFontCharset( int charset );
	int GetFontCharset() const;
	COLORREF GetFontColor() const;
	void SetFontColor( COLORREF value );
	void SetJustification( int justification );
	int GetJustification() const;

	virtual void Clear();

	int GetFieldType() const;
	void SetFieldType( int value );

protected:
	static int FromStringCommon( CDrawObject* obj, const CString & data );

// Attributes
private:
	CDoubleRect m_position;
	CString m_name;
	CBorderLine m_border;
	CBorderLine m_columnline;
	CBorderLine m_rowline;
	BOOL m_fill;
	COLORREF m_fillcolor;

	CString		m_fontName;
	int			m_fontSize;
	BOOL		m_fontBold;
	BOOL		m_fontItalic;
	BOOL		m_fontUnderline;
	BOOL		m_fontStrikeout;
	COLORREF	m_fontColor;
	int			m_justification;
	int			m_charset;

	CString		m_title;

	int m_fieldType;

};
#endif //_CDRAWOBJECT_H_1C0C1458_5F37_423F_BAECFA571AA0
