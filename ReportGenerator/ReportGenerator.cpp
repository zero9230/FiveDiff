/* ==========================================================================
	File :			ReportGenerator.cpp
	
	Class :			CReportGenerator

	Date :			07/27/04

	Purpose :		"CReportGenerator" is a print engine for reports.

	Description :	"CReportGenerator" works by loading report templates, 
					filling them with data and printing the to the printer 
					(or screen). The class loads report template in the 
					form of text files, and the member "Add" can then be 
					used to set data to the fields. There are two members, 
					one for fields (which takes a string) and one for 
					grids (taking a "CStringArray").

	Usage :			Add a "CReportGenerator" member to your class. Set the 
					report template with "SetReportfile". Add data to 
					fields with "Add". For grids, "Add" takes a "CStringArray" 
					as input. Each string in the array contains a single 
					line for the grid, with each column delimited with a '|'.

					To add new data to the report, but keeping the template, 
					call "Clear".

					A multi-template report is created by adding templates with 
					"AddTemplate" instead. A multi-template report can contain 
					a title page (that will be just one page), one or more 
					section(s) and a summary (that will also just be one page). 
					A grid with the same name can exist on the title-page, a 
					section and the summary, and data added will be spread 
					across the three. If there is not enough data, first the 
					section will be suppressed, in second hand the summary.

					Fields can be added by calling "AddObject" with a pointer 
					to the correct type. Note that coordinates must be expressed 
					in inches (or fractions thereof).

					Objects (added both from a template or by calling "AddObject") 
					can be accessed by calling "GetObject", and the attributes 
					can be modified at runtime.
   ========================================================================
	Changes :		28/3 2005	Version 2.0
   ========================================================================
					24/6 2006	Returning TRUE from Add when adding data
								as per documentation

								Added support for font charset. 
								(Vladimir Svrkota, J Bartkowiak).

								Added locale-handling (J Bartkowiak).

								Added [%pagebreak%]-command for grids 
								(Charlie Curry, Carsten B Poulsen)

								Added "ReplaceCell" to set cell data in a 
								grid (Carsten B Poulsen)
   ========================================================================*/

#include "stdafx.h"
#include "ReportGenerator.h"
#include "TextFile/TextFile.h"
#include "FieldFactory.h"
#include "UnitConversion.h"
#include "StringHelpers.h"
#include "Tokenizer.h"

#include "DrawGrid.h"
#include "DrawField.h"

#include <math.h>

////////////////////////////////////////////////////////////////////
// Public functions
//
CReportGenerator::CReportGenerator() : m_pages( 0 )
/* ============================================================
	Function :		CReportGenerator::CReportGenerator
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

CReportGenerator::~CReportGenerator()
/* ============================================================
	Function :		CReportGenerator::~CReportGenerator
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	New();

}

CString CReportGenerator::GetReportname() const
/* ============================================================
	Function :		CReportGenerator::GetReportname
	Description :	Accessor. Getter for "m_reportname".
	Access :		Public
					
	Return :		CString
	Parameters :	none

	Usage :			Call to get the value of "m_reportname".

   ============================================================*/
{

	return m_reportname;

}

void CReportGenerator::SetReportname( CString value )
/* ============================================================
	Function :		CReportGenerator::SetReportname
	Description :	Accessor. Setter for "m_reportname".
	Access :		Public
					
	Return :		void
	Parameters :	CString value

	Usage :			Call to set the value of "m_reportname".

   ============================================================*/
{

	if( m_reportname.GetLength() )
		New();

	m_reportname = value;

}

BOOL CReportGenerator::Add( const CString & field, const CString & data )
/* ============================================================
	Function :		CReportGenerator::Add
	Description :	Adds data to a text field in the report.
	Access :		Public
					
	Return :		void
	Parameters :	const CString & field	-	Field name of 
												field to add data 
												to.
					const CString & data	-	Data to add

	Usage :			Call to add data to a text field.

   ============================================================*/
{

	SetErrorMessage( _T( "" ) );
	BOOL result = FALSE;

	if( GetData().GetSize() )
	{

		// Validate that the desired field is not a grid
		CDrawField* obj = dynamic_cast< CDrawField* >( GetObject( field ) );
		if( obj )
		{
			obj->AddData( data );
			result = TRUE;
		}
	}

	return result;

}

