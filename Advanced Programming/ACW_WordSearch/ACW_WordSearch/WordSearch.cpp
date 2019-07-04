#include "WordSearch.h"
#include <fstream>
#include <sstream>
#include <String>
#include <iostream>
#include <Algorithm>
#include <Vector>

using namespace std;


struct LLNode         // Stores the advanced Grid
{
	char Data;
	LLNode* Left = nullptr;
	LLNode* Right= nullptr;
	LLNode* Up = nullptr;
	LLNode* Down = nullptr;
	LLNode* topLeft = nullptr;
	LLNode* topRight = nullptr;
	LLNode* bottomLeft = nullptr;
	LLNode* bottomRight = nullptr;
};
LLNode* headPtr;      // stores the address of the head node 
LLNode* RootHead;     // stores the address to the root/head of the list

//Size of Grid
int gridsize;
//2d Array storing Grid
char simpleGrid[9][9] = {};

//Array storing Dictionary
string Dictionary[30];                            
                
// For searching in all 8 direction
int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int wordsMatched;                               //Number of words matched
// the row and column of matched word
int MatchedCol[30];                   
int MatchedRow[30];
int cellsVisited;                            // Number of cells visited
//Number of dictionary entries visited
int DicNumbers;
int DictionaryVisits;
// Matched words in the order they were matched
string OrderedMatchedWords[30];
// Size of Dictionary

int MaxWords;
// ordered words to be compaired for write results method
int MaxOrderedWords;
string UnmatchedWords[30];
//OUtput file name for write results
string outputFile;



WordSearch::WordSearch(const char * const filename) {     //filename = output_simple.txt or output_advanced.txt 
	// Add your code here
	outputFile = filename;
	gridsize = 0;
	DicNumbers = 0;
	DictionaryVisits = 0;
	cellsVisited = 0;
	MaxOrderedWords = 0;
	wordsMatched = 0;
	MaxWords = 0;
	headPtr = nullptr;  // set list as empty

}

WordSearch::~WordSearch() {
	LLNode* move = RootHead;
	while (RootHead)
	{
		for (int i = 0; i < gridsize; i++)
		{
			for (int j = 0; j < gridsize; j++)
			{
				RootHead = move->Right;
				delete move;
				move = RootHead;
				if (i == gridsize - 1)
				{
					move = move->Down;
				}
			}
		}	
	}
}

void WordSearch::ReadSimplePuzzle() {
	ifstream fin;
	fin.open(puzzleName);
	string str;
	char c;
	if (fin)
	{		
		getline(fin, str);
		gridsize = atoi(str.c_str());
		for (int Rows = 0; Rows < gridsize; Rows++)
		{
			for (int Cols = 0; Cols < gridsize;)
			{
				fin.get(c);
				if (c != ' ' && c != '\n')
				{
					simpleGrid[Rows][Cols] = c;
					Cols++;
				}
			}
		}			
	}
	else
	{
		cout << "Error while oppening simple file" << endl;
	}
	fin.close();
}



void WordSearch::ReadSimpleDictionary() {
	vector<string> Dictionaryarray;
	int j = 0;
	ifstream Fin;
	Fin.open(dictionaryName);
	if (Fin.fail())
	{ cerr << "Cannot open simple dictionary file" << endl;}
	else
	{
		for (int i = 0; i < 30; i++)
		{
			if (Fin.eof())
			{
				break;
			}
			else
			{
				getline(Fin, Dictionary[i]);
				Dictionaryarray.push_back(Dictionary[i]);
				sort(Dictionaryarray.begin(), Dictionaryarray.end());           //sorts vector array
				MaxWords++;
			}
		}
		for (vector<string>::const_iterator i = Dictionaryarray.begin(); i != Dictionaryarray.end(); ++i)  // puts sorted array back into regular array
		{
			Dictionary[j] = *i;	
			j++;
		}
	}
   Fin.close();
}

