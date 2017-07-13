#include "StdAfx.h"
#include "Map.h"

namespace Serpents
{
	Map::Map( double width, double height )
	{
		this->bounds.left = 0;
		this->bounds.top = 0;
		this->bounds.right = width;
		this->bounds.bottom = height;
	}


	Map::Map( double left, double top, double right, double bottom )
	{
		this->bounds.left = left;
		this->bounds.top = top;
		this->bounds.right = right;
		this->bounds.bottom = bottom;
	}


	Map::~Map(void)
	{
	}


	void Map::addObjectToCollisionMap( MapObject & obj )
	{
		int x1 = (int)(obj.getBounds().left / cellSize.x);
		int x2 = (int)(obj.getBounds().right / cellSize.x);
		int y1 = (int)(obj.getBounds().top / cellSize.y);
		int y2 = (int)(obj.getBounds().bottom / cellSize.y);
	}



	DPOINT Map::getFreeSpotForSize(GustyUtils::SPoint<double> objSize)
	{
		DPOINT ret = {0,0};
		return ret;
	}



	DFLOAT Map::getHeight()
	{
		return bounds.bottom - bounds.top;
	}


	DFLOAT Map::getWidth()
	{
		return bounds.right - bounds.left;
	}


	//
	//	Setter pt. dimensiunile unui cell.
	//

	void Map::setNumCells( IPOINT nCells )
	{
		this->numCells = nCells;
		this->cellSize.x = getWidth() / nCells.x;
		this->cellSize.y = getHeight() / nCells.y;
	}

}