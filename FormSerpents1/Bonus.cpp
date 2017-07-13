#include "StdAfx.h"
#include "Bonus.h"

namespace Serpents
{
	Bonus::Bonus( long timeToLive )
	{
		this->timeToLive = timeToLive;
		this->setShape(MapObject::ObjectShapeCircular);
	}

	Bonus::~Bonus(void)
	{
	}


	//
	//	=================================== BonusController =================================================
	//


	BonusController::BonusController()
	{
		defaultTimeToLive = 30000;
		defaultSize.x = defaultSize.y = 15;
	}


	Bonus* BonusController::getItemAt( int index )
	{
		return this->bonuses.getElementAt( index );
	}


	int BonusController::getNumberOfItems()
	{
		return this->bonuses.getLength();
	}


	void BonusController::onTimeGoesBy( double timeUnits )
	{
		for( int i=0; i<getNumberOfItems(); i++ )
		{
			bonuses[i]->timeToLive -= (long)timeUnits;
			if( bonuses[i]->timeToLive < 0 )
			{
				//System::Diagnostics::Trace::WriteLine("XXXXXX unspawn3=" + getNumberOfItems() );

				bonuses.removeAt(i);
				i--;
				//System::Diagnostics::Trace::WriteLine("XXXXXX unspawn4=" + getNumberOfItems() );

			}
		}
	}


	void BonusController::spawnNewBonus( DPOINT point )
	{
		//System::Diagnostics::Trace::WriteLine("XXXXXX spawn1=" + getNumberOfItems() );
		Bonus * myBonus = new Bonus( defaultTimeToLive );
		myBonus->setPivot( MapObject::CenterPivot );
		myBonus->setSize( defaultSize );
		myBonus->setLocation( point );
		bonuses.add( myBonus );
		//System::Diagnostics::Trace::WriteLine("XXXXXX spawn2=" + getNumberOfItems() );
	}
}