void WordSearch::ReadAdvancedPuzzle() {
	ifstream fin;
	fin.open(puzzleName);
	string str;
	char c;
	LLNode* TempAbove = nullptr;   // Stores the temporary value held above the current node
	LLNode* TempAbovePrevious= nullptr;   // Stores the previous temp above value
	LLNode* Temp = nullptr;       //holds current row location of root head
	if (fin)
	{
		getline(fin, str);
		gridsize = atoi(str.c_str());                 //Size of the grid (e.g., 15)
		for (int Rows = 0; Rows < gridsize; Rows++)   ////......
		{
			for (int Cols = 0; Cols < gridsize;)   /////::::::::
			{
				fin.get(c);
				if (c != ' ' && c != '\n')
				{
					struct LLNode* newNode = new LLNode;                       //(struct LLNode*)malloc(sizeof(struct LLNode));
					if(headPtr== nullptr)  //if first letter
					{
						headPtr = newNode;
						RootHead = headPtr;   // stores the head address 
						newNode->Data = c;
						Temp = headPtr;
					}
					else if (TempAbove== nullptr)  //if first row of grid
					{
						newNode->Data = c;         //set data to letter in grid
						headPtr->Right = newNode;   //link last item to this item
						newNode->Left = headPtr;  //link this item to last 
						headPtr = newNode;         // move head to this node
						if (Cols == gridsize-1)      // if at last col 
						{
							TempAbove = Temp;  
						}					
					}
					else if (TempAbove != nullptr)
					{
						newNode->Data = c;                              // (1  Data Link )
						TempAbove->Down = newNode;
						newNode->Up = TempAbove;                        // (2  Vertical Up/down 1 link )
						if (Cols == 0)                         // 3 links
						{
						 newNode->topRight = TempAbove->Right;
						 Temp = newNode;                       // to store address of first letter of col (will become TempAbove on next row)
						 
						 TempAbovePrevious = TempAbove;
						 TempAbove = TempAbove->Right; // move to next letter above
						 headPtr = newNode;                           // current node (Previous node when using it above this line)
						}
						else if (Cols!= 0 && Cols!=gridsize-1)  //L        5 links
						{
							newNode->topRight = TempAbove->Right;
							headPtr->Right = newNode;                   
							newNode->Left = headPtr;                    // (3  Horizontal Left/Right 1 Link )
							TempAbove->bottomLeft = headPtr;            // (4  Diagonal Topright/Bottomleft Link)
							TempAbovePrevious->bottomRight = newNode; 
							newNode->topLeft = TempAbovePrevious;       // (5  Diagonal Topleft/BottomRight link)

							TempAbovePrevious = TempAbove;
							TempAbove = TempAbove->Right; // move to next letter above
							headPtr = newNode;                           // current node (Previous node when using it above this line)
						}
						else if (Cols == gridsize-1)      //              4 links
						{
							 headPtr->Right = newNode;
							 newNode->Left = headPtr;                    // (3  Horizontal Left/Right 1 Link )
							 TempAbovePrevious->bottomRight = newNode;
							 newNode->topLeft = TempAbovePrevious;       // (4  Diagonal Topleft/BottomRight link)
							 TempAbove->bottomLeft = headPtr;
							 headPtr->topRight = TempAbove;	 
                             TempAbove = Temp;
						}        
					}
				Cols++;
				}
			}				
		}	
	}
	else
	{
		cout << "Error while oppening simple file" << endl;
	}
	fin.close();
}

void WordSearch::ReadAdvancedDictionary() {
	std::cout;
}



