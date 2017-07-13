#pragma once

#include "MapObject.h"
#include "GusUtils.h"
using namespace GustyUtils;

namespace Serpents
{

	typedef struct
	{
		GusArray<MapObject> elementArray;
	}MapCell;

	//
	//	Clasa de reprezentare a suprafetei de joc, incluzand limitele fizice, obstacolele, etc. De asemenea va fi folosita pt. a usura calculele de 
	//	coliziune a obiectelor de pe harta.
	//

	class Map
	{
	public:
		//
		//	Constructor de specificare a marimii. Coltul stanga-sus al dreptunghiului folosit va fi (0,0)
		//

		Map( DFLOAT width, DFLOAT height );

		//
		//	Constructor de specificare directa a coordonatelor.
		//

		Map( DFLOAT left, DFLOAT top, DFLOAT right, DFLOAT bottom );

		//
		//	Destructor.
		//

		~Map();

		//
		//	adauga un obiect de harta la testarea de coliziune.
		//

		virtual void addObjectToCollisionMap( MapObject & obj );

		//
		//	Getter pt. limitele fizice ale hartii de joc.
		//

		virtual SRectangle<DFLOAT> getBounds(){ return bounds; }

		//
		//	Getter pt. dimensiunile unui cell.
		//

		virtual DPOINT getCellSize(){ return cellSize; }

		//
		//	Calculeaza un loc liber pe care se poate amplasa un obiect de dimensiune objSize
		//

		virtual DPOINT getFreeSpotForSize( DPOINT objSize );

		//
		//	Getter pt. inaltimea suprafetei folosite.
		//

		virtual DFLOAT getHeight();

		//
		//	Getter pt. numarul de celule (segmente) ale hartii.
		//

		virtual IPOINT getNumCells(){ return numCells; }

		//
		//	Getter pt. lungimea suprafetei folosite.
		//

		virtual DFLOAT getWidth();

		//
		//	Setter pt. bounds.
		//

		virtual void setBounds( SRectangle<DFLOAT> rect ){ bounds = rect; }

		//
		//	Setter pt. dimensiunile unui cell.
		//

		virtual void setNumCells( IPOINT nCells );

	protected:

		//	Dreptunghi ce delimiteaza suprafata de joc.
		SRectangle<DFLOAT> bounds;

		DPOINT cellSize;
		IPOINT numCells;

		MapCell ** cellMatrix;

	};
}