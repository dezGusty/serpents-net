#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace FormSerpents1 {

	ref class VisualEngine;
	ref class Tester;

	/// <summary>
	/// Summary for PlayForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class PlayForm : public System::Windows::Forms::Form
	{
	public:
		PlayForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			postInit();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlayForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Timer^  gameActionTimer;

	private: System::Windows::Forms::Timer^  keyboardTimer;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->gameActionTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->keyboardTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// gameActionTimer
			// 
			this->gameActionTimer->Interval = 10;
			this->gameActionTimer->Tick += gcnew System::EventHandler(this, &PlayForm::gameActionTimer_Tick);
			// 
			// keyboardTimer
			// 
			this->keyboardTimer->Enabled = true;
			this->keyboardTimer->Tick += gcnew System::EventHandler(this, &PlayForm::keyboardTimer_Tick);
			// 
			// PlayForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 600);
			this->Name = L"PlayForm";
			this->Text = L"PlayForm";
			this->ResumeLayout(false);

		}
#pragma endregion

		//
		//	Regiune declaratii manuale
		//
#pragma region Declaratiile mele

		bool jocCreat;
		FormSerpents1::VisualEngine ^ engineJoc;
		
		bool testerCreat;
		FormSerpents1::Tester ^ testerJoc;

		void postInit();
		void actiuneActionTimer();
		void actiuneKeyboardTimer();
		void startJoc();
		void startTest();

		void startTracing( String ^ filename );

		System::Void PlayFormKeyDown( System::Object ^ , System::Windows::Forms::KeyEventArgs ^ e);

		System::Void PlayFormKeyUp( System::Object ^ , System::Windows::Forms::KeyEventArgs ^ e);

	public:
		virtual void OnPaint( PaintEventArgs^ e ) override sealed;
		virtual void OnPaintBackground( PaintEventArgs^ e ) override sealed;

#pragma endregion
	private: System::Void gameActionTimer_Tick(System::Object^  sender, System::EventArgs^  e) 
			 {
				 actiuneActionTimer();
			 }
	private: System::Void keyboardTimer_Tick(System::Object^  sender, System::EventArgs^  e) 
			 {
				actiuneKeyboardTimer();
			 }
};
}
