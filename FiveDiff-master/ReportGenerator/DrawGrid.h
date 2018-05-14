#ifndef _CDRAWGRID_H_DB911B74_E892_48F2_B7267CB4E3FC
#define _CDRAWGRID_H_DB911B74_E892_48F2_B7267CB4E3FC

///////////////////////////////////////////////////////////
// File :		DrawGrid.h
// Created :	07/27/04
//

#include "DrawObject.h"
#include "Column.h"

class CPageLength : public CObject {
public:
	CPageLength() {
		m_startLine = -1;
		m_startLine = -1;
	}
	int m_startLine;
	int m_endLine;
};

#include "TContainer.h"

class CDrawGrid : public CDrawObject
{
public:
// Construction/destruction

	CDrawGrid::CDrawGrid();

// Operations
	virtual void Draw( int page, CDC* dc );
	static CDrawObject* FromString( const CString & str );
	void AddData( const CStringArray& arr );
	void AddData( const CString& line );
	BOOL ReplaceCell( int row, int col, const CString & cell );
	void FillGrid( int rows, int cols, const CString & cell );

	int GetLines() { return m_data.GetSize(); };
	int GetLinesPerPage();
	int GetPages() { 
		CalcPages();
		return m_pages.GetSize(); 
	};

	void SetLPI( int value );
	int GetLPI() const;

	virtual void Clear();

	int GetColumns() const;

	int GetPageOffset() const;
	void SetPageOffset( int offset );

private:
// Attributes

	CStringArray	m_data;
	int				m_lpi;
	int				m_offset;

	TContainer< CColumn* > m_columns;
	void AddColumn( CColumn* column );

	virtual BOOL IsBold( CString& text ) const;
	virtual BOOL IsItalic( CString& text ) const;

	virtual BOOL IsBoldSeparator( CString& text ) const;
	virtual BOOL IsSeparator( CString& text ) const;
	virtual BOOL IsDoubleSeparator( CString& text ) const;
	virtual BOOL IsPagebreak( CString& text ) const;

	void CalcPages();
	TContainer< CPageLength* > m_pages;

};
#endif //_CDRAWGRID_H_DB911B74_E892_48F2_B7267CB4E3FC
