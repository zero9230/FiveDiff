#ifndef _CDRAWFIELD_H_DB911B74_E892_48F2_B7267CB4E3FC
#define _CDRAWFIELD_H_DB911B74_E892_48F2_B7267CB4E3FC

///////////////////////////////////////////////////////////
// File :		DrawField.h
// Created :	07/27/04
//

#include "DrawObject.h"

class CDrawField : public CDrawObject
{
public:
// Construction/destruction
	CDrawField::CDrawField();

// Operations
	virtual void Draw( int page, CDC* dc );
	static CDrawObject* FromString( const CString & str );

	void AddData( const CString& str ) { SetTitle( str ); };
	virtual void Clear();

protected:
	virtual void ReplaceFields( int page, CString & str ) const;

private:
	virtual BOOL IsBold( CString& text ) const;
	virtual BOOL IsItalic( CString& text ) const;

};
#endif //_CDRAWFIELD_H_DB911B74_E892_48F2_B7267CB4E3FC
