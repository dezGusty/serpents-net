#pragma once

#include "GusUtils.h"
using namespace GustyUtils;

namespace Serpents
{
	class MapObject
	{
	private:
		DRECT rect;

		//
		//	setari comune tuturor constructorilor. (functie apelata din c-tor)
		//

		virtual void init(double,double,double,double);

	public:

		typedef enum 
		{
			TopLeftCornerPivot,
			CenterPivot,
			NumPivots
		}PivotPoint;

		typedef enum
		{
			ObjectShapeRectangular,
			ObjectShapeCircular,
			ObjectShapeSquare,
			NumShapes
		}ObjectShape;

		//
		//	Constructori.
		//

		MapObject();
		MapObject( DRECT initialRect );

		~MapObject(void);

		//
		//	seteaza pozitia dreptunghiului
		//

		virtual void setBounds( DRECT someRect ){ rect = someRect; }

		//
		//	getter pt. pozitia dreptunghiului asociat
		//

		virtual DRECT getBounds() { return rect; }

		//
		//	getter pentru locatie.
		//
		virtual DPOINT getLocation();

		//
		//	getter pentru dimensiune.
		//

		virtual DPOINT getSize();

		//
		//	getter pt. forma de baza.
		//

		virtual ObjectShape getShape(){ return shape; }

		//
		//	Obtine dimensiunea folosita pentru calculul distantei intre diferite obiecte de forma circulara.
		//

		double getSizeFromCenter();

		//
		//	misca pivotul
		//

		virtual void setPivot( PivotPoint point );

		//
		//	seteaza forma folosita pt. determinarea coliziunilor/suprapunerilor.
		//

		virtual void setShape( ObjectShape newShape ){ shape = newShape; }

		//
		//	redimensioneaza dreptunghiul locatiei, pastrand pivotul fix
		//

		virtual void setSize( DPOINT newSize ){ setSize(newSize.x, newSize.y); }

		//
		//	redimensioneaza dreptunghiul locatiei, pastrand pivotul fix
		//
		virtual void setSize( double x, double y );

		//
		//	reamplaseaza locatia, in functie de punctul pivot.
		//

		virtual void setLocation( DPOINT newLocation ){ setLocation(newLocation.x, newLocation.y); }

		//
		//	reamplaseaza locatia, in functie de punctul pivot.
		//
		virtual void setLocation( double x, double y );

		//
		//	verifica overlapping-ul
		//

		virtual bool intersectsWith( MapObject & rhs, bool checkBorderCollision = false );

	protected:
		PivotPoint pivot;	//	pivotul folosit pt. plasare/redimensionare
		ObjectShape shape;	//	forma simpla folosita pentru detectarea de coliziune
	};
}