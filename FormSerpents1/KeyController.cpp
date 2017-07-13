#include "StdAfx.h"
#include "KeyController.h"
#include "GusUtils.h"

#include <string.h>

namespace Serpents
{
	//
	//	Clasa Key
	//

	Key::Key()
	{
		name=NULL;
		this->enable( false );
	}


	Key::~Key()
	{
		SAFE_DELETE(name);
	}


	void Key::addToName( const int aNumber )
	{
		if( name == NULL )
		{
			return;
		}

		int currentSize = strlen(name);

		//	Calc. cifre

		int digits = 1;
		int tempNumber = aNumber;
		while( tempNumber > 0 )
		{
			tempNumber/=10;
			if( tempNumber > 0 ) digits++;
		}

		//	Asigura dimensiunea maxima

		if( currentSize + digits <= MAX_KEYNAME_SIZE )
		{
			tempNumber = (aNumber >=0)? aNumber : -aNumber;
			int* sir = new int[digits];
			int k=0;
			while(tempNumber>0)
			{
				sir[k++] = tempNumber%10;
				tempNumber/=10;
			}
			char * aux = new char[currentSize + digits];

			for( int i=0; i<currentSize; i++ )
			{
				aux[i] = name[i];
			}
			for(int i=0;i<k;i++)
			{
				aux[i+currentSize] = (char)(sir[k-1-i] + '0');
			}
			delete sir;
		}
	}


	void Key::setName( char * newName )
	{
		SAFE_DELETE( name );
		name = newName;
		enable();
	}


	void Key::setName( const char c )
	{
		SAFE_DELETE(name);
		name = new char[2];
		name[0] = c;
		name[1] = '\0';
		enable();
	}


	//void Key::setName(const char newName[])
	//{
	//	SAFE_DELETE(name);
	//	name = new char[ strlen(newName) ];
	//	strcpy_s(name, newName);
	//}


	//
	//	Clasa KeyDefiner
	//


	KeyDefiner::KeyDefiner()
	{
		for(int i=48;i<=57;i++)
		{
			key[i].setName((char)i);
		}
		for(int i=65;i<=90;i++)
		{
			key[i].setName((char)i);
		}
		for(int i=112;i<=123;i++)
		{
			key[i].setName("F");
			key[i].addToName(i-111);
		}
		for(int i=96;i<=105;i++)
		{
			key[i].setName("Num");
			key[i].addToName(i-96);
		}
		key[8].setName("Bkspc");

		key[13].setName("Enter");

		key[16].setName("Shift");

		key[17].setName("Ctrl");

		key[18].setName("Alt");

		key[19].setName("Break");

		key[20].setName("CapsLk");

		key[27].setName("Escape");

		key[32].setName("Space");

		key[33].setName("PageUp");

		key[34].setName("PageDn");

		key[35].setName("End");

		key[36].setName("Home");

		key[37].setName("Left");

		key[38].setName("Up");

		key[39].setName("Right");

		key[40].setName("Down");

		key[45].setName("Insert");

		key[46].setName("Delete");

		key[91].setName("Win");

		key[93].setName("View");

		key[106].setName("Num*");

		key[107].setName("Num+");

		key[109].setName("Num-");

		key[110].setName("Num.");

		key[111].setName("Num/");

		key[145].setName("ScrLk");

		key[186].setName(";");

		key[187].setName("=");

		key[188].setName(",");

		key[189].setName("-");

		key[190].setName(".");

		key[191].setName("/");

		key[192].setName("~");

		key[219].setName("[");

		key[220].setName("\\");

		key[221].setName("]");

		key[222].setName("'");
	}


	int KeyDefiner::getIndexOf(const char *name)
	{
		int ret=-1;
		if( name == NULL )
		{
			return ret;
		}
		for(int i=0;i<maxKeys;i++)
		{
			if(key[i].isEnabled())
			{
				if(strcmp(key[i].getName(), name)==0)
				{
					ret=i;
					break;
				}
			}
		}
		return ret;
	}


	//
	//	Clasa KeyController
	//

	KeyController::KeyController( KeyDefiner &kd, int noOfPlayers , bool takeOwnershipOfDefiner )
	{
		keyDefiner = &kd;
		deleteKDOnEnd = takeOwnershipOfDefiner;
	}


	KeyController::~KeyController(void)
	{
		if( deleteKDOnEnd )
		{
			delete keyDefiner;
		}
	}
}