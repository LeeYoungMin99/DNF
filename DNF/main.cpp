// main.cpp

#include "stdafx.h"
#include "MainGame.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

void jsonWrite()
{
	ofstream json_file;
	json_file.open("d:\\JSON_DATA.json");

	Json::Value Computer;
	Computer["CPU"] = "I7";
	Computer["RAM"] = "16G";

	Json::Value Language;
	Language["C++"] = "Visual Studio";
	Language["Python"] = "IDLE";

	Computer["Program"] = Language;
	Computer["HDD"] = "2TB";

	Json::Value Cable;
	Cable.append("Power");
	Cable.append("Printer");
	Cable.append("Mouse");

	Computer["Computer"]["Cable"] = Cable;

	Json::Value number;
	number["Int"] = 123;
	number["Double"] = 456.012;
	number["Bool"] = true;

	Computer["Computer"]["Number"] = number;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "		"; // Tab
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	writer->write(Computer, &cout);
	writer->write(Computer, &json_file);
	cout << endl;	// add if and flush

	json_file.close();
}

void jsonRead() {
	ifstream json_dir("d:\\JSON_DATA.json");
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value; JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);
	if (ok == true) {
		cout << "CPU: " << value["CPU"] << endl;
		cout << "Program Python: " << value["Program"]["Python"] << endl;
		cout << "Computer Cable: " << value["Computer"]["Cable"] << endl;
		cout << "Computer Cable[0]: " << value["Computer"]["Cable"][0] << endl;
		cout << endl;
		cout << "Computer Number Int(as int): " << value["Computer"]["Number"].get("Int", -1).asInt() << endl; // "Int" 값이 없으면 -1 반환. 
		cout << "Computer Number Int(as int): " << value["Computer"]["Number"]["Int"].asInt() << endl; // "Int" 값이 없으면 0 반환. 
		cout << "Computer Number Double(as double): " << value["Computer"]["Number"].get("Double", -1).asDouble() << endl; // "Double" 값이 없으면 -1 반환. 
		cout << "Computer Number Double(as string): " << value["Computer"]["Number"].get("Double", "Empty").asString() << endl; // "Double" 값이 없으면 Empty 반환. 
		cout << "Computer Number Bool(as bool): " << value["Computer"]["Number"].get("Bool", false).asBool() << endl; // "Bool" 값이 없으면 false 반환. 
		cout << endl; cout << "Root size: " << value.size() << endl;
		cout << "Program size: " << value["Program"].size() << endl;
		cout << "Computer Cable size: " << value["Computer"]["Cable"].size() << endl;
		cout << endl; int size = value["Computer"]["Cable"].size(); // size() 값을 for 문에서 그대로 비교하면 warning C4018가 발생 한다.
		for (int i = 0; i < size; i++)
			cout << "Computer Cable: " << value["Computer"]["Cable"][i] << endl;
		cout << endl;
		for (auto i : value["Computer"]["Cable"])
			cout << "Computer Cable: " << i << endl;
	}
	else
	{
		cout << "Parse failed." << endl;
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	MainGame game;

	if (false == game.Init(hInstance))
	{
		return 0;
	}

	INT32 res = game.Run();

	return res;
}
