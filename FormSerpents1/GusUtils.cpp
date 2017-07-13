#include "StdAfx.h"
#include "GusUtils.h"
#include <math.h>

namespace GustyUtils
{

	template <class T> static bool RectanglesCollide( T left1, T right1, T top1, T bottom1, 
											T left2, T right2, T top2, T bottom2 )
	{
		if( right2 < left1 )
			return false;
		if( left2 > right1 )
			return false;
		if( top2 > bottom1 )
			return false;
		if( top1 > bottom2 )
			return false;
		return true;
	}


	/*bool RectanglesCollideD( double left1, double right1, double top1, double bottom1, 
											double left2, double right2, double top2, double bottom2 )
	{
		if( right2 < left1 )
			return false;
		if( left2 > right1 )
			return false;
		if( top2 > bottom1 )
			return false;
		if( top1 > bottom2 )
			return false;
		return true;
	}*/


	double GetSegmentLength( double x1, double y1, double x2, double y2 )
	{
		double ret = 0;
		double width = fabs( x2 - x1 );
		double height = fabs( y2 - y1 );

		ret = sqrt( width * width + height * height );
		return ret;
	}



	


	//
	//	=========================================== GusUtils =========================================
	//

	GusUtils::GusUtils(void)
	{
	}


	GusUtils::~GusUtils(void)
	{
	}

	template <class T> static bool GusUtils::RectanglesCollide( T left1, T right1, T top1, T bottom1, 
											T left2, T right2, T top2, T bottom2 )
	{
		if( right2 < left1 )
			return false;
		if( left2 > right1 )
			return false;
		if( top2 > bottom1 )
			return false;
		if( top1 > bottom2 )
			return false;
		return true;
	}
}