BOOL CReportGenerator::Add( const CString & field, const CStringArray & data )
/* ============================================================
	Function :		CReportGenerator::Add
	Description :	Adds "data" to the grid "field". Data is 
					assumed to be one string per row, columns 
					delimited with a |-character.
	Access :		Public
					
	Return :		BOOL						-	"TRUE" if data 
													was added. If 
													"FALSE", the 
													field does not 
													exist or is not 
													a grid.
	Parameters :	const CString & field		-	Field name of 
													grid to add 
													data to
					const CStringArray & data	-	Data to add

	Usage :			Call to add data to a grid. "AddData" will
					spread the data for a grid over several 
					templates, that is, if a report contains a 
					title page, a section and a summary, and all 
					three have a grid with the same name, data 
					added will first fill up the title page, 
					then the summary and last the section. 
					Several sections with a grid with the same 
					name will not work, however. Note that if 
					there is not enough data to fill the summary 
					or section, the summary or section will not 
					be printed.

   ============================================================*/
{

	// Assign to title and summary pages first of all.
	// If a grid stretches over title, section and summary and 
	// the number of lines are not enough to put at least one 
	// row in each, the section will be skipped first, then 
	// the summary.

	SetErrorMessage( _T( "" ) );

	if( GetData().GetSize() )
	{
		int max = data.GetSize();
		int lastTemplate = GetData().GetSize() - 1;
		int titleLines = 0;
		int summaryLines = max;
		CDrawGrid* titlegrid = NULL;
		CDrawGrid* summarygrid = NULL;
		CDrawGrid* sectiongrid = NULL;

		CContainer* title = GetData().GetAt( 0 );
		if( title->GetType() == TEMPLATE_TYPE_TITLE_PAGE )
		{
			titlegrid = dynamic_cast< CDrawGrid* >( GetObject( field, 0 ) );
			if( titlegrid )
				titleLines = titlegrid->GetLinesPerPage();
		}

		for( int t = 0 ; t <= lastTemplate ; t++ )
		{
			CContainer* fields = GetData().GetAt( t );
			if( fields && fields->GetType() == TEMPLATE_TYPE_SECTION )
			{
				sectiongrid = dynamic_cast< CDrawGrid* >( GetObject( field, t ) );
				if( sectiongrid )
					t = lastTemplate + 1;
			}
		}

		CContainer* summary = GetData().GetAt( lastTemplate );
		if( summary->GetType() == TEMPLATE_TYPE_SUMMARY_PAGE )
		{
			summarygrid = dynamic_cast< CDrawGrid* >( GetObject( field, lastTemplate ) );
			if( summarygrid )
			{
				int nontitlelines = max - titleLines;
				int remainder = min( summarygrid->GetLinesPerPage(), nontitlelines % sectiongrid->GetLinesPerPage() );
				if( sectiongrid )
					summaryLines = max - remainder;
				else
					summaryLines = max - summarygrid->GetLinesPerPage();
			}
		}


		for( int i = 0 ; i < max ; i++ )
		{

			BOOL added = FALSE;
			CString line = data[ i ];
			if( i < titleLines )
			{
				titlegrid->AddData( line );
				added = TRUE;
			}
			else if( i >= summaryLines )
			{
				summarygrid->AddData( line );
				added = TRUE;
			}
			else
			{
				for( int t = 0 ; t <= lastTemplate ; t++ )
				{
					CContainer* fields = GetData().GetAt( t );
					if( fields && fields->GetType() == TEMPLATE_TYPE_SECTION )
					{
						CDrawGrid* obj = dynamic_cast< CDrawGrid* >( GetObject( field, t ) );
						if( obj )
						{
							obj->AddData( line );
							added = TRUE;
						}
					}
				}
			}
			if( !added )
				return FALSE;

		}
	}

	return TRUE;

}

