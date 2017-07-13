#pragma once

#include "MapObject.h"
#include "GusUtils.h"

using namespace GustyUtils;

namespace Serpents
{
	//
	//	Clasa de control a unui obiect tip bonus.
	//

	class Bonus :
		public MapObject
	{
	public:
		Bonus( long time = 30000 );
		~Bonus();
		virtual int getValue(){ return value; }
		virtual long getTimeToLive(){ return timeToLive; }
		virtual double getHealth(){ return health; }

		virtual void setTimeToLive( long time ){ this->timeToLive = time; }
	protected:
		int value;
		long timeToLive;
		double health;

		friend class BonusController;
	};

	//
	//	Clasa interfata pentru accesul mai lejer la bonusuri.
	//

	class BonusController
	{
	protected:
		GusArray<Bonus> bonuses;
		long defaultTimeToLive;
		DPOINT defaultSize;
		int maximumAllowedBonuses;

	public:
		BonusController();
		virtual Bonus * getItemAt( int index );
		virtual DPOINT getDefaultSize(){ return defaultSize; }
		virtual long getDefaultTimeToLive(){ return defaultTimeToLive; }
		virtual int getMaximumAllowedBonuses(){ return maximumAllowedBonuses; }
		virtual int getNumberOfItems();
		int getLength(){ return getNumberOfItems(); }
		virtual void onTimeGoesBy( double timeUnits );//	most likely milliseconds
		virtual void setDefaultSize( DPOINT sz ){ defaultSize = sz; }
		virtual void setDefaultTimeToLive( long rhs ){ defaultTimeToLive = rhs; }
		virtual void setMaximumAllowerBonuses( int rhs ){ maximumAllowedBonuses = rhs; }
		virtual void spawnNewBonus( DPOINT location );
	};

}