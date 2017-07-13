//  TGKeyDefs.h
//---------------------------------------------------------------------------
//  [ro] - clase de lucru cu tastele. TGKey, TGKeyDefiner tin minte
//          toate tastele folosite. TGKeyController contine definitiile
//          pentru un singur jucator
//  [en] - classes built to easen work with keys. TGKey & TGKeyDefiner
//          keep record of all the usable keys. TGKeyController has the
//          keydefs for a certain player
//---------------------------------------------------------------------------
//	26.02.2007 - relucrat clase
//  15.11.2004  - added support for AddToName func.
//  created 14.11.2004
//---------------------------------------------------------------------------
#ifndef TGKeyDefsH
#define TGKeyDefsH
//---------------------------------------------------------------------------
#include <string.h>
//---------------------------------------------------------------------------
class TGKey;
class TGKeyDefiner;
class TGKeyController;

//---------------------------------------------------------------------------
//  [ro] - clasa cu datele necesare pt. o tasta
//  [en] - class containing all the data req. for a key
//---------------------------------------------------------------------------
#define s_size 7

class TGKey
{
private:
    char name[s_size];          //the associated name
public:
    bool enabled;               //is this key used?
    TGKey();
    void AddToName(int aNumber);
    char* GetName(){return name;}
    void SetName(char n[s_size]);
    void SetName(char c);
};

//---------------------------------------------------------------------------
//  [ro] - clasa ce contine valorile standard ale tastelor
//  [en] - class containing default values for the keys
//---------------------------------------------------------------------------
#define maxKeys 256                //array of keys is this long
class TGKeyDefiner
{
public:
    TGKey Key[256];
    TGKeyDefiner();
    int GetIndex(char n[6]);
};

//---------------------------------------------------------------------------
//  [ro] - clasa ce retine tastele pe care vrea sa le foloseasca jucatorul
//          si stadiul curent al acestora
//  [en] - class to keep track of the keybindings wished for by the player
//          and their current status
//---------------------------------------------------------------------------

class TGKeyController
{
    //  [en] - internal typedefs
    //  [en] - a key
    typedef struct
    {
        bool pressed;   //for where a long press is verified
        int  keycode;   //the associated keycode for a key
    }TGPlayerKey;
    //  [en] - all controll put together
    typedef struct
    {
        TGPlayerKey up;     //
        TGPlayerKey down;   //
        TGPlayerKey left;   //
        TGPlayerKey right;  //movement keys
        TGPlayerKey action; //special action key
        bool isRelative;    //is the control relative to the current position?
    }TGPlayerKeys;
    //  [en] - all game keys put together
private:
    TGKeyDefiner *KD;
    int noOfPlayers;
public:
    TGPlayerKeys *PlayerKey;
    TGPlayerKey *MenuKey;
    TGPlayerKey *PauseKey;

    TGKeyController(TGKeyDefiner *aKD, int aNoOfPlayers);
    ~TGKeyController();
    int GetNoOfPlayers(){return noOfPlayers;}
};

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
//Gusty
