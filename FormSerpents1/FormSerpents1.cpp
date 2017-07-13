// FormSerpents1.cpp : main project file.

#include "stdafx.h"
#include "PlayForm.h"

using namespace FormSerpents1;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	//Application::Run(gcnew MainForm());
	Application::Run(gcnew PlayForm());
	return 0;
}
