#ifndef _CDOUBLEPOINT_H_1C0C1458_5F37_423F_BAECFA571AA0
#define _CDOUBLEPOINT_H_1C0C1458_5F37_423F_BAECFA571AA0

class CDoublePoint
{
public:
	CDoublePoint(){
		x = 0;
		y = 0;
	};

	CDoublePoint( double xpos, double ypos ) {
		x = xpos;
		y = ypos;
	};

	double x;
	double y;
};

#endif // _CDOUBLEPOINT_H_1C0C1458_5F37_423F_BAECFA571AA0