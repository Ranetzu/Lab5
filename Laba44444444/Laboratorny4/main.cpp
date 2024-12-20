#include "Operator.h"
#include "MainForm.h"
#include <sqlite3.h>
using namespace System;
using namespace System::Windows::Forms;



[STAThreadAttribute]
int main(cli::array<System::String^>^ args) {
	//sqlite3* DB;
	//sqlite3_open("Database1.accdb", &DB);
	Application::SetCompatibleTextRenderingDefault(false);
	/*if (exit) {
		std::cout << "DB is not open." <<sqlite3_errmsg(DB) << std::endl;
	}
	else {
		std::cout << "DB is open." << std::endl;
	}*/
	Application::EnableVisualStyles();
	Laboratorny4::MainForm form;
	Application::Run(% form);
}