void CReportGenerator::New()
/* ============================================================
	Function :		CReportGenerator::New
	Description :	Clears the current report, removes the 
					template as well.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			Call before loading a new report template.

   ============================================================*/
{

	m_fields.RemoveAll();
	m_reportname = _T( "" );

}

BOOL CReportGenerator::Print()
/* ============================================================
	Function :		CReportGenerator::Print
	Description :	Prints the current template and data to 
					the default printer.
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if successful.
	Parameters :	none

	Usage :			Call to print the current report.

   ============================================================*/
{

	BOOL	result = FALSE;

	// Create default printer CDC
	CPrintDialog printer( FALSE );

	if( printer.GetDefaults() )
	{

		HDC hdcPrinter = printer.GetPrinterDC();
		CDC dc;
		dc.Attach( hdcPrinter );

		// Print to CDC
		Print( &dc );
		dc.EndDoc();

	}

	return result;

}

void CReportGenerator::PrintPage( CDC * dc, int page )
/* ============================================================
	Function :		CReportGenerator::PrintPage
	Description :	Prints a specific page of the report.
	Access :		Public
					
	Return :		void
	Parameters :	CDC * dc	-	"CDC" to print to.
					int page	-	Page to print

	Usage :			Call to print a specific page. Can also be 
					used to print to screen.

   ============================================================*/
{

	// Loop fields on screen, fill with
	// data as appropriate
	CUnitConversion::Init( dc->GetDeviceCaps( LOGPIXELSY ) );

	// Find the correct template
	CContainer* fields = GetTemplate( page );
	if( fields )
	{
		int max = fields->GetSize();
		for( int t = 0 ; t < max ; t++ )
		{

			CDrawObject* obj = fields->GetAt( t );
			if( obj )
				obj->Draw( page, dc );
		}
	}
}

int CReportGenerator::GetSize() const
/* ============================================================
	Function :		CReportGenerator::GetSize
	Description :	Returns the number of objects in the 
					report template.
	Access :		Public
					
	Return :		int		-	Number of objects.
	Parameters :	none

	Usage :			Call to get the number of objects of the 
					current template.

   ============================================================*/
{

	return m_fields.GetSize();

}

BOOL CReportGenerator::Print( CDC * dc )
/* ============================================================
	Function :		CReportGenerator::Print
	Description :	Prints the report to a specific "CDC".
	Access :		Private
					
	Return :		BOOL		-	"TRUE" if successful.
	Parameters :	CDC * dc	-	"CDC" to print to

	Usage :			Call to print to a non-default printer

   ============================================================*/
{

	// Calculate the number of pages
	int pages = CalculatePages();

	DOCINFO docinfo;
	memset( &docinfo, 0, sizeof( docinfo ) ); 
	docinfo.cbSize = sizeof( docinfo );
	docinfo.lpszDocName = GetReportname();

	if( dc->StartDoc( &docinfo ) )
	{
		for( int t = 1 ; t <= pages ; t++ )
		{
			if( dc->StartPage() )
			{
				PrintPage( dc, t );
				dc->EndPage();
			}
			else
			{
				dc->AbortDoc();
				return FALSE;
			}
		}
		dc->EndDoc();
	}

	return TRUE;

}

