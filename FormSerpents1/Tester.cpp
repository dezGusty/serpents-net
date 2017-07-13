#include "StdAfx.h"
#include "Tester.h"

#include "GusUtils.h"
#include "BodyPart.h"
#include "Serpent.h"

using namespace Serpents;
using namespace GustyUtils;

namespace FormSerpents1
{
	Tester::Tester(void)
	{
	}

	void Tester::onKeyDown( int keyCode )
	{
		System::Diagnostics::Trace::Flush();
		if( form )
		{
			System::Diagnostics::Trace::Flush();

			Serpents::Serpent * mySerpent = new Serpents::Serpent();
			mySerpent->addParts(5);
			BodyPart * getter = mySerpent->getBodyPart(0);
			getter = mySerpent->getBodyPart(0);

			System::Windows::Forms::Label ^debugLabel = gcnew Label();

			mySerpent->spawn(10,10);
			getter = mySerpent->getBodyPart(0);
			debugLabel->Text = getter->getLocation().x.ToString();

			mySerpent->move(1);
			debugLabel->Text = getter->getLocation().x.ToString();
			getter = mySerpent->getBodyPart(0);

			mySerpent->move(1);
			debugLabel->Text = getter->getLocation().x.ToString();
			getter = mySerpent->getBodyPart(0);

			debugLabel->Size = System::Drawing::Size(40, 40);
			debugLabel->Location = System::Drawing::Point(0, 0);
			debugLabel->BackColor = System::Drawing::Color::FromArgb( 155, 255, 255 );
			this->form->/*getDrawingPanel()->*/Controls->Add(debugLabel);

	
		}
	}
}