void WordSearch::SolvePuzzleSimple() {
	for (int row = 0; row < gridsize; row++)                 // cycle through the grid rows .......
	{
		for (int col = 0; col < gridsize; col++)             // cycle through the grid cols ::::::::
		{
			char Currentletter = simpleGrid[row][col];        // sets the current letter to the letter in grid
			cellsVisited++;
			for (int WordCount = 0; WordCount < MaxWords; WordCount++)   //Cycle through the dictionary of words    
			{
				DictionaryVisits++;
				string CurrentWord = Dictionary[WordCount];        // Current word equals the current word we are looking at in dictionary
				
				if (Currentletter < CurrentWord[0])                 // if passed the possible matches 
				{
					WordCount = MaxWords;
					break;
				}

				if (Currentletter == CurrentWord[0])                    // if grid letter = to first letter of current word
				{
					for (int direction = 0; direction < 8; direction++)
					{
						int rowdirection = row + x[direction], coldirection = col + y[direction];
					    int LengthValidation;
						int Wordlength = CurrentWord.length();
						for (LengthValidation = 1; LengthValidation < Wordlength; LengthValidation++)
						{
							if (rowdirection >= gridsize || rowdirection < 0 || coldirection >= gridsize || coldirection < 0)
							{
								cellsVisited++;
								break;
							}
							if (simpleGrid[rowdirection][coldirection] != CurrentWord[LengthValidation])
							{
								cellsVisited++;
								break;
							}
							rowdirection += x[direction], coldirection += y[direction];
						}
						if (LengthValidation == Wordlength)                   // if all characters have been matched
						{
							MatchedCol[wordsMatched]= col;  
							MatchedRow[wordsMatched] = row;
							OrderedMatchedWords[wordsMatched] = CurrentWord;
							MaxOrderedWords++;
							wordsMatched++;
							DictionaryVisits++;
							break;
						}
					}
				}		
			}
		}
	}
}

void WordSearch::SolvePuzzleAdvanced() {
	LLNode * ColPosHolder = nullptr;                                   // holds the current position of the first item of each col
	int directionRow = 0;                                    // ints that change according to the direction of a sequence matched
	int directionCol = 0;
	for (int row = 0; row < gridsize; row++)                 // cycle through the grid rows .......
	{
		for (int col = 0; col < gridsize; col++)             // cycle through the grid cols ::::::::
		{
			char CurrentletterCycle = RootHead->Data;        // sets the current letter to the letter in grid
			for (int WordCount = 0; WordCount < MaxWords; WordCount++)   //Cycle through the dictionary of words    
			{
				DictionaryVisits++;
				string CurrentWord = Dictionary[WordCount];        // Current word equals the current word we are looking at in dictionary				
				if (col == 0)
				{
					ColPosHolder = RootHead;            // sets it to first col position in row
				}
				if (CurrentletterCycle < CurrentWord[0])                 // if passed the possible matches 
				{
					WordCount = MaxWords;
					
					break;
				}
				if (CurrentletterCycle == CurrentWord[0])                    // if grid letter = to first letter of current word
				{
					LLNode * HeadHolder = RootHead;    // pointer so that points at different direction sequences
					directionCol = col;
					directionRow = row;
					for (int direction = 0; direction < 8; direction++)
					{
						int LengthValidation;
						int Wordlength = CurrentWord.length();
						for (LengthValidation = 1; LengthValidation < Wordlength; LengthValidation++)  // increases till the entire words has been found 
						{		
							switch (direction)                       //the direction the sequence is following (diagonal verticle horizontal)
							{
							case 0:
								HeadHolder = HeadHolder->topLeft;
								directionCol -= 1;
								directionRow -=  1;
								break;
							case 1:
								HeadHolder = HeadHolder->Up;
								directionRow -=  1;
								break;
							case 2:
								HeadHolder = HeadHolder->topRight;
								directionCol += 1;
								directionRow -=  1;
								break;
							case 3:
								HeadHolder = HeadHolder->Left;
								directionCol -=  1;
								break;
							case 4:
								HeadHolder = HeadHolder->Right;
								directionCol += 1;
								break;
							case 5:
								HeadHolder = HeadHolder->bottomLeft;
								directionCol -= 1;
								directionRow += 1;
								break;
							case 6:
								HeadHolder = HeadHolder->Down;
								directionRow += 1;
								break;
							case 7:
								HeadHolder = HeadHolder->bottomRight;
								directionCol += 1;
								directionRow += 1;
								break;
							default:
								break;
							}						

							// If out of bound break
							//if normal edge block 
							if ((row == 0 && (direction == 0 || direction == 1 || direction == 2)) || (col == 0 && (direction == 0 || direction == 3 || direction == 5)) || (col==gridsize-1 && (direction == 2 || direction == 4 || direction ==7))||(row ==gridsize-1 && (direction == 5 || direction == 6 || direction == 7)))
							{
								cellsVisited++;
								HeadHolder = RootHead;
								directionCol = col;
								directionRow = row;
								break;
							}
							// if left top corner edge block 
							if ((row == 0 && col==0 ) && (direction == 0 || direction == 1 || direction == 2 || direction == 3 || direction == 5))
							{
								cellsVisited++;
								HeadHolder = RootHead;
								directionCol = col;
								directionRow = row;
								break;
							}

							// if right top corner edge block 
							if ((row == 0 && col == gridsize - 1) && (direction == 0 || direction == 1 || direction == 2 || direction == 4 || direction == 7))
							{
								cellsVisited++;
								HeadHolder = RootHead;
								directionCol = col;
								directionRow = row;
								break;
							}

							// if left bottom corner edge block
							if ((row == gridsize - 1 && col == 0 ) && (direction == 0 || direction == 3 || direction == 5 || direction == 6 || direction == 7))
							{
								cellsVisited++;
								HeadHolder = RootHead;
								directionCol = col;
								directionRow = row;
								break;
							}

							// if Right bottom corner edge block
							if ((row == gridsize - 1 && col == gridsize - 1) && (direction == 2 || direction == 4 || direction == 5 || direction == 6 || direction == 7))
							{
								cellsVisited++;
								HeadHolder = RootHead;
								directionCol = col;
								directionRow = row;
								break;
							}

							//if out of bounds 
							if(directionCol <0 || directionRow <0 || directionCol>=gridsize || directionRow>=gridsize)
							{
								cellsVisited++;
								HeadHolder = RootHead;
								directionCol = col;
								directionRow = row;
								break;
								
							}

							// If not matched,  break
							if (HeadHolder->Data != CurrentWord[LengthValidation])
							{
								cellsVisited++;
								HeadHolder = RootHead;
								directionCol = col;
								directionRow = row;
								break;
							}

							cellsVisited++;
						}
						// If all character matched, then value of must
						// be equal to length of word
						if (LengthValidation == Wordlength)
						{
							MatchedCol[wordsMatched] = col;
							MatchedRow[wordsMatched] = row;
							OrderedMatchedWords[wordsMatched] = CurrentWord;
							MaxOrderedWords++;
							wordsMatched++;
							DictionaryVisits++;
							directionCol = col;
							directionRow = row;
							break;
						}
					}
				}
			}
			if (col==gridsize-1)
			{
			RootHead = ColPosHolder->Down;
			}
			else
			{
			RootHead = RootHead->Right;
			}
		}
	}	
}