int CReportGenerator::CalculatePages()
/* ============================================================
	Function :		CReportGenerator::CalculatePages
	Description :	The function returns the number of pages 
					necessary for this report
	Access :		Private
					
	Return :		int		-	The number of pages necessary
								for this report
	Parameters :	none

	Usage :			Call to get the pages for this report. Will 
					always return a minimum of 1 pages.

   ============================================================*/
{

	int pages = 0;
	int tpls = GetData().GetSize();
	for( int t = 0 ; t < tpls ; t++ )
	{
		CContainer* fields = GetData().GetAt( t );
		if( fields->GetType() == TEMPLATE_TYPE_TITLE_PAGE )
		{
			pages++;
			fields->SetStartPage( 1 );
			fields->SetEndPage( 1 );
			SetPageOffset( t, 1 );
		}
		else if( fields->GetType() == TEMPLATE_TYPE_SUMMARY_PAGE )
		{
			// If the template contains a grid with no 
			// data, assign -1 as start and end page as we will 
			// not print the summary.

			if( ContainsEmptyGrid( t ) )
			{
				fields->SetStartPage( -1 );
				fields->SetEndPage( -1 );
				SetPageOffset( t, -1 );
			}
			else
			{
				pages++;
				fields->SetStartPage( pages );
				fields->SetEndPage( pages );
				SetPageOffset( t, pages );
			}
		}
		else
		{
			// If a grid contains no data, assign -1 
			// as start and end page as we will not print 
			// this page.

			// Loop the grids, find the one using the most pages
			int max = fields->GetSize();
			BOOL emptygrid = FALSE;
			int maxpages = 1;
			for( int i = 0 ; i < max ; i++ )
			{
				CDrawGrid* element = dynamic_cast< CDrawGrid* >( fields->GetAt( i ) );
				if( element )
				{
					double lines = (double ) element->GetLines();
					if( lines == 0 )
						emptygrid = TRUE;

					int gridpages = element->GetPages();
					maxpages = max( gridpages, maxpages );
				}
			}

			if( emptygrid )
			{
				fields->SetStartPage( -1 );
				fields->SetEndPage( -1 );
				SetPageOffset( t, -1 );
			}
			else
			{
				pages++;
				fields->SetStartPage( pages );
				SetPageOffset( t, pages );
				pages += ( maxpages - 1);
				fields->SetEndPage( pages );
			}
		}
	}

	return pages;

}

BOOL CReportGenerator::SetReportfile( CString value )
/* ============================================================
	Function :		CReportGenerator::SetReportfile
	Description :	Loads "value" as the single template for
					this report.
	Access :		Public

	Return :		BOOL			-	"TRUE" if successful
	Parameters :	CString value	-	Name of the template file
					
	Usage :			Call to just load a single template.

   ============================================================*/
{

	SetErrorMessage( _T( "" ) );

	BOOL result = FALSE;
	CTextFile file;
	CStringArray arr;

	if( file.ReadTextFile( value, arr ) )
		result = ParseTemplate( arr );
	else
		SetErrorMessage( file.GetErrorMessage() );

	return result;

}

void CReportGenerator::SetErrorMessage( const CString& error )
/* ============================================================
	Function :		CReportGenerator::SetErrorMessage
	Description :	Sets the class error message
	Access :		Protected

	Return :		void
	Parameters :	const CString& error	-	Error message
					
	Usage :			"m_error" is used to report errors back to 
					the caller.

   ============================================================*/
{

	m_error = error;

}

const CContainerArray& CReportGenerator::GetData() const
/* ============================================================
	Function :		CReportGenerator::GetData
	Description :	Returns the field object container.
	Access :		Protected

	Return :		const CContainerArray&	-	Container
	Parameters :	none

	Usage :			Call to get access to the class data container.

   ============================================================*/
{

	return m_fields;

}

const CString& CReportGenerator::GetErrorMessage()
/* ============================================================
	Function :		CReportGenerator::GetErrorMessage
	Description :	Gets the current error, if any, for the 
					class.
	Access :		Public

	Return :		const CString&	-	Error message. Empty 
										if none.
	Parameters :	none

	Usage :			"m_error" is used to report errors back to 
					the caller.

   ============================================================*/
{

	return m_error;

}

void CReportGenerator::Clear()
/* ============================================================
	Function :		CReportGenerator::Clear
	Description :	Clears the data in the report.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to clear before adding new data. Will 
					not remove the template.

   ============================================================*/
{

	for( int t = 0 ; t < GetData().GetSize() ; t++ )
		GetData().GetAt( t )->Clear();

}

int CReportGenerator::GetFieldType( const CString& field, int tplate ) const
/* ============================================================
	Function :		CReportGenerator::GetFieldType
	Description :	Returns the type for field "field"
	Access :		Public

	Return :		int						-	Field type
	Parameters :	const CString& field	-	Name of the field
					
	Usage :			Field types are defined in DrawObject.h, 
					and it can be one of the following:
						"FIELD_TYPE_NONE"
						"FIELD_TYPE_GRID"
						"FIELD_TYPE_FIELD"
						"FIELD_TYPE_LABEL"
						"FIELD_TYPE_BOX"
						"FIELD_TYPE_ELLIPSE"
						"FIELD_TYPE_LINE"
						"FIELD_TYPE_PICTURE"

   ============================================================*/
{

	int result = FIELD_TYPE_NONE;
	CDrawObject* obj = GetObject( field, tplate );
	if( obj )
		result = obj->GetFieldType();

	return result;

}

