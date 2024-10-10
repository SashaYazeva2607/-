#include <conio.h>
#include <windows.h>
int main()
{
	HANDLE hStdoutOld, hStdoutNew; // дескрипторы буфера экрана 
	DWORD dwWritten; // для количества выведенных символов. 
	// создаем буфер экрана 
	hStdoutNew = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, // чтение и запись
		0, // не разделяемый 
		NULL, // защита по умолчанию 
		CONSOLE_TEXTMODE_BUFFER, // текстовый режим
		NULL); // не используется 
	if (hStdoutNew == INVALID_HANDLE_VALUE)
	{
		_cputs("Create console screen buffer failed.\n");
		return GetLastError();
	}   // сохраняем старый буфер экрана 
	hStdoutOld = GetStdHandle(STD_OUTPUT_HANDLE);
	// ждем команду на переход к новому буферу экрана 
	_cputs("Press any key to set new screen buffer active.\n");
	_getch(); // делаем активным новый буфер экрана 
	if (!SetConsoleActiveScreenBuffer(hStdoutNew))
	{
		_cputs("Set new console active screen buffer failed.\n");
		return GetLastError();
	} // выводим текст в новый буфер экрана 
	char text[] = "This is a new screen buffer.";
	if (!WriteConsole(
		hStdoutNew, // дескриптор буфера экрана 34 
		text, // символы, которые выводим 35 
		sizeof(text), // длина текста 
		&dwWritten, // количество выведенных символов 36 37
		NULL)) // не используется 
		_cputs("Write console output character failed.\n");
	// выводим сообщение о вводе символа 
	char str[] = "\nPress any key to set old screen buffer.";
	if (!WriteConsole(
		hStdoutNew, // дескриптор буфера экрана j
		str, // символы, которые выводим 
		sizeof(str), // длина текста 
		&dwWritten, // количество выведенных символов 
		NULL)) // не используется 
		_cputs("Write console output character failed.\n");
	_getch(); // восстанавливаем старый буфер экрана 50 
	if (!SetConsoleActiveScreenBuffer(hStdoutOld))
	{
		_cputs("Set old console active screen buffer failed.\n");
		return GetLastError();
	}
	// пишем в старый буфер экрана 56 
	_cputs("This is an old console screen buffer.\n");
	// закрываем новый буфер экрана 
	CloseHandle(hStdoutNew); // ждем команду на завершение программы 
	_cputs("Press any key to finish.\n");
	_getch();
	return 0;
}