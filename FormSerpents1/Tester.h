#pragma once

#include "PlayForm.h"
using namespace FormSerpents1;

namespace FormSerpents1
{
	ref class Tester
	{
	public:
		Tester(void);
		//
		//	Reactioneaza la apasarea unei taste. (Mapping catre SerpentsEngine)
		//

		virtual void onKeyDown( int keyCode );
		//
		//	Getter pentru form-ul legat de engine.
		//

		virtual void setFormToUse( FormSerpents1::PlayForm ^formToUse ){ this->form = formToUse; }

	protected:
		PlayForm ^form;

	};
}