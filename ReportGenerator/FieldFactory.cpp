/* ==========================================================================
	File :			FieldFactory.cpp
	
	Class :			CFieldFactory

	Date :			07/27/04

	Purpose :		"CFieldFactory" is a factory class for drawable objects.

	Description :	The class contains one static function which creates 
					drawable objects from strings.

	Usage :			Call to load a report from a text file.
   ========================================================================
	Changes :		28/3 2005	Version 2.0

   ========================================================================*/

#include "stdafx.h"
#include <locale.h>

#include "FieldFactory.h"

#include "DrawBox.h"
#include "DrawEllipse.h"
#include "DrawGrid.h"
#include "DrawLine.h"
#include "DrawPicture.h"
#include "DrawField.h"
#include "DrawLabel.h"

void CFieldFactory::CreateFromString( CContainer& fields, const CStringArray& arr )
/* ============================================================
	Function :		CFieldFactory::CreateFromString
	Description :	Creates instances of "CDrawObject"-derived 
					objects and adds them to the data container 
					"fields".
	Access :		Public

	Return :		void
	Parameters :	CContainer& fields	-	Container to add data to.
					const CStringArray& arr	-	File content to load.
					
	Usage :			Call to load a report from a file

   ============================================================*/
{

	// Save old locale and set locale for decimal-point character to "C"
	CString oldLocale = _tsetlocale(LC_NUMERIC, NULL);
	_tsetlocale(LC_NUMERIC, _T("C")); 

	int max = arr.GetSize();
	for( int t = 0 ; t < max ; t++ )
	{

		CDrawObject* obj;

		obj = CDrawBox::FromString( arr[ t ] );
		if( !obj)
			obj = CDrawEllipse::FromString( arr[ t ] );
		if( !obj)
			obj = CDrawGrid::FromString( arr[ t ] );
		if( !obj)
			obj = CDrawLine::FromString( arr[ t ] );
		if( !obj)
			obj = CDrawPicture::FromString( arr[ t ] );
		if( !obj)
			obj = CDrawField::FromString( arr[ t ] );
		if( !obj)
			obj = CDrawLabel::FromString( arr[ t ] );

		if( obj)
			fields.Add( obj );

	}

	// restore old LC_NUMERIC locale
	_tsetlocale(LC_NUMERIC, oldLocale); 

}