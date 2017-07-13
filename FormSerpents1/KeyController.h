#pragma once

#include "GusUtils.h"
using namespace GustyUtils;

namespace Serpents
{

#define MAX_KEYNAME_SIZE 7	//	Numarul maxim de caractere permis pentru asocierea alfanumerica a tastelor

	//
	//	Clasa ce contine informatiile necesare pentru o tasta.
	//

	class Key
	{
	protected:
		char * name;
		bool enabled;               //is this key used?

	public:
		//	Constructor.
		Key();
		//	Destructor.
		~Key();

		//
		//	Fc. utilitara; adauga un numar la finalul textului (folosita pt. generarea tastelor F1..F12
		//
		void addToName( const int aNumber );

		//
		//	Activeaza/dezactiveza tasta.
		//
		void enable( bool value = true ){ enabled = value;}

		//
		//	Getter pentru numele asociat tastei
		//
		char* getName(){ return name; }

		//
		//	Getter pt. starea activa/inactiva
		//
		bool isEnabled(){ return enabled;}

		//
		//	Setter pentru numele asociat tastei
		//
		void setName( char *someName );

		//
		//	Setter pentru numele asociat tastei
		//
		void setName( const char c );

		//
		//	Setter pentru numele asociat tastei
		//
		//void setName( const char[/*MAX_KEYNAME_SIZE*/] );
	};


#define maxKeys 256	//	Numarul maxim posibil de taste. Codurile posibile sunt intre 0 si maxKeys-1

	//
	//	Clasa ce contine definitiile de taste. Va fi folosita pur si simplu pentru asocierile de nume cu codurile numerice ale tastelor.
	//

	class KeyDefiner
	{
	public:
		Key key[256];
		KeyDefiner();
		int getIndexOf(const char * name);
	};


	//
	//	Clasa ce retine tastele pe care le va folosi jucatorul, precum si starea curenta a acestora.
	//

	class KeyController
	{
	public:
		typedef struct
		{
			char * name;
			int keyBinding;
			int alternateKeyBinding;
			bool pressed;
		}KeyBinding;

		//	Constructor.
		KeyController( KeyDefiner &kd, int noOfPlayers = 1, bool takeOwnershipOfDefiner = true );
		//	Destructor.
		~KeyController();

		//
		//	Getter pt. numarul de jucatori controlati de keycontroller.
		//
		int getNumberOfPlayers(){ return noOfPlayers; }

	protected:
		KeyDefiner * keyDefiner;
		//GusArray<KeyBinding> bindings;
		int noOfPlayers;
		bool deleteKDOnEnd;
	};
}