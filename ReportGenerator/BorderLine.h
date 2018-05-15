#ifndef _CBORDERLINE_H_EA71DC98_B065_422B_952D3BA7F0C6
#define _CBORDERLINE_H_EA71DC98_B065_422B_952D3BA7F0C6

///////////////////////////////////////////////////////////
// File :		BorderLine.h
// Created :	07/27/04
//


class CBorderLine
{
public:
// Construction/destruction
	CBorderLine();
	virtual ~CBorderLine();

	void operator=( const CBorderLine& line ){

		m_visible = line.m_visible;
		m_style = line.m_style;
		m_color = line.m_color;
		m_thickness = line.m_thickness;

	};

// Operations
	BOOL GetVisible() const;
	void SetVisible( BOOL value );
	int GetStyle() const;
	void SetStyle( int value );
	COLORREF GetColor() const;
	void SetColor( COLORREF value );
	double GetThickness() const;
	void SetThickness( double value );

// Attributes

private:
	BOOL m_visible;
	int m_style;
	COLORREF m_color;
	double m_thickness;


};
#endif //_CBORDERLINE_H_EA71DC98_B065_422B_952D3BA7F0C6