CString CReportGenerator::GetFieldName( int field, int tplate ) const
/* ============================================================
	Function :		CReportGenerator::GetFieldName
	Description :	Gets the field name for the field with the 
					index "field"
	Access :		Public

	Return :		CString		-	Name of the field
	Parameters :	int field	-	Index of the field
					int	tplate	-	Template to get field from
	Usage :			Call to get the field name of a field

   ============================================================*/
{
	
	CString result( _T( "" ) );
	CContainer* fields = GetData().GetAt( tplate );
	if( fields )
	{
		CDrawObject* obj = fields->GetAt( field );
		if( obj )
			result = obj->GetName();
	}

	return result;

}

int CReportGenerator::GetFieldColumns( const CString& field, int tplate ) const
/* ============================================================
	Function :		CReportGenerator::GetFieldColumns
	Description :	Get the number of the columns for the field
	Access :		Public

	Return :		int						-	Number of columns. 
												-1 if not a grid
	Parameters :	const CString&	field	-	Name of field
					
	Usage :			Call to get the number of fields for a grid.

   ============================================================*/
{

	int result = -1;
	if( GetFieldType( field, tplate ) == FIELD_TYPE_GRID )
	{
		CDrawGrid* obj = static_cast< CDrawGrid* >( GetObject( field, tplate ) );
		if( obj )
			result = obj->GetColumns();
	}

	return result;

}

void CReportGenerator::AddObject( CDrawObject* obj, int tplate )
/* ============================================================
	Function :		CReportGenerator::AddObject
	Description :	Adds a field to template "tplate".
	Access :		Public

	Return :		void
	Parameters :	CDrawObject* obj	-	Field to add
					int tplate			-	Template to add field to
					
	Usage :			Call to add a new field to the template.

   ============================================================*/
{

	CContainer* fields = GetData().GetAt( tplate );
	if( fields )
		fields->Add( obj );

}

CDrawObject* CReportGenerator::GetObject( const CString& field, int tplate ) const
/* ============================================================
	Function :		CReportGenerator::GetObject
	Description :	Gets the fields named "field" from the template "tplate".
	Access :		Public

	Return :		CDrawObject*	-	The object, or "NULL" if not found
	Parameters :	int tplate		-	The template to get the field from
					
	Usage :			If "tplate" is -1, the first field with this 
					name in all templates is returned.

   ============================================================*/
{

	CDrawObject* obj = NULL;
	if( tplate != -1 )
	{
		CContainer* fields = GetData().GetAt( tplate );
		if( fields )
			obj = fields->Get( field );
	}
	else
	{
		int tpls = GetData().GetSize();
		for( int i = 0 ; i < tpls ; i++ )
		{
			obj = GetObject( field, i );

			// If non-NULL we want to break here
			if( obj )
				return obj;
		}
	}

	return obj;

}

BOOL CReportGenerator::ParseTemplate( const CStringArray& arr, int type )
/* ============================================================
	Function :		CReportGenerator::ParseTemplate
	Description :	Parses and adds the data in "arr" to the report.
	Access :		Protected

	Return :		BOOL					-	"TRUE" if the template was added.
	Parameters :	const CStringArray& arr -	The data to create the fields from
					int type				-	The type of the template.
					
	Usage :			"type" can be one of the following:
						"TEMPLATE_TYPE_SECTION"
						"TEMPLATE_TYPE_TITLE_PAGE"
						"TEMPLATE_TYPE_SUMMARY_PAGE"

   ============================================================*/
{

	BOOL result = FALSE;

	CContainer* fields = new CContainer;
	fields->SetType( type );
	CFieldFactory::CreateFromString( *fields, arr );
	if( fields->GetSize() )
	{
		if( type == TEMPLATE_TYPE_TITLE_PAGE )
		{
			m_fields.Insert( 0, fields );
		}
		else if( type == TEMPLATE_TYPE_SUMMARY_PAGE )
		{
			m_fields.Add( fields );
		}
		else
		{
			// Check if the last template is a summary, 
			// in that case we will want to insert 
			// this as the second-to-last template
			CContainer* test = GetData().GetAt( GetData().GetSize() - 1 );
			if( test && test->GetType() == TEMPLATE_TYPE_SUMMARY_PAGE )
				m_fields.Insert( GetData().GetSize() - 2, fields );
			else
				m_fields.Add( fields );	// Just add it
		}

		result = TRUE;
	}

	return result;

}

