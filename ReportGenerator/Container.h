#ifndef _CONTAINER_H_81AFA3A0_992F_40FA_AB544D7B68F6
#define _CONTAINER_H_81AFA3A0_992F_40FA_AB544D7B68F6

///////////////////////////////////////////////////////////
// File :		Container.h
// Created :	08/24/04
//
#include "DrawObject.h"

#define TEMPLATE_TYPE_NONE			-1
#define TEMPLATE_TYPE_SECTION		0
#define TEMPLATE_TYPE_TITLE_PAGE	1
#define TEMPLATE_TYPE_SUMMARY_PAGE	2

class CContainer : public CObject
{
public:
// Construction/destruction
	CContainer() {
		SetStartPage( 0 );
		SetEndPage( 0 );
		SetType( TEMPLATE_TYPE_NONE );
	};

	virtual ~CContainer(  ) {
		RemoveAll();
	};

// Operations
	void Add( CDrawObject* obj ) {
		m_arr.Add( obj );
	};

	CDrawObject* GetAt( int index ) const {
		CDrawObject*  result = NULL;
		if( index < GetSize() )
			result = static_cast< CDrawObject* >( m_arr.GetAt( index ) );
		return result;
	};

	CDrawObject* Get( const CString& field ) const {
		int max = GetSize();
		for( int t = 0 ; t < max ; t++ )
		{
			CDrawObject* test = GetAt( t );
			if( test->GetName() == field )
				return test;
		}
		return NULL;
	};

	int GetSize() const {
		return m_arr.GetSize();
	};

	void Clear() {
		int max = GetSize();
		for( int t = 0 ; t < max ; t++ )
			GetAt( t )->Clear();
	};

	void RemoveAt( int index ) {
		if( index < GetSize() ) {
			delete GetAt( index );
			m_arr.RemoveAt( index );
		}
	};

	void RemoveAll() {
		while( GetSize() )
			RemoveAt( 0 );
	};

	int GetType() {
		return m_type;
	};

	void SetType( int type ) {
		m_type = type;
	};

	void SetStartPage( int page )
	{
		m_startPage = page;
	};

	void SetEndPage( int page )
	{
		m_endPage = page;
	};

	int GetStartPage()
	{
		return m_startPage;
	};

	int GetEndPage()
	{
		return m_endPage;
	};

// Attributes
private:
	CObArray m_arr;
	int m_type;
	int m_startPage;
	int m_endPage;
};

#endif //_CONTAINER_H_81AFA3A0_992F_40FA_AB544D7B68F6
