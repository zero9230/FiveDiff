#ifndef _CDRAWLINE_H_AD91241C_86D8_40ED_989AB8B8033
#define _CDRAWLINE_H_AD91241C_86D8_40ED_989AB8B8033

///////////////////////////////////////////////////////////
// File :		DrawLine.h
// Created :	07/27/04
//

#include "DrawObject.h"

class CDrawLine : public CDrawObject
{
public:
// Construction/destruction

	CDrawLine::CDrawLine();

// Operations
	virtual void Draw( int page, CDC* dc );
	static CDrawObject* FromString( const CString & str );

// Attributes

};
#endif //_CDRAWLINE_H_AD91241C_86D8_40ED_989AB8B8033
