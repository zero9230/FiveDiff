#ifndef _CDOUBLERECT_H_1C0C1458_5F37_423F_BAECFA571AA0
#define _CDOUBLERECT_H_1C0C1458_5F37_423F_BAECFA571AA0

class CDoubleRect
{

public:
	CDoubleRect() {
		top = 0;
		left = 0;
		right = 0;
		bottom = 0;
	};

	CDoubleRect( double inleft, double intop, double inright, double inbottom ) {
		top = intop;
		left = inleft;
		right = inright;
		bottom = inbottom;
	};

	CPoint TopLeft() const {
		return CPoint( static_cast< int >( left ), static_cast< int >( top ) );
	};

	CPoint BottomRight() const {
		return CPoint( static_cast< int >( right ), static_cast< int >( bottom ) );
	};

	double Height()
	{
		return bottom - top;
	};

	double top;
	double left;
	double right;
	double bottom;

};

#endif // _CDOUBLERECT_H_1C0C1458_5F37_423F_BAECFA571AA0