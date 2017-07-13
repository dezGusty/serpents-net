//  TGKeyDefs.cpp
//---------------------------------------------------------------------------
//	26.02.2007 - relucrat clase, pt. MSVC++ 2005
//  15.11.2004  - added support for AddToName func.
//  created 14.11.2004
//---------------------------------------------------------------------------
#include <stdafx.h>
#include <stdio.h>
#pragma hdrstop

#include "TGKeyDefs.h"
//---------------------------------------------------------------------------
//  [ro] - clasa cu datele necesare pt. o tasta
//  [en] - class containing all the data req. for a key
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  constructor
//---------------------------------------------------------------------------
TGKey::TGKey()
{
    enabled = false;
    for(int i=0; i<s_size ;i++)
        name[i] = '\0';
}
//---------------------------------------------------------------------------
//  [en] - set the associated name
//---------------------------------------------------------------------------
void TGKey::SetName(char n[s_size])
{
    strcpy_s(name,n);
    enabled=true;
}
//---------------------------------------------------------------------------
void TGKey::SetName(char c)
{
    name[0] = c;
    enabled = true;
    for(int i=1; i<s_size ;i++)
        name[i] = '\0';
}
//---------------------------------------------------------------------------
//  [ro] - adauga un nr in string, util pt F11, Num4, etc
//  [en] - add an integer to the name string, useful for F11, Num4, etc.
//---------------------------------------------------------------------------
void TGKey::AddToName(int aNumber)
{
    int currentPos = strlen(name);
    //calc the digits
    int digits = 1;
    int tempNumber = aNumber;
    while(tempNumber>0)
    {
        tempNumber/=10;
        if(tempNumber>0) digits++;
    }
    //if new length exceeds maximum allowed cancel append
    if(currentPos+digits<=s_size)
    {
        tempNumber=aNumber;
        int* sir = new int[digits];
        int k=0;
        while(tempNumber>0)
        {
            sir[k++] = tempNumber%10;
            tempNumber/=10;
        }
        for(int i=0;i<k;i++)
            name[i+currentPos] = (char)(sir[k-1-i] + '0');
        delete sir;
    }
}
//---------------------------------------------------------------------------
//  [ro] - clasa ce contine valorile standard ale tastelor
//  [en] - class containing default values for the keys
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  constructor
//---------------------------------------------------------------------------
TGKeyDefiner::TGKeyDefiner()
{
    for(int i=48;i<=57;i++)
    {
        Key[i].SetName((char)i);
    }
    for(int i=65;i<=90;i++)
    {
        Key[i].SetName((char)i);
    }
    for(int i=112;i<=123;i++)
    {
        Key[i].SetName("F");
        Key[i].AddToName(i-111);
    }
    for(int i=96;i<=105;i++)
    {
        Key[i].SetName("Num");
        Key[i].AddToName(i-96);
    }
    Key[8].SetName("Bkspc");

    Key[13].SetName("Enter");

    Key[16].SetName("Shift");

    Key[17].SetName("Ctrl");

    Key[18].SetName("Alt");

    Key[19].SetName("Break");

    Key[20].SetName("CapsLk");

    Key[27].SetName("Escape");

    Key[32].SetName("Space");

    Key[33].SetName("PageUp");

    Key[34].SetName("PageDn");

    Key[35].SetName("End");

    Key[36].SetName("Home");

    Key[37].SetName("Left");

    Key[38].SetName("Up");

    Key[39].SetName("Right");

    Key[40].SetName("Down");

    Key[45].SetName("Insert");

    Key[46].SetName("Delete");

    Key[91].SetName("Win");

    Key[93].SetName("View");

    Key[106].SetName("Num*");

    Key[107].SetName("Num+");

    Key[109].SetName("Num-");

    Key[110].SetName("Num.");

    Key[111].SetName("Num/");

    Key[145].SetName("ScrLk");

    Key[186].SetName(";");

    Key[187].SetName("=");

    Key[188].SetName(",");

    Key[189].SetName("-");

    Key[190].SetName(".");

    Key[191].SetName("/");

    Key[192].SetName("~");

    Key[219].SetName("[");

    Key[220].SetName("\\");

    Key[221].SetName("]");

    Key[222].SetName("'");
}
//---------------------------------------------------------------------------
//  [en] - get the index of a key with a certain name
//---------------------------------------------------------------------------
int TGKeyDefiner::GetIndex(char n[6])
{
    int ret=-1;
    for(int i=0;i<maxKeys;i++)
        if(Key[i].enabled)
            if(strcmp(Key[i].GetName(), n)==0)
            {
                ret=i;
                break;
            }
    return ret;
}
//---------------------------------------------------------------------------
//  [ro] - clasa ce retine tastele pe care vrea sa le foloseasca jucatorul
//          si stadiul curent al acestora
//  [en] - class to keep track of the keybindings wished for by the player
//          and their current status
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  constructor
//---------------------------------------------------------------------------
TGKeyController::TGKeyController(TGKeyDefiner *aKD, int aNoOfPlayers)
{
    KD=aKD;
    noOfPlayers=aNoOfPlayers;
    PlayerKey = new TGPlayerKeys[noOfPlayers];
    MenuKey = new TGPlayerKey();
    PauseKey = new TGPlayerKey();
}
//---------------------------------------------------------------------------
//  destructor
//---------------------------------------------------------------------------
TGKeyController::~TGKeyController()
{
    delete PlayerKey;
    delete MenuKey;
    delete PauseKey;
}
//---------------------------------------------------------------------------
//Gusty
