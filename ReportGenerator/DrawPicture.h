#ifndef _CDRAWPICTURE_H_4E6837F8_6F3C_4A5F_9C17BF402EF0
#define _CDRAWPICTURE_H_4E6837F8_6F3C_4A5F_9C17BF402EF0

///////////////////////////////////////////////////////////
// File :		DrawPicture.h
// Created :	07/27/04
//

#include "DrawObject.h"

class CDrawPicture : public CDrawObject
{
public:
// Construction/destruction
	CDrawPicture();
	virtual ~CDrawPicture();

// Operations
	CString GetFilename() const;
	void SetFilename( CString value );
	virtual void Draw( int page, CDC* dc );
	static CDrawObject* FromString( const CString & str );

	virtual void SetHDIB( HANDLE hdib );
	virtual void SetHBITMAP( HBITMAP hbmp );

// Attributes
private:
	CString m_filename;
	HANDLE m_bitmap;

};
#endif //_CDRAWPICTURE_H_4E6837F8_6F3C_4A5F_9C17BF402EF0