void WordSearch::WriteResults(const double loadTime, const double solveTime) const {	
	ofstream myfile;
	myfile.open(outputFile);

	myfile << "NUMBER_OF_WORDS_MATCHED ";
	myfile << wordsMatched<<endl;
	myfile << endl;
	myfile << "WORDS_MATCHED_IN_GRID" << endl;

	for (int i =0 ;i< wordsMatched;i++)
	{
		myfile << MatchedRow[i];
		myfile << " ";
		myfile << MatchedCol[i];
		myfile << " ";
		myfile << OrderedMatchedWords[i]  << endl;
	}
	myfile << endl;

	myfile << "WORDS_UNMATCHED_IN_GRID" << endl;
	for (int i = 0;i<MaxWords;)
	{ 
		for (int k = 0; k <= MaxOrderedWords; k++)
		{
			if (Dictionary[i]==OrderedMatchedWords[k])
			{
				i++;
				break;
			}
			else if (i == 0 && k == MaxOrderedWords)
			{
				myfile << Dictionary[i]<<endl;
				i++;
				break;
			}
			else if (k == MaxOrderedWords)
			{
				myfile << Dictionary[i]<<endl;
				i++;
				break;
			}
		}
	}
	myfile << endl;

	myfile << "NUMBER_OF_GRID_CELLS_VISITED ";
	myfile << cellsVisited << endl;
	myfile << endl;

	myfile << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED ";
	myfile << DictionaryVisits << endl;
	myfile << endl;

	myfile << "TIME_TO_POPULATE_GRID_STRUCTURE ";
	myfile << loadTime <<endl;
	myfile << endl;

	myfile << "TIME_TO_SOLVE_PUZZLE ";
	myfile << solveTime << endl;
	myfile << endl;

	myfile.close();
}