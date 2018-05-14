#ifndef _CDRAWELLIPSE_H_29A6772B_3A54_4F8D_97A5D20456D
#define _CDRAWELLIPSE_H_29A6772B_3A54_4F8D_97A5D20456D

///////////////////////////////////////////////////////////
// File :		DrawEllipse.h
// Created :	07/27/04
//

#include "DrawObject.h"

class CDrawEllipse : public CDrawObject
{
public:
// Construction/destruction
	CDrawEllipse::CDrawEllipse();

// Operations
	virtual void Draw( int page, CDC* dc );
	static CDrawObject* FromString( const CString & str );

// Attributes

};
#endif //_CDRAWELLIPSE_H_29A6772B_3A54_4F8D_97A5D20456D
