#ifndef _CDRAWBOX_H_434874C6_95A1_485E_A023645FB82
#define _CDRAWBOX_H_434874C6_95A1_485E_A023645FB82

///////////////////////////////////////////////////////////
// File :		DrawBox.h
// Created :	07/27/04
//

#include "DrawObject.h"

class CDrawBox : public CDrawObject
{
public:
// Construction/destruction
	CDrawBox::CDrawBox();

// Operations
	virtual void Draw( int page, CDC* dc );
	static CDrawObject* FromString( const CString & str );

// Attributes


};
#endif //_CDRAWBOX_H_434874C6_95A1_485E_A023645FB82
