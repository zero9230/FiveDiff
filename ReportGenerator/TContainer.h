#ifndef _TCONTAINER_H_81AFA3A0_992F_40FA_AB544D7B68F6
#define _TCONTAINER_H_81AFA3A0_992F_40FA_AB544D7B68F6

///////////////////////////////////////////////////////////
// File :		TContainer.h
// Created :	08/24/04
//
template< class T > class TContainer
{
public:
// Construction/destruction
	TContainer() {};

	virtual ~TContainer(  ) {
		RemoveAll();
	};

// Operations
	void Add( T obj ) {
		m_arr.Add( obj );
	};

	T GetAt( int index ) const {
		T  result = NULL;
		if( index < GetSize() )
			result = static_cast< T >( m_arr.GetAt( index ) );
		return result;
	};

	T Get( const CString& field ) const {
		int max = GetSize();
		for( int t = 0 ; t < max ; t++ )
		{
			T test = GetAt( t );
			if( test->GetName() == field )
				return test;
		}
		return NULL;
	};

	int GetSize() const {
		return m_arr.GetSize();
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

// Attributes
private:
	CObArray m_arr;

};

#endif //_TCONTAINER_H_81AFA3A0_992F_40FA_AB544D7B68F6
