#pragma once

#include "Program.h"

namespace Gabinet {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;
	/// <summary>
	/// Podsumowanie informacji o Logowanie
	/// </summary>
	public ref class Logowanie : public System::Windows::Forms::Form
	{
	public:
		Logowanie(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~Logowanie()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnZaloguj;
	private: System::Windows::Forms::Button^  btnAnuluj;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  txtUzytkownik;
	private: System::Windows::Forms::TextBox^  txtHaslo;
	protected:


	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Wymagana metoda wsparcia projektanta - nie nale¿y modyfikowaæ
		/// zawartoœæ tej metody z edytorem kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnZaloguj = (gcnew System::Windows::Forms::Button());
			this->btnAnuluj = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtUzytkownik = (gcnew System::Windows::Forms::TextBox());
			this->txtHaslo = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// btnZaloguj
			// 
			this->btnZaloguj->Location = System::Drawing::Point(160, 208);
			this->btnZaloguj->Name = L"btnZaloguj";
			this->btnZaloguj->Size = System::Drawing::Size(75, 23);
			this->btnZaloguj->TabIndex = 0;
			this->btnZaloguj->Text = L"Zaloguj";
			this->btnZaloguj->UseVisualStyleBackColor = true;
			this->btnZaloguj->Click += gcnew System::EventHandler(this, &Logowanie::btnZaloguj_Click);
			// 
			// btnAnuluj
			// 
			this->btnAnuluj->Location = System::Drawing::Point(51, 208);
			this->btnAnuluj->Name = L"btnAnuluj";
			this->btnAnuluj->Size = System::Drawing::Size(75, 23);
			this->btnAnuluj->TabIndex = 1;
			this->btnAnuluj->Text = L"Anuluj";
			this->btnAnuluj->UseVisualStyleBackColor = true;
			this->btnAnuluj->Click += gcnew System::EventHandler(this, &Logowanie::btnAnuluj_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(33, 68);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"u¿ytkownik:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(33, 119);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(37, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"has³o:";
			// 
			// txtUzytkownik
			// 
			this->txtUzytkownik->Location = System::Drawing::Point(135, 65);
			this->txtUzytkownik->Name = L"txtUzytkownik";
			this->txtUzytkownik->Size = System::Drawing::Size(100, 20);
			this->txtUzytkownik->TabIndex = 4;
			// 
			// txtHaslo
			// 
			this->txtHaslo->Location = System::Drawing::Point(135, 116);
			this->txtHaslo->Name = L"txtHaslo";
			this->txtHaslo->PasswordChar = '*';
			this->txtHaslo->Size = System::Drawing::Size(100, 20);
			this->txtHaslo->TabIndex = 5;
			// 
			// Logowanie
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->txtHaslo);
			this->Controls->Add(this->txtUzytkownik);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnAnuluj);
			this->Controls->Add(this->btnZaloguj);
			this->Name = L"Logowanie";
			this->Text = L"Logowanie";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnAnuluj_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}

private: System::Void btnZaloguj_Click(System::Object^  sender, System::EventArgs^  e) {
	
	String^ konfiguracja = L"datasource=localhost;port=3306;username=root;password=1234;database=Gabinet";
	MySqlConnection^ laczBaze = gcnew MySqlConnection(konfiguracja);
	MySqlCommand^ zapytanie = gcnew MySqlCommand("select * from uzytkownik where uzytkownik_nazwa = '"+txtUzytkownik->Text+"' and haslo = PASSWORD('"+txtHaslo->Text+"');", laczBaze);
	MySqlDataReader^ odczytanie;
	try {
		laczBaze->Open();
		odczytanie = zapytanie->ExecuteReader();

		if (odczytanie->Read()) {
			int id_uzytkownik = odczytanie->GetInt32(0);
			this->Hide();
			Program^ program = gcnew Program(id_uzytkownik);
			program->ShowDialog();
			this->Close();
		}
		else {
			MessageBox::Show("Bledna nazwa uzytkownika lub niepoprawne haslo");
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}

	laczBaze->Close();

}

};
}