BOOL CReportGenerator::AddTemplate( const CString& filename, int type )
/* ============================================================
	Function :		CReportGenerator::AddTemplate
	Description :	Adds a template to the report
	Access :		Public

	Return :		BOOL					-	"TRUE" if the template contained 
												any fields.
	Parameters :	const CString& filename -	File to load template from
					int type				-	Type of template to add.
					
	Usage :			"type" can be one of the following:
						"TEMPLATE_TYPE_SECTION"
						"TEMPLATE_TYPE_TITLE_PAGE"
						"TEMPLATE_TYPE_SUMMARY_PAGE"

   ============================================================*/
{
	BOOL result = FALSE;

	if( CheckTemplate( type ) )
	{
		
		SetErrorMessage( _T( "" ) );

		CString f( filename );
		CTextFile file;
		CStringArray arr;

		if( file.ReadTextFile( f, arr ) )
			result = ParseTemplate( arr, type );
		else
			SetErrorMessage( file.GetErrorMessage() );
	}

	return result;

}

BOOL CReportGenerator::AddTemplate( const CStringArray& arr, int type )
/* ============================================================
	Function :		CReportGenerator::AddTemplate
	Description :	Adds a template to the report
	Access :		Public

	Return :		BOOL	-					"TRUE" if the template contained 
												any fields.
	Parameters :	const CStringArray& arr -	Array containing the data 
												for the fields
					int type				-	Type of template to add.
					
	Usage :			"arr" is assumed to be the contents of a rpt-file.
					"type" can be one of the following:
						"TEMPLATE_TYPE_SECTION"
						"TEMPLATE_TYPE_TITLE_PAGE"
						"TEMPLATE_TYPE_SUMMARY_PAGE"

   ============================================================*/
{

	if( CheckTemplate( type ) )
	{
		
		SetErrorMessage( _T( "" ) );
		return ParseTemplate( arr, type );
	}

	return FALSE;

}

BOOL CReportGenerator::AddTemplate( UINT resourceID, int type )
/* ============================================================
	Function :		CReportGenerator::AddTemplate
	Description :	Adds a template to the report
	Access :		Public

	Return :		BOOL			-	"TRUE" if the template contained 
										any fields.
	Parameters :	UINT resourceID	-	Resource ID of the template
					int type		-	Type of template to add.
					
	Usage :			The type of the resource must be "RG_REPORT".
					"type" can be one of the following:
						"TEMPLATE_TYPE_SECTION"
						"TEMPLATE_TYPE_TITLE_PAGE"
						"TEMPLATE_TYPE_SUMMARY_PAGE"

   ============================================================*/
{

	BOOL result = FALSE;

	if( CheckTemplate( type ) )
	{
		
		// Load resource of the correct type
		HRSRC hRes = ::FindResource( AfxGetResourceHandle(), MAKEINTRESOURCE( resourceID ), _T( "RG_REPORT" ) );
		if( hRes )
		{
			HGLOBAL hGlobal = ::LoadResource( AfxGetResourceHandle(), hRes );
			if( hGlobal )
			{

				LPTSTR buf = ( LPTSTR ) ::LockResource( hGlobal );
				if( buf )
					result = AddTemplate( buf, type );

			}
		}
	}

	return result;

}

BOOL CReportGenerator::AddTemplate( CFile& f, int type )
/* ============================================================
	Function :		CReportGenerator::AddTemplate
	Description :	Adds a template to the report
	Access :		Public

	Return :		BOOL		-	"TRUE" if the template contained 
									and fields.
	Parameters :	CFile&f		-	File containing the template
					int type	-	Type of template to add.
					
	Usage :			"type" can be one of the following:
						"TEMPLATE_TYPE_SECTION"
						"TEMPLATE_TYPE_TITLE_PAGE"
						"TEMPLATE_TYPE_SUMMARY_PAGE"

   ============================================================*/
{

	BOOL result = FALSE;

	if( CheckTemplate( type ) )
	{
		
		CString data;
		int count = f.GetLength();
		if( count > 0 )
		{
			char* buf;
			buf = new char[ count ];
			if( buf )
			{

				if( f.Read( buf, count ) == ( UINT ) count )
					result = AddTemplate( ( LPTSTR ) buf, type );

				delete[] buf;

			}
		}
	}

	return result;

}

BOOL CReportGenerator::AddTemplate( LPCTSTR buf, int type )
/* ============================================================
	Function :		CReportGenerator::AddTemplate
	Description :	Adds a template to the report
	Access :		Public

	Return :		BOOL		-	"TRUE" if the template 
									contained any fields.
	Parameters :	LPCSTR buf	-	Contents of template
					int type	-	Type of template to add.
					
	Usage :			"buf" is assumed to have the contents of a rpt-file
					"type" can be one of the following:
						"TEMPLATE_TYPE_SECTION"
						"TEMPLATE_TYPE_TITLE_PAGE"
						"TEMPLATE_TYPE_SUMMARY_PAGE"

   ============================================================*/
{

	BOOL result = FALSE;
	if( CheckTemplate( type ) )
	{
		SetErrorMessage( _T( "" ) );
		CString contents( buf );
		CStringArray arr;
		Tokenize( contents, arr );

		if( ParseTemplate( arr, type ) )
			result = TRUE;
	}

	return result;

}

BOOL CReportGenerator::CheckTemplate( int type ) const
/* ============================================================
	Function :		CReportGenerator::CheckTemplate
	Description :	Tests if a template of type "type" can be 
					added to the report.
	Access :		Private

	Return :		BOOL		-	"TRUE" if a "type" template can 
									be added to the report.
	Parameters :	int type	-	Type of template to add
					
	Usage :			A report can contain a single title page and 
					summary. "type" can be one of the following:
						"TEMPLATE_TYPE_SECTION"
						"TEMPLATE_TYPE_TITLE_PAGE"
						"TEMPLATE_TYPE_SUMMARY_PAGE"

   ============================================================*/
{

	BOOL result = TRUE;

	if( GetData().GetSize() )
	{
		if( type == TEMPLATE_TYPE_TITLE_PAGE )
		{
			// Test if we already have a title page
			CContainer* test = GetData().GetAt( 0 );
			if( test && test->GetType() == type )
				result = FALSE;
		}

		if( type == TEMPLATE_TYPE_SUMMARY_PAGE )
		{
			// Test if we already have a summary page
			CContainer* test = GetData().GetAt( GetData().GetSize() - 1 );
			if( test && test->GetType() == type )
				result = FALSE;
		}
	}

	return result;

}

int CReportGenerator::GetTemplateSize( int tplte ) const
/* ============================================================
	Function :		CReportGenerator::GetTemplateSize
	Description :	Returns the number of fields in the 
					template with index "tplte"
	Access :		Private

	Return :		int			-	Number of fields in the 
									template.
	Parameters :	int tplte	-	Index of the template to test
					
	Usage :			Call to get the number of fields in an 
					individual template.

   ============================================================*/
{

	int result = 0;

	CContainer* fields = GetData().GetAt( tplte );
	if( fields )
		result = fields->GetSize();

	return result;

}

