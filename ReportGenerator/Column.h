#ifndef _CCOLUMN_H_5C03130_5919_4A14_BAFB39A6237B
#define _CCOLUMN_H_5C03130_5919_4A14_BAFB39A6237B

///////////////////////////////////////////////////////////
// File :		Column.h
// Created :	02/20/05
//


class CColumn : public CObject
{
public:
// Construction/destruction
	CColumn();
	virtual ~CColumn();

// Operations
	double GetWidth() const;
	void SetWidth( double value );
	CString GetFont() const;
	void SetFont( CString value );
	int GetFontSize() const;
	void SetFontSize( int value );
	int GetFontCharset() const;
	void SetFontCharset( int value );
	BOOL GetFontItalic() const;
	void SetFontItalic( BOOL value );
	BOOL GetFontUnderline() const;
	void SetFontUnderline( BOOL value );
	BOOL GetFontBold() const;
	void SetFontBold( BOOL value );
	BOOL GetFontStrikeout() const;
	void SetFontStrikeout( BOOL value );
	COLORREF GetFontColor() const;
	void SetFontColor( COLORREF value );
	int GetJustification() const;
	void SetJustification( int value );
	CString GetName() const;
	void SetName( CString value );


	CFont* GetColumnFont() const;

// Attributes

private:
	double width;
	CString font;
	int fontSize;
	BOOL fontItalic;
	BOOL fontUnderline;
	BOOL fontBold;
	BOOL fontStrikeout;
	COLORREF fontColor;
	int justification;
	CString name;
	int charset;

};
#endif //_CCOLUMN_H_5C03130_5919_4A14_BAFB39A6237B
