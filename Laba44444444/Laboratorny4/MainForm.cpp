#include "MainForm.h"
#include "AddUserForm.h"
#include "DataForm.h"
#include <string>


int Count = 0;
std::vector<std::string> names;
std::vector<int> SellofElectric;
std::vector<int> SellofWater;



int callback(void* NotUsed, int argc, char** argv, char** azColName) {

	names.push_back(argv[1]);
	SellofElectric.push_back(atoi(argv[2]));
	SellofWater.push_back(atoi(argv[3]));
	Count++;
	return 0;
}




System::Void Laboratorny4::MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ fileName;
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
		fileName = openFileDialog1->FileName;
	}
	
	

	String^ informationFromFile;
	try {
		StreamReader^ file = File::OpenText(fileName);


		while ((informationFromFile = file->ReadLine()) != nullptr) {
			array<System::String^>^ StringArray = informationFromFile->Split('\t');

			listHousehold->Add(gcnew Household(StringArray[0], Convert::ToInt32(Convert::ToString(StringArray[1])), Convert::ToInt32(Convert::ToString(StringArray[2]))));
		}
		file->Close();
		
		int comprasions = 0;
		int permutations = 0;
		int now_permutations = 0;
		int size = listHousehold->Count;
		do {
			now_permutations = 0;
			for (int i = 0; i < size - 1; i++) {

				if (listHousehold[i]->Name[0] > listHousehold[i + 1]->Name[0]) {
					Household^ first_before = listHousehold[i];
					listHousehold[i] = listHousehold[i + 1];
					listHousehold[i + 1] = first_before;
					now_permutations++;
				}
				comprasions++;
			}
			permutations += now_permutations;

			size--;
		} while (now_permutations != 0);
	
		
		dataGridView1->DataSource = nullptr;
		dataGridView1->DataSource = listHousehold;
		
	}
	catch (Exception^ e) {
		MessageBox::Show("Ошибка", "Не удалось прочитать файл");
		
	}
	
	
}

System::Void Laboratorny4::MainForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	saveFileDialog1->Filter = "Text Files|*.txt|All Files|*.*";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		StreamWriter^ sw = gcnew StreamWriter(saveFileDialog1->FileName);
		for (int i = 0; i < listHousehold->Count; i++) {
			sw->WriteLine(listHousehold[i]->Name + "\t" + Convert::ToInt32(listHousehold[i]->sellofElectric) + "\t" + Convert::ToInt32(listHousehold[i]->sellOfWater));
		}
		
		sw->Close();
	}

}

System::Void Laboratorny4::MainForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	AddUserForm^ form = gcnew AddUserForm(this, listHousehold, 0);
	
	form->ShowDialog();
	int comprasions = 0;
	int permutations = 0;
	int now_permutations = 0;
	int size = listHousehold->Count;
	do {
		now_permutations = 0;
		for (int i = 0; i < size - 1; i++) {

			if (listHousehold[i]->Name[0] > listHousehold[i + 1]->Name[0]) {
				Household^ first_before = listHousehold[i];
				listHousehold[i] = listHousehold[i + 1];
				listHousehold[i + 1] = first_before;
				now_permutations++;
			}
			comprasions++;
		}
		permutations += now_permutations;

		size--;
	} while (now_permutations != 0);
	dataGridView1->DataSource = nullptr;
	dataGridView1->DataSource = listHousehold;

}

System::Void Laboratorny4::MainForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	AddUserForm^ form = gcnew AddUserForm(this, listHousehold);
	
	form->ShowDialog();
	int comprasions = 0;
	int permutations = 0;
	int now_permutations = 0;
	int size = listHousehold->Count;
	do {
		now_permutations = 0;
		for (int i = 0; i < size - 1; i++) {

			if (listHousehold[i]->Name[0] > listHousehold[i + 1]->Name[0]) {
				Household^ first_before = listHousehold[i];
				listHousehold[i] = listHousehold[i + 1];
				listHousehold[i + 1] = first_before;
				now_permutations++;
			}
			comprasions++;
		}
		permutations += now_permutations;

		size--;
	} while (now_permutations != 0);
	dataGridView1->DataSource = nullptr;
	dataGridView1->DataSource = listHousehold;
}

System::Void Laboratorny4::MainForm::button5_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Крутая прога", "Программа была переделана для того чтобы я её сдал.");
}
using namespace System::Runtime::InteropServices;
System::Void Laboratorny4::MainForm::button6_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::cout << "Clicked" << std::endl;
	sqlite3* DB;
	int exit = 0;

	/*String^ fileName;
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
		fileName = openFileDialog1->FileName;
	}*/
	//std::string unmanaged = msclr::interop::marshal_as<std::string>(fileName);

	//const char*  f = unmanaged.c_str();
	//const char* f = (const char*)(Marshal::StringToHGlobalAnsi(fileName)).ToPointer();
	exit = sqlite3_open("db.db", &DB);

	if (exit) {
		MessageBox::Show("Error.");
	}
	std::string data("CALLBACK FUNCTION");

	std::string sql("SELECT * FROM Users;");

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);



	for (int i = 0; i < Count; i++) {
		listHousehold->Add(gcnew Household(gcnew String(names[i].c_str()), SellofElectric[i], SellofWater[i]));
		std::cout << names[i] << SellofElectric[i] << SellofWater[i] << std::endl;
	}
	sqlite3_close(DB);
	int comprasions = 0;
	int permutations = 0;
	int now_permutations = 0;
	int size = listHousehold->Count;
	do {
		now_permutations = 0;
		for (int i = 0; i < size - 1; i++) {

			if (listHousehold[i]->Name[0] > listHousehold[i + 1]->Name[0]) {
				Household^ first_before = listHousehold[i];
				listHousehold[i] = listHousehold[i + 1];
				listHousehold[i + 1] = first_before;
				now_permutations++;
			}
			comprasions++;
		}
		permutations += now_permutations;

		size--;
	} while (now_permutations != 0);


	dataGridView1->DataSource = nullptr;
	dataGridView1->DataSource = listHousehold;

	Count = 0;
	names.clear();
	SellofElectric.clear();
	SellofWater.clear();
}


using System::Runtime::InteropServices::Marshal;

static std::string toStandardString(System::String^ string)
{
	System::IntPtr pointer = Marshal::StringToHGlobalAnsi(string);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string returnString(charPointer, string->Length);
	Marshal::FreeHGlobal(pointer);

	return returnString;
}
System::Void Laboratorny4::MainForm::button7_Click(System::Object^ sender, System::EventArgs^ e)
{
	sqlite3* DB;
	int exit = 0;
	char* err_msg = 0;
	char* messaggeError;

	exit = sqlite3_open("db.db", &DB);
	if (exit) {
		MessageBox::Show("Error.");
	}
	char* sql = "DELETE FROM Users";
	exit = sqlite3_exec(DB, sql, 0, 0, &err_msg);
	for (int i = 0; i < listHousehold->Count; i++) {
		std::string sql("INSERT INTO Users VALUES(" + std::to_string(i) + ", '" + toStandardString(listHousehold[i]->Name) + "', " + std::to_string(listHousehold[i]->sellofElectric) + ", " + std::to_string(listHousehold[i]->sellOfWater) + "); ");

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error Insert" << std::endl;
			std::cerr << messaggeError << std::endl;
			sqlite3_free(messaggeError);
		}
		else {
			std::cout << "Records created Successfully!" << std::endl;
		}

	}
	sqlite3_close(DB);
}