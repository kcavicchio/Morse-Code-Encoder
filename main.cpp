#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

void clearScreen();


void saveFile(string output)
{
	ofstream file("output.txt");
	if (file.is_open())
	{
		file << output;
		file.close();
	}
}

int main()
{
	//char ch = getch(); 
	//endwin(); 
	//printf("KEY NAME : %s - %d\n", keyname(ch), ch);
	char input;
	string output;
	string hidden; //we save the alphanumeric input in this string
	string total; //we save the overall translation in this string (so we can rewrite it out in the case of backspace)

	bool quit = false;
	while (!quit)
	{
		if (_kbhit())
		{
			input = _getch();
			bool addSpace = true;
			hidden += input;
			//cout << input;
			switch (input)
			{
			case 'a': case 'A':
				output = ".-";
				break;
			case 'b': case 'B':
				output = "-...";
				break;
			case 'c': case 'C':
				output = "-.-.";
				break;
			case 'd': case 'D':
				output = "-..";
				break;
			case 'e': case 'E':
				output = ".";
				break;
			case 'f': case 'F':
				output = "..-.";
				break;
			case 'g': case 'G':
				output = "--.";
				break;
			case 'h': case 'H':
				output = "....";
				break;
			case 'i': case 'I':
				output = "..";
				break;
			case 'j': case 'J':
				output = ".---";
				break;
			case 'k': case 'K':
				output = "-.-";
				break;
			case 'l': case 'L':
				output = ".-..";
				break;
			case 'm': case 'M':
				output = "--";
				break;
			case 'n': case 'N':
				output = "-.";
				break;
			case 'o': case 'O':
				output = "---";
				break;
			case 'p': case 'P':
				output = ".--.";
				break;
			case 'q': case 'Q':
				output = "--.-";
				break;
			case 'r': case 'R':
				output = ".-.";
				break;
			case 's': case 'S':
				output = "...";
				break;
			case 't': case 'T':
				output = "-";
				break;
			case 'u': case 'U':
				output = "..-";
				break;
			case 'v': case 'V':
				output = "...-";
				break;
			case 'w': case 'W':
				output = ".--";
				break;
			case 'x': case 'X':
				output = "-..-";
				break;
			case 'y': case 'Y':
				output = "-.--";
				break;
			case 'z': case 'Z':
				output = "--..";
				break;
			case '0':
				output = "-----";
				break;
			case '1':
				output = ".----";
				break;
			case '2':
				output = "..---";
				break;
			case '3':
				output = "...--";
				break;
			case '4':
				output = "....-";
				break;
			case '5':
				output = ".....";
				break;
			case '6':
				output = "-....";
				break;
			case '7':
				output = "--...";
				break;
			case '8':
				output = "---..";
				break;
			case '9':
				output = "----.";
				break;
			case ' ':
				output = "/";
				break;
			case '.':
				output = "-.-.-.";
				break;
			case '\r':
				output = "/\n";
				hidden += '\n';
				addSpace = false;
				break;
			case '\t':
				quit = true;
				break;
			case '\b':
				//in the case of backspace, the only way I could figure out
				//to erase text from command output was to clear the whole screen
				clearScreen();
				output = "";
				//output = "\b \b";
				if (hidden.size() >= 1)
					hidden = hidden.substr(0, hidden.size() - 2 );
				if (total.size() >= 1)
					total = total.substr(0, total.size() - 1);
				while (total.size() >= 1 && total[total.size() - 1] != ' ')
				{
					total = total.substr(0, total.size() - 1);
					//output += "\b \b";
				}
				cout << total;
				addSpace = false;
				break;
			/*case '^s':
				//if (hidden.size() >= 1);
					//hidden = hidden.substr(0, hidden.size() - 2);
				saveFile(hidden);
				output = "";
				addSpace = false;
				break;*/
			default:
				output = input;
				break;
			}
			if (output == "\n") break;
			if (addSpace) output += " ";
			total += output;
			cout << output;
		}
	}
	//cout << endl << hidden << endl;
	saveFile(hidden); //we save the original text input to the output file
}


///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
//  Note: I borrowed this function from some code that Prof. Smallberg
//  handed us in CS 31 to facilitate one of our projects.
///////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
	static const char* term = getenv("TERM");
	if (term == nullptr || strcmp(term, "dumb") == 0)
		cout << endl;
	else
	{
		static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
		cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
	}
}

#endif
