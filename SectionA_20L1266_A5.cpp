#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void HomeScreen() {
	cout << "-------------------MENU-------------------\n"
		<< "Enter C to create grid\n"
		<< "Enter S to search words from existing grid\n"
		<< "Enter Q to quit";
}

int StringLength(char*);	// calculates number of characters in a character pointer array
char* InputChar();	//	inputs character form 
void GetWordCount(int&, ifstream&);
char* InputLine(ifstream&);
char** ReadWordListFromFileCreate(int, string);
char** ReadWordListFromFile(int&, string);
char** ReadWordListFromFileSearch(int&, string, int&, int&);
char** FillGridFromFile(const int&, const int&, string);
char* ConvertUCase(char*);
void SortWordList(char**, const int&);
char* RemoveSpace(char*);

// matrix manipulation
char** DeclareMatrix(const int&);
char** DeclareMatrixRC(const int&, const int&);
void PrintMatrix(char**, const int&);
void DeleteMatrix(char**, const int&);
void StoreOutput(char**, const int&, ofstream&);

// for grid creation part
bool CheckHorizontalRtoL(char**, char*, const int&, int, int);
bool CheckHorizontalLtoR(char**, char*, const int&, int, int);
bool CheckVerticalTtoB(char**, char*, const int&, int, int);
bool CheckVerticalBtoT(char**, char*, const int&, int, int);
bool CheckDiagonalLtoRTtoB(char**, char*, const int&, int, int);
bool CheckDiagonalLtoRBtoT(char**, char*, const int&, int, int);
bool CheckDiagonalRtoLTtoB(char**, char*, const int&, int, int);
bool CheckDiagonalRtoLBtoT(char**, char*, const int&, int, int);
void PlaceHorizontalRtoL(char**, char*, const int&, int, int);
void PlaceHorizontalLtoR(char**, char*, const int&, int, int);
void PlaceVerticalTtoB(char**, char*, const int&, int, int);
void PlaceVerticalBtoT(char**, char*, const int&, int, int);
void PlaceDiagonalLtoRTtoB(char**, char*, const int&, int, int);
void PlaceDiagonalLtoRBtoT(char**, char*, const int&, int, int);
void PlaceDiagonalRtoLTtoB(char**, char*, const int&, int, int);
void PlaceDiagonalRtoLBtoT(char**, char*, const int&, int, int);
void FillMatrix(char**, char**, const int&, const int&, const int&, bool&);



