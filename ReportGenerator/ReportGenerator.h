#ifndef _CREPORTGENERATOR_H_688F6432_632D_42FB_B5ADC773DB0
#define _CREPORTGENERATOR_H_688F6432_632D_42FB_B5ADC773DB0

///////////////////////////////////////////////////////////
// File :		ReportGenerator.h
// Created :	07/27/04
//

#include "ContainerArray.h"
#include "DrawObject.h"

class CReportGenerator
{
public:
// Construction/destruction
	CReportGenerator();
	virtual ~CReportGenerator();

// Operations
	virtual CString GetReportname() const;
	virtual void SetReportname( CString value );
	virtual BOOL SetReportfile( CString value );

	virtual BOOL Add( const CString & field, const CString & data );
	virtual BOOL Add( const CString & field, const CStringArray & data );

	virtual BOOL FillGrid( const CString & field, int rows, int cols, const CString & data = "" );
	virtual BOOL ReplaceCell( const CString & field, int row, int col, const CString & data );

	virtual void New();
	virtual void Clear();

	virtual BOOL Print();
	virtual BOOL Print( CDC * dc );
	virtual void PrintPage( CDC * dc, int page = 0 );
	virtual int CalculatePages();

	const CString& GetErrorMessage();

	// Data
	virtual int GetSize() const;
	virtual int GetTemplateSize( int tplte ) const;
	virtual CString GetFieldName( int field, int tplate = 0 ) const;
	virtual int GetFieldType( const CString& field, int tplate = -1 ) const;
	virtual int GetFieldColumns( const CString& field, int tplate = -1 ) const;

	virtual void AddObject( CDrawObject* obj, int tplate = 0 );
	CDrawObject* GetObject( const CString& field, int tplate = -1 ) const;

	virtual BOOL AddTemplate( const CString& filename, int type = TEMPLATE_TYPE_SECTION );
	virtual BOOL AddTemplate( const CStringArray& arr, int type = TEMPLATE_TYPE_SECTION );
	virtual BOOL AddTemplate( UINT resourceID, int type = TEMPLATE_TYPE_SECTION );
	virtual BOOL AddTemplate( CFile& f, int type = TEMPLATE_TYPE_SECTION );
	virtual BOOL AddTemplate( LPCTSTR buf, int type = TEMPLATE_TYPE_SECTION );

protected:

	// Misc
	virtual void SetErrorMessage( const CString& error );
	virtual const CContainerArray& GetData() const;
	BOOL ParseTemplate( const CStringArray& arr, int type = TEMPLATE_TYPE_SECTION );
	BOOL CheckTemplate( int type ) const;
	CContainer* GetTemplate( int page ) const;
	BOOL ContainsEmptyGrid( int tplt ) const;
	void SetPageOffset( int tplt, int page );

// Attributes
private:
	CString m_reportname;
	CContainerArray m_fields;

	int m_pages;
	CString m_error;

};

#endif //_CREPORTGENERATOR_H_688F6432_632D_42FB_B5ADC773DB0
