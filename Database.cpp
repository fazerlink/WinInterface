#include "Database.h"
sqlite3* db = nullptr;
sqlite3_stmt* st;
std::string outputInfo;
HWND hWnd;
int callback(void*, int, char**, char**);
int CreateDatabase(HWND hWnd)
{
	int rb = sqlite3_open16(L"Info.db", &db);
	if (rb != SQLITE_OK) {

		MessageBox(hWnd, "Error. Cannot open database ",
			"", MB_OK | MB_ICONWARNING);
		sqlite3_close(db);
		return 0;

	}
	return 0;
}
int inputInfo(char* result, char* temperature, char* pressure, char* minutes, int counter, HWND hWnd)
{

	char* err;
	char KEK;
	int rb;
	if (counter == 1)
	{
		CreateDatabase(hWnd);
		const char* open = "CREATE TABLE IF NOT EXISTS tests(lineID INTEGER PRIMAL KEY NOT NULL, result REAL, temperature REAL, pressure REAL, minutes REAL);";

		rb = sqlite3_exec(db, open, 0, 0, &err);

		if (rb != SQLITE_OK) {

			MessageBox(hWnd, "Error. Cannot crate table database ",
				"", MB_OK | MB_ICONWARNING);
			sqlite3_close(db);
			return 0;

		}
	}


	char* open1 =
		(char*)"INSERT INTO tests (lineID, result, temperature, pressure, minutes) VALUES (?, ?, ?, ?, ?);";
	int rf = sqlite3_prepare(db, open1, -1, &st, NULL);
	sqlite3_bind_int(st, 1, counter);
	sqlite3_bind_text(st, 2, result, sizeof(result), SQLITE_TRANSIENT);
	sqlite3_bind_text(st, 3, temperature, sizeof(temperature), SQLITE_TRANSIENT);
	sqlite3_bind_text(st, 4, pressure, sizeof(pressure), SQLITE_TRANSIENT);
	sqlite3_bind_text(st, 5, minutes, sizeof(minutes), SQLITE_TRANSIENT);
	sqlite3_step(st);
	if (rf != SQLITE_OK) {

		MessageBox(hWnd, "Error. Cannot crate table database ",
			"", MB_OK | MB_ICONWARNING);
		sqlite3_close(db);
		return 0;

	}



	sqlite3_close(db);

	return 0;

}
char* outputInfoLineID(int counter)
{
	char* outputName;
	char* err;
	int rb = sqlite3_open16(L"Info.db", &db);
	std::string select = " SELECT lineID FROM tests WHERE lineID = ";
	std::string count;
	count = std::to_string(counter);
	select = select + count;
	outputName = (char*)select.c_str();
	int rc = sqlite3_exec(db, outputName, callback, &outputInfo, &err);
	return (char*)outputInfo.c_str();

}
char* outputInfoName(int counter)
{
	char* outputName;
	char* err;
	int rb = sqlite3_open16(L"Info.db", &db);
	std::string select = " SELECT result FROM tests WHERE lineID = ";
	std::string count;
	count = std::to_string(counter);
	select = select + count;
	outputName = (char*)select.c_str();
	int rc = sqlite3_exec(db, outputName, callback, 0, &err);
	return (char*)outputInfo.c_str();


}
char* outputInfoTemperature(int counter)
{
	char* outputName;
	char* err;
	int rb = sqlite3_open16(L"Info.db", &db);
	std::string select = " SELECT temperature FROM tests WHERE lineID = ";
	std::string count;
	count = std::to_string(counter);
	select = select + count;
	outputName = (char*)select.c_str();
	int rc = sqlite3_exec(db, outputName, callback, &outputInfo, &err);
	return (char*)outputInfo.c_str();

}
char* outputInfoPressure(int counter)
{
	char* outputName;
	char* err;
	int rb = sqlite3_open16(L"Info.db", &db);
	std::string select = " SELECT pressure FROM tests WHERE lineID = ";
	std::string count;
	count = std::to_string(counter);
	select = select + count;
	outputName = (char*)select.c_str();
	int rc = sqlite3_exec(db, outputName, callback, &outputInfo, &err);
	return (char*)outputInfo.c_str();

}
char* outputInfoMinutes(int counter)
{
	char* outputName;
	char* err;
	int rb = sqlite3_open16(L"Info.db", &db);
	std::string select = " SELECT minutes FROM tests WHERE lineID = ";
	std::string count;
	count = std::to_string(counter);
	select = select + count;
	outputName = (char*)select.c_str();
	int rc = sqlite3_exec(db, outputName, callback, &outputInfo, &err);
	return (char*)outputInfo.c_str();

}
void closeDatabase()
{
	sqlite3_close(db);
}

int callback(void* NotUsed, int argc, char** argv,
	char** azColName)
{
	std::string buffer;
	for (int i = 0; i < argc; i++)
	{
		buffer = argv[i];


	}
	outputInfo = buffer;


	return 0;
}
