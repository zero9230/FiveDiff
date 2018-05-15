#ifndef _FIELDFACTORY_H_
#define _FIELDFACTORY_H_

#include "Container.h"

class CFieldFactory {

public:
	static void CreateFromString( CContainer& fields, const CStringArray& arr );

};

#endif // _FIELDFACTORY_H_