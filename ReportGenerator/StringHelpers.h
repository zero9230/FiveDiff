#ifndef _STRINGHELPERS_H_
#define _STRINGHELPERS_H_

void	MakeSaveString( CString& str );
void	UnmakeSaveString( CString& str );
int		ReplaceTag( CString& text, const CString& tag );
void	Tokenize( const CString& data, CStringArray& arr );

HANDLE	DDBToDIB( HBITMAP bitmap );

#endif // _STRINGHELPERS_H_