// for the search part
bool CheckSHorizontalRtoL(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
bool CheckSHorizontalLtoR(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
bool CheckSVerticalTtoB(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
bool CheckSVerticalBtoT(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
bool CheckSDiagonalLtoRTtoB(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
bool CheckSDiagonalLtoRBtoT(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
bool CheckSDiagonalRtoLTtoB(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
bool CheckSDiagonalRtoLBtoT(char** matrix, char*, const int&, const int&, int, int, int&, int&, const int&, const int&);
void CheckSMatrix(char**, char**, const int&, const int&, const int&, ofstream&);

int main()
{
	char choice = ' ';
	string gridfile, wordfile, outputfile, temp;
	int numOfWords, rows, cols;
	bool fail;

	while (choice != 'Q' || choice != 'q'){
		HomeScreen();
		while ((choice != 'C' || choice != 'c') || (choice != 'S' || choice != 's')) {
			cout << "Enter choice(c, s or q): ";
			cin >> choice;
			if (choice == 'q' || choice == 'Q')
				return -1;
			if ((choice == 'c' || choice == 'C') || (choice == 's' || choice == 'S')) {
				break;
			}
		}

		cout << "\n";

		if (choice == 'c' || choice == 'C') {
			wordfile = ' ';
			numOfWords = 0;
			cout << "Enter name of file that has word list with .txt extension: ";
			cin >> wordfile;

			while (numOfWords < 1) {
				cout << "Enter number of words in file: ";
				cin >> numOfWords;
			}


			char** words = ReadWordListFromFileCreate(numOfWords, wordfile);

			if (words) {
				rows = cols = 0;
				
				while (rows < 1) {
					cout << "Enter rows for grid (should be greater than 0): ";
					cin >> rows;
				}
				while (cols < 1) {
					cout << "Enter cols for grid (should be greater than 0): ";
					cin >> cols;
				}
				
				outputfile = ' ';
				temp = ' ';

				cout << endl;
				do {
					cout << "Enter name of file to store output with .txt extension: ";
					cin >> outputfile;
					temp = outputfile.substr(outputfile.length() - 4, 4);
				} while (temp.compare(".txt") != 0);


				// converts all words to uppercase
				for (int i = 0; i < numOfWords; i++) {
					words[i] = ConvertUCase(words[i]);
				}

				// removes spaces in words that contain spaces
				for (int i = 0; i < numOfWords; i++) {
					words[i] = RemoveSpace(words[i]);
				}

				// prints the wordlist as it was in input.txt
				cout << "\n---------Output Word List---------\n";
				PrintMatrix(words, numOfWords);

				SortWordList(words, numOfWords);	// sorts wordlist in descending order of wondlength

				cout << endl;

				char** grid = DeclareMatrixRC(rows, cols);

				fail = false;
				FillMatrix(grid, words, numOfWords, rows, cols, fail);
				if (!fail) {
					// prints the grid
					cout << "\n---------Output Grid---------\n\n";
					PrintMatrix(grid, rows);
					
					
					ofstream fout(outputfile);
					StoreOutput(grid, rows, fout);
					cout << endl;

					// stores grid in output.txt
					// StoreOutput(Grid, SizeOfGrid, fout);

					// deallocates wordlist
					DeleteMatrix(words, numOfWords);

					// deallocates grid
					DeleteMatrix(grid, rows);
				}
				else system("pause");
				cout << endl;
				fail = false;
			}

		}

		if (choice == 's' || choice == 'S') {
			rows = cols = 0;
			numOfWords = 0;
			wordfile = ' ';
			cout << "Enter filename that contains wordlist with .txt extension: ";
			cin >> wordfile;
			char** words = ReadWordListFromFileSearch(numOfWords, wordfile, rows, cols);
			
			if (words) {
				gridfile = ' ';
				cout << "Enter filename that contains grid with .txt extension: ";
				cin >> gridfile;
				char** grid = FillGridFromFile(rows, cols, gridfile);
				
				if (grid) {
					// converts grid to uppercase if not already uppercase
					for (int i = 0; i < rows; i++) {
						grid[i] = ConvertUCase(grid[i]);
					}

					// converts all words to uppercase
					for (int i = 0; i < numOfWords; i++) {
						words[i] = ConvertUCase(words[i]);
					}

					cout << endl;
					
					outputfile = ' ';
					temp = ' ';
					
					do {
						cout << "Enter name of file to store output with .txt extension: ";
						cin >> outputfile;
						temp = outputfile.substr(outputfile.length() - 4, 4);
					} while (temp.compare(".txt") != 0);

					// prints the wordlist as it was in input.txt
					cout << "\n---------Output Word List---------\n";
					PrintMatrix(words, numOfWords);

					// prints the grid
					cout << "\n---------Output Grid---------\n\n";
					PrintMatrix(grid, rows);


					cout << "\n---------Output Location---------\n";


					cout << endl;
					ofstream fout(outputfile);
					CheckSMatrix(grid, words, rows, numOfWords, cols, fout);

					// deallocates wordlist
					DeleteMatrix(words, numOfWords);

					// deallocates grid
					DeleteMatrix(grid, rows);
				}
			}	
			cout << endl;
			system("pause");
			cout << endl;
		}
	}
}


// calculates number of characters in a character pointer array
int StringLength(char* input) {
	int length = 0;

	for (char* i = input; *i != '\0'; i++)
		if (*i != ' ')
			length++;

	return length;
}

//	inputs character form 
char* InputChar() {
	char* temp = new char(80);
	cin.getline(temp, 80);

	int sizeoftemp = StringLength(temp);
	char* arr = new char[sizeoftemp + 1];

	for (int i = 0; i < sizeoftemp; i++)
		arr[i] = temp[i];

	arr[sizeoftemp] = '\0';
	delete temp;

	return arr;
}

void GetWordCount(int& size, ifstream& FIN) {
	string temp;
	do {
		getline(FIN, temp, '\n');
		size++;
	} while (!FIN.eof());
}

char* InputLine(ifstream& fin) {

	char* buffer = new char[80];

	fin.getline(buffer, 80, '\n');
	int linelen = StringLength(buffer);


	char* line = new char[linelen + 1];
	int count = 0;
	for (int i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] != ' ')
			line[count++] = buffer[i];
	line[linelen] = '\0';

	delete[] buffer;

	return line;
}

char** ReadWordListFromFileCreate(int size, string file) {
	ifstream fin(file);
	if (!fin) {
		cout << "\nError! File not found\n\n";
		return NULL;
	}

	if (size < 1) {
		cout << "invalid size\n\n";
		return NULL;
	}

	char** wordList = new char* [size]; //declares 2d array of character to store file contents

	for (int i = 0; i < size; i++)
	{
		wordList[i] = InputLine(fin);
	}

	fin.close();


	return wordList;
}

char** ReadWordListFromFile(int& size, string file) {
	ifstream fin(file);
	if (!fin) {
		cout << "\nError! File not found\n\n";
		return NULL;
	}
	GetWordCount(size, fin);
	fin.clear();
	fin.seekg(0);


	if (size < 1) {
		cout << "invalid size\n\n";
		return NULL;
	}

	char** wordList = new char* [size]; //declares 2d array of character to store file contents

	for (int i = 0; i < size; i++)
	{
		wordList[i] = InputLine(fin);
	}

	fin.close();


	return wordList;
}

char** ReadWordListFromFileSearch(int& size, string file, int& rows, int& cols) {
	ifstream fin(file);
	if (!fin) {
		cout << "\nError! File not found\n\n";
		return NULL;
	}
	
	fin >> rows >> cols >> size;

	if (size < 1) {
		cout << "invalid size\n\n";
		return NULL;
	}

	char temp[80];
	fin.getline(temp, 80, '\n');

	char** wordList = new char* [size]; //declares 2d array of character to store file contents

	for (int i = 0; i < size; i++)
	{
		wordList[i] = InputLine(fin);
	}

	fin.close();


	return wordList;
}

char** FillGridFromFile(const int& rows, const int& cols, string file) {
	ifstream fin(file);
	if (!fin) {
		cout << "\nError! File not found\n\n";
		return NULL;
	}

	if (rows < 1) {
		cout << "invalid size\n\n";
		return NULL;
	}

	char** grid = DeclareMatrixRC(rows, cols); //declares 2d array of character to store file contents

	for (int i = 0; i < rows; i++)
		for (int j = 0 ; j < cols ; j++)
			fin >> grid[i][j];

	fin.close();

	return grid;
}

// converts all letters to upper case if they are in lower case
char* ConvertUCase(char* arr) {
	int size = StringLength(arr);
	char* temp = new char[size + 1];
	for (int i = 0; i < size; i++)
		temp[i] = arr[i];   // copies arr to a temp to be later manipulated

	temp[size] = '\0';  // null at the end of the string

	for (int i = 0; i < size; i++) {
		if ((int)arr[i] >= 97)   // converts ith term to lowercase if it is in uppercase
			temp[i] -= 32;
	}

	return temp;
}

// sorts character array in descending order of word length
void SortWordList(char** wordlist, const int& numOfWords) {
	int i, j;

	for (i = 1; i < numOfWords; i++) {
		char* temp = wordlist[i];
		j = i - 1;

		while (j >= 0 && StringLength(temp) > StringLength(wordlist[j])) {
			wordlist[j + 1] = wordlist[j];
			j--;
		}
		wordlist[j + 1] = temp;
	}

}

// removes spaces if found in the character pointer
char* RemoveSpace(char* arr) {
	int size = StringLength(arr);
	int modifiedSize = size;	// will store the size without the spaces

	for (int i = 0; i < size; i++)
		if (arr[i] == 32)
			modifiedSize--;   // decrements when space found

	char* temp = new char[modifiedSize + 1];	// declares a temp array with modifiedSize
	temp[modifiedSize] = '\0';  // null at the end of the string

	for (int i = 0, count = 0; i < size; i++, count++) {
		if ((int)arr[i] == 32)   // converts ith term to lowercase if it is in uppercase
			i++;
		temp[count] = arr[i];
	}

	return temp;
}

// checks for eight possible ways a word may be placed inside the grid
// also checks for overlaps between words

bool CheckHorizontalRtoL(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (col - wordlength < 0)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row][col - i] != '\0' && matrix[row][col - i] != word[i])
			return false;

	return  true;
}

bool CheckHorizontalLtoR(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (col + wordlength > gridcols)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row][col + i] != '\0' && matrix[row][col + i] != word[i])
			return false;

	return  true;
}

bool CheckVerticalTtoB(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (row + wordlength > gridrows)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row + i][col] != '\0' && matrix[row + i][col] != word[i])
			return false;

	return  true;
}

bool CheckVerticalBtoT(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (row - wordlength < 0)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row - i][col] != '\0' && matrix[row - i][col] != word[i])
			return false;

	return  true;
}

bool CheckDiagonalLtoRTtoB(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (row + wordlength > gridrows || col + wordlength > gridcols)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row + i][col + i] != '\0' && matrix[row + i][col + i] != word[i])
			return false;

	return  true;
}

bool CheckDiagonalLtoRBtoT(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (row - wordlength < 0 || col + wordlength > gridcols)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row - i][col + i] != '\0' && matrix[row - i][col + i] != word[i])
			return false;

	return  true;
}

bool CheckDiagonalRtoLTtoB(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (row + wordlength > gridrows || col - wordlength < 0)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row + i][col - i] != '\0' && matrix[row + i][col - i] != word[i])
			return false;

	return  true;
}

bool CheckDiagonalRtoLBtoT(char** matrix, char* word, const int& wordlength, int row, int col, const int& gridrows, const int& gridcols) {
	if (row - wordlength < 0 || col - wordlength < 0)
		return false;

	for (int i = 0; i < wordlength; i++)
		if (matrix[row - i][col - i] != '\0' && matrix[row - i][col - i] != word[i])
			return false;

	return  true;
}

// places the word in the grid depending on the random number generated in FillMatrix if check of respective function comes back true

void PlaceHorizontalRtoL(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row][col - i] = word[i];
}

void PlaceHorizontalLtoR(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row][col + i] = word[i];
}

void PlaceVerticalTtoB(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row + i][col] = word[i];

}

void PlaceVerticalBtoT(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row - i][col] = word[i];
}

void PlaceDiagonalLtoRTtoB(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row + i][col + i] = word[i];
}

void PlacekDiagonalLtoRBtoT(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row - i][col + i] = word[i];
}

void PlaceDiagonalRtoLTtoB(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row + i][col - i] = word[i];
}

void PlaceDiagonalRtoLBtoT(char** matrix, char* word, const int& wordlength, int row, int col) {
	for (int i = 0; i < wordlength; i++)
		matrix[row - i][col - i] = word[i];
}

void FillMatrix(char** matrix, char** wordlist, const int& size, const int& gridrows, const int& gridcols, bool& fail) {
	srand((unsigned)time(NULL));
	int row, col, wordlength, placementchoice, count = 0;
	for (int i = 0, flag = 0; i < size;) {
		wordlength = StringLength(wordlist[i]);

		row = rand() % (gridrows);
		col = rand() % (gridcols);
		placementchoice = rand() % 8;
		if (flag == 1) flag = 0;
		if (count == 5000) count = 0;

		if (placementchoice == 0) {
			if (CheckHorizontalLtoR(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlaceHorizontalLtoR(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}
		else if (placementchoice == 1) {
			if (CheckHorizontalRtoL(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlaceHorizontalRtoL(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}
		else if (placementchoice == 2) {
			if (CheckVerticalTtoB(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlaceVerticalTtoB(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}
		else if (placementchoice == 3) {
			if (CheckVerticalBtoT(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlaceVerticalBtoT(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}
		else if (placementchoice == 4) {
			if (CheckDiagonalLtoRTtoB(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlaceDiagonalLtoRTtoB(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}
		else if (placementchoice == 5) {
			if (CheckDiagonalLtoRBtoT(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlacekDiagonalLtoRBtoT(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}
		else if (placementchoice == 6) {
			if (CheckDiagonalRtoLTtoB(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlaceDiagonalRtoLTtoB(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}
		else if (placementchoice == 7) {
			if (CheckDiagonalRtoLBtoT(matrix, wordlist[i], wordlength, row, col, gridrows, gridcols)) {
				PlaceDiagonalRtoLBtoT(matrix, wordlist[i], wordlength, row, col);
				flag = 1;
			}
		}

		count++;

		if (flag == 1 || count == 5000) {
			if (count == 5000) {
				cout <<"Error!! Grid cannot be formed\n";
				fail = true;
				return;
			}
			i++;
		}
	}
	for (int i = 0; i < gridrows; i++)
		for (int j = 0; j < gridcols; j++)
			if (matrix[i][j] == '\0')
				matrix[i][j] = 65 + (rand() % 26);

	return;
}



// checks if the word is present in all possible ways

bool CheckSHorizontalRtoL(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (col + 1 - wordlength < 0)
		return false;

	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row][col - i] != word[i]) {
			return false;
		}
		endpoint++;
	}

	endrow = row;
	endcol = col - endpoint + 1;

	return  true;
}

bool CheckSHorizontalLtoR(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (col + wordlength > gridcols)
		return false;
	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row][col + i] != word[i])
			return false;
		endpoint++;
	}

	endrow = row;
	endcol = col + endpoint - 1;

	return  true;
}

bool CheckSVerticalTtoB(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (row + wordlength > size)
		return false;

	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row + i][col] != word[i])
			return false;
		endpoint++;
	}

	endrow = endpoint + row - 1;
	endcol = col;

	return  true;
}

bool CheckSVerticalBtoT(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (row + 1 - wordlength < 0)
		return false;

	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row - i][col] != word[i])
			return false;
		endpoint++;
	}

	endrow = row - endpoint + 1;
	endcol = col;

	return  true;
}

bool CheckSDiagonalLtoRTtoB(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (row + wordlength > size || col + wordlength > gridcols)
		return false;

	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row + i][col + i] != word[i])
			return false;
		endpoint++;
	}

	endrow = row + endpoint - 1;
	endcol = col + endpoint - 1;

	return  true;
}

bool CheckSDiagonalLtoRBtoT(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (row + 1 - wordlength < 0 || col + wordlength > gridcols)
		return false;

	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row - i][col + i] != word[i])
			return false;
		endpoint++;
	}

	endrow = row - endpoint + 1;
	endcol = col + endpoint - 1;

	return  true;
}

bool CheckSDiagonalRtoLTtoB(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (row + wordlength > size|| col + 1 - wordlength < 0)
		return false;

	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row + i][col - i] != word[i])
			return false;
		endpoint++;
	}

	endrow = row + endpoint - 1;
	endcol = col - endpoint + 1;

	return  true;
}

