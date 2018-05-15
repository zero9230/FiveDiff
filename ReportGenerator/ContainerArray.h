#ifndef _CONTAINERARRAY_H_81AFA3A0_992F_40FA_AB544D7B68F6
#define _CONTAINERARRAY_H_81AFA3A0_992F_40FA_AB544D7B68F6

///////////////////////////////////////////////////////////
// File :		ContainerArray.h
// Created :	05/28/05
//

#include "Container.h"

class CContainerArray
{
public:
// Construction/destruction
	CContainerArray() {};

	virtual ~CContainerArray(  ) {
		RemoveAll();
	};

// Operations
	void Add( CContainer* obj ) {
		m_arr.Add( static_cast< CObject* >( obj ) );
	};

	CContainer* GetAt( int index ) const {
		CContainer* result = NULL;
		if( index >= 0 && index < GetSize() )
			result = static_cast< CContainer* >( m_arr.GetAt( index ) );

		return result;
	};

	CDrawObject* Get( const CString& field ) const {
		int max = GetSize();
		for( int t = 0 ; t < max ; t++ )
		{
			CContainer* test = GetAt( t );
			if( test )
			{
				CDrawObject* result = test->Get( field );
				if( result )
					return result;
			}
		}
		return NULL;
	};

	int GetSize() const {
		return m_arr.GetSize();
	};

	void RemoveAt( int index ) {
		if( index >= 0 && index < GetSize() ) {
			delete GetAt( index );
			m_arr.RemoveAt( index );
		}
	};

	void RemoveAll() {
		while( GetSize() )
			RemoveAt( 0 );
	};

	void Insert( int index, CContainer* obj )
	{
		if( index < 0 )
			index = 0;
		if( index < GetSize() )
			m_arr.InsertAt( index, obj );
		else
			m_arr.Add( obj );
	};

// Attributes
private:
	CObArray m_arr;

};

#endif //_CONTAINERARRAY_H_81AFA3A0_992F_40FA_AB544D7B68F6