CContainer* CReportGenerator::GetTemplate( int page ) const
/* ============================================================
	Function :		CReportGenerator::GetTemplate
	Description :	Gets the template for page "page".
	Access :		Private

	Return :		CContainer*	-	The template for "page"
	Parameters :	int page	-	The page to get the template for.
					
	Usage :			Call for a report filled with data to get 
					the template for a specific print page. 
					Note that the first page is page 1.

   ============================================================*/
{
	CContainer* result = NULL;
	int max = GetData().GetSize();
	for( int t = 0 ; t < max ; t++ )
	{
		CContainer* fields = GetData().GetAt( t );
		if( fields )
		{
			if( page >= fields->GetStartPage() && page <= fields->GetEndPage() )
				result = fields;
		}
	}

	return result;
}

BOOL CReportGenerator::ContainsEmptyGrid( int tplt ) const
/* ============================================================
	Function :		CReportGenerator::ContainsEmptyGrid
	Description :	Checks if the template contains a grid with 
					no data.
	Access :		Private

	Return :		BOOL		-	"TRUE" if the template contains 
									a grid with no data.
	Parameters :	int tplt	-	The template to check.
					
	Usage :			Call to see if the template contains an empty 
					grid. Templates with empty grids will not 
					normally be printed.

   ============================================================*/
{

	BOOL result = FALSE;

	CContainer* fields = GetData().GetAt( tplt );
	if( fields )
	{
		int max = fields->GetSize();
		for( int t = 0 ; t < max ; t++ )
		{
			CDrawGrid* grid = dynamic_cast< CDrawGrid* >( fields->GetAt( t ) );
			if( grid )
				if( grid->GetLines() == 0 )
					result = TRUE;
		}
	}

	return result;

}

void CReportGenerator::SetPageOffset( int tplt, int page )
/* ============================================================
	Function :		CReportGenerator::SetPageOffset
	Description :	Sets the start page for all grids in the 
					template "tplt"
	Access :		Private

	Return :		void
	Parameters :	int tplt	-	The template to modify.
					int page	-	The start page to set.
					
	Usage :			Called during page calculations. The grids 
					must know on what page during the printout 
					they are located, to be able to print the 
					correct data.

   ============================================================*/
{
	CContainer* fields = GetData().GetAt( tplt );
	if( fields )
	{
		int max = fields->GetSize();
		for( int t = 0 ; t < max ; t++ )
		{
			CDrawGrid* grid = dynamic_cast< CDrawGrid* >( fields->GetAt( t ) );
			if( grid )
				grid->SetPageOffset( page );

		}
	}
}

BOOL CReportGenerator::ReplaceCell( const CString & field, int row, int col, const CString & data )
/* ============================================================
	Function :		CReportGenerator::ReplaceCell
	Description :	Replaces data in a specific cell in the grid "field".

	Access :		Public

	Return :		BOOL					-	TRUE if the data was
												replaced
	Parameters :	const CString & field	-	Name of the grid.
					int row					-	Row with cell to replace
					int col					-	Column to replace
					const CString & cell	-	New data

	Usage :			Call to change data in a specific cell in a grid.

   ============================================================*/
{

	SetErrorMessage( _T( "" ) );
	BOOL result = FALSE;

	if( GetData().GetSize() )
	{

		// Validate that the desired field is not a grid
		CDrawGrid* obj = dynamic_cast< CDrawGrid* >( GetObject( field ) );
		if( obj )
		{
			result = obj->ReplaceCell( row, col, data );
		}

	}

	return result;

}

BOOL CReportGenerator::FillGrid( const CString & field, int rows, int cols, const CString & data )
/* ============================================================
	Function :		CReportGenerator::FillGrid
	Description :	Fills the grid "field".with "data"

	Access :		Public

	Return :		BOOL					-	TRUE if the grid was 
												found and filled.
	Parameters :	const CString & field	-	Name of the grid to fill
					int rows				-	Number of rows to fill
					int cols				-	Number of columns to fill
					const CString & cell	-	Data to fill grid with

	Usage :			Call to fill a grid with data

   ============================================================*/
{
	SetErrorMessage( _T( "" ) );
	BOOL result = FALSE;

	if( GetData().GetSize() )
	{

		// Validate that the desired field is not a grid
		CDrawGrid* obj = dynamic_cast< CDrawGrid* >( GetObject( field ) );
		if( obj )
		{
			obj->FillGrid( rows, cols, data );
			result = TRUE;
		}

	}

	return result;

}