bool CheckSDiagonalRtoLBtoT(char** matrix, char* word, const int& wordlength, const int& size, int row, int col, int& endrow, int& endcol, const int& gridcols) {
	if (row + 1 - wordlength < 0 || col + 1 - wordlength < 0)
		return false;

	int endpoint = 0;

	for (int i = 0; i < wordlength; i++) {
		if (matrix[row - i][col - i] != word[i])
			return false;
		endpoint++;
	}

	endrow = row - endpoint + 1;
	endcol = col - endpoint + 1;

	return  true;
}

void CheckSMatrix(char** matrix, char** wordlist, const int& size, const int& wordcount, const int& gridcols, ofstream& fout) {
	int startrow = 0, startcol = 0, endrow = 0, endcol = 0, wordlength, flag = 0, count = 0;

	for (int word = 0; word < wordcount; word++) {
		if (flag == 1) flag = 0;
		if (endrow != 0 || endcol != 0) {
			endrow = 0;
			endcol = 0;
		}

		for (startrow = 0, flag = 0; startrow < size && flag == 0; startrow++) {
			wordlength = StringLength(wordlist[word]);
			for (startcol = 0; matrix[startrow][startcol] != '\0' && flag == 0; startcol++) {
				if (matrix[startrow][startcol] == wordlist[word][0]) {
					if (CheckSHorizontalLtoR(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
					else if (CheckSHorizontalRtoL(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
					else if (CheckSVerticalTtoB(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
					else if (CheckSVerticalBtoT(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
					else if (CheckSDiagonalLtoRTtoB(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
					else if (CheckSDiagonalLtoRBtoT(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
					else if (CheckSDiagonalRtoLTtoB(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
					else if (CheckSDiagonalRtoLBtoT(matrix, wordlist[word], wordlength, size, startrow, startcol, endrow, endcol, gridcols)) {
						flag = 1;
					}
				}
			}
		}
		if (flag == 1) {
			cout << "{" << startrow - 1 << "," << startcol - 1 << "},{" << endrow << "," << endcol << "}" << endl;
			fout << "{" << startrow - 1 << "," << startcol - 1 << "},{" << endrow << "," << endcol << "}" << endl;
		}
		else {
			cout << "Not Found\n";
			fout << "Not Found\n";

		}
	}
}

// declares a 2d dynamic array of size rows x rows
char** DeclareMatrix(const int& rows) {
	char** temp = new char* [rows];

	for (int i = 0; i < rows; ++i)
		temp[i] = new char[rows + 1];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < rows + 1; j++)
			temp[i][j] = '\0';

	return temp;
}

char** DeclareMatrixRC(const int& rows, const int& cols) {
	char** temp = new char* [rows];

	for (int i = 0; i < rows; ++i)
		temp[i] = new char[cols + 1];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols + 1; j++)
			temp[i][j] = '\0';

	return temp;
}

// prints matrix
void PrintMatrix(char** matrix, const int& rows) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; matrix[i][j] != '\0'; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}
//void PrintMatrixCreate(char** matrix, const int& rows, const int& cols) {
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++)
//			cout << matrix[i][j] << " ";
//		cout << endl;
//	}
//}

// deallocates 2d array
void DeleteMatrix(char** matrix, const int& rows) {
	for (int i = 0; i < rows; i++)
		delete[] matrix[i];

	delete[] matrix;
}

// stores output grid into output file
void StoreOutput(char** grid, const int& SizeOfGrid, ofstream& fout) {
	for (int i = 0; i < SizeOfGrid; i++) {
		for (int j = 0; grid[i][j] != '\0'; j++)
			fout << grid[i][j] << " ";
		fout << endl;
	}
}