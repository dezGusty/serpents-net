#include "StdAfx.h"
#include "MapObject.h"

namespace Serpents
{
	MapObject::MapObject()
	{
		init(0,0,0,0);
	}


	MapObject::MapObject(DRECT initialRect)
	{
		init(initialRect.left, initialRect.top, initialRect.right, initialRect.bottom);
	}


	MapObject::~MapObject(void)
	{
	}


	DPOINT MapObject::getLocation()
	{
		DPOINT ret;
		switch( pivot )
		{
		case CenterPivot:
			{
				double width = rect.right - rect.left;
				double height = rect.bottom - rect.top;
				ret.x = rect.left + width/2;
				ret.y = rect.top + height/2;
				break;
			}
		case TopLeftCornerPivot:
			{
				ret.x = rect.left;
				ret.y = rect.top;
				break;
			}
		}
		return ret;
	}


	DPOINT MapObject::getSize()
	{
		DPOINT ret;
		switch( pivot )
		{
		case CenterPivot:
			{
				ret.x = rect.right - rect.left;
				ret.y = rect.bottom - rect.top;
				break;
			}
		case TopLeftCornerPivot:
			{
				ret.x = rect.left;
				ret.y = rect.top;
				break;
			}
		}
		return ret;
	}


	double MapObject::getSizeFromCenter()
	{
		return (getSize().x + getSize().y)/4;
	}



	void MapObject::init(double x1, double y1, double x2, double y2)
	{
		this->setPivot(CenterPivot);
		this->setShape(ObjectShapeRectangular);
		rect.left = x1;
		rect.right = x2;
		rect.top = y1;
		rect.bottom = y2;
	}


	bool MapObject::intersectsWith(Serpents::MapObject &rhs, bool checkBorderCollision)
	{
		DRECT myRect = rhs.getBounds();

		switch( shape )
		{
		case ObjectShapeRectangular:
		case ObjectShapeSquare:
			{
				if( checkBorderCollision )
				{
					if( rect.left >= myRect.right )
						return false;
					if( rect.top >= myRect.bottom )
						return false;
					if( rect.right <= myRect.left )
						return false;
					if( rect.bottom <= myRect.top )
						return false;
				}
				else
				{
					if( rect.left > myRect.right )
						return false;
					if( rect.top > myRect.bottom )
						return false;
					if( rect.right < myRect.left )
						return false;
					if( rect.bottom < myRect.top )
						return false;
				}
				return true;
				//break;
			}
		case ObjectShapeCircular:
			{
				//	Coliziune circulara.

				DPOINT loc = getLocation();
				DPOINT loc2 = rhs.getLocation();

				double len1 = GustyUtils::GetSegmentLength( loc.x, loc.y, loc2.x, loc2.y );
				double len2 = this->getSizeFromCenter() + rhs.getSizeFromCenter();
				System::Diagnostics::Trace::WriteLine( "BP:collideswith(), len1 (dist)=" + len1.ToString("F") + " ... len2 (sumrad)=" + len2.ToString("F") );

				if( len1 >= len2 )
				{
					if( len1 == len2 && checkBorderCollision )
					{
						return true;
					}
					return false;
				}
				return true;
			}
			//break;
		}
		return true;
	}


	void MapObject::setLocation(double x, double y)
	{
		rect.left;

		switch( pivot )
		{
		case CenterPivot:
			{
				double width = rect.right - rect.left;
				double height = rect.bottom - rect.top;
				rect.left = x - width/2;
				rect.top = y - width/2;
				rect.right = x + width/2;
				rect.bottom = y + height/2;
				break;
			}
		case TopLeftCornerPivot:
			{
				double width = rect.right - rect.left;
				double height = rect.bottom - rect.top;
				rect.left = x;
				rect.top = y;
				rect.right = x + width;
				rect.bottom = y + height;
				break;
			}
		}
	}


	void MapObject::setPivot(Serpents::MapObject::PivotPoint point)
	{
		this->pivot = point;
	}


	void MapObject::setSize(double x, double y)
	{
		switch( pivot )
		{
		case CenterPivot:
			{
				double width = rect.right - rect.left;
				double height = rect.bottom - rect.top;
				rect.left += (width-x)/2;
				rect.top += (height-y)/2;
				rect.right -= (width-x)/2;
				rect.bottom -= (height-y)/2;
				break;
			}
		case TopLeftCornerPivot:
			{
				rect.right = rect.left + x;
				rect.bottom = rect.top + y;
				break;
			}
		}
	}
}