/********************************************************************************************************************************************************
 Title: queryTrees
 Author: Jose Antonio Uribe
 Created: October 15, 2014
 Purpose:This program fills up a tree of your choice(BST, AVL, LazyBST, LazyAVL) and allows you to search it for sequences.
 Build with: g++ -o queryTrees queryTrees.cpp
Remember! All header files below contain their implementations!
********************************************************************************************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include "sequenceMap.h"
#include "BSTDNA.h"
#include "AVLDNA.h"
#include "BSTLAZYDNA.h"
#include "AVLLAZYDNA.h"

void fileCheck(ifstream& file);

template <class T>
void fillTree(T& root, ifstream& file);

bool checkForLegality(string thisLine);

template <class T>
void createSequenceMaps(T& root, string thisLine);

void flipString(string& tobeFlipped);

void newLine();//gets rid of any unecessary characters from input

int main( int argc, char *argv[])
{
	string fileName = argv[1];
	string query;
	char again;
	sequenceMap queryContainer;
	ifstream rebase210(fileName);
	fileCheck(rebase210);



	string parameter = argv[2];
	if(parameter == "BST" ){
	   BinarySearchTree database;
	   fillTree<BinarySearchTree>(database, rebase210);
	   do{
	   cout << "query the tree: ";
	   //database.printTree();
	   cin >> query;
	   //newLine();
	   queryContainer.updateRecognitionSequence(query);
	   database.find(queryContainer);
	   cout << "Enter Y to query again; otherwise, enter anything else to exit: ";
           cin >> again;
           newLine();
	   }while(again == 'Y');
	}
	else if(parameter == "AVL" ){ 
	   AvlTree database;
	   fillTree<AvlTree>(database, rebase210);
	   do{
	   cout << "query the tree: ";
	   cin >> query;
	   newLine();
	   queryContainer.updateRecognitionSequence(query);
	   database.find(queryContainer);
	   cout << "Enter Y to query again; otherwise, enter anything else to exit: ";
           cin >> again;
           newLine();
	   }while(again == 'Y');
	}
	else if(parameter == "LazyBST" ) {
	   LazyBinarySearchTree database;
	   fillTree<LazyBinarySearchTree>(database, rebase210);
	   do{
	   cout << "query the tree: ";
	   cin >> query;
           newLine();
	   queryContainer.updateRecognitionSequence(query);
	   database.find(queryContainer);
           cout << "Enter Y to query again; otherwise, enter anything else to exit: ";
           cin >> again;
	   newLine();
	   }while(again == 'Y');
	}
	else if(parameter == "LazyAVL") {
           do{
	   LazyAvlTree database;
	   fillTree<LazyAvlTree>(database, rebase210);
	   cout << "query the tree: ";
	   cin >> query;
	   newLine();
	   queryContainer.updateRecognitionSequence(query);
	   database.find(queryContainer);
           cout << "Enter Y to query again; otherwise, enter anything else to exit: ";
           cin >> again;
	   newLine();
	   }while(again == 'Y');
	}
	else cout << "Parameter flag not valid" << endl;
	
	rebase210.close();
	return 0;
}


void fileCheck(ifstream& file)
//simply put, this function will check if the file is within the same directory as the executable.
//Otherwise, the program will end, prompting the changing of location of the file.
{
    if(file.fail())
    {
        cerr << "Input file could not be opened. Check if the file is in the same directory"
             << " as the executable.\n";
        exit(1);
    }
}

template <class T>
//Using the already opened file stream, this will fill up the tree with the data inside
void fillTree(T& root, ifstream& file)
{
    string currentLine;
    bool firstLineFound = 0;
    while(file>>currentLine)
    {
      firstLineFound = checkForLegality(currentLine);

      if(firstLineFound){
	createSequenceMaps(root, currentLine);
      }
    }

}

bool checkForLegality(string thisLine)
//A simple check. Since we parse files line by line, we will check if the string ends in //, the accepted format of the recog. sequence.
{
    if(thisLine[thisLine.size() - 2] == '/' && thisLine[(thisLine.size() - 1)] == '/') return true;
    else return false;
}

template <class T>
//Using a stack, we create, then insert, a sequenceMap for the current line obtained from filltree
void createSequenceMaps(T& root, string thisLine)
{
    int currentPos = 0;
    stack<char> acronym;
    acronym.push(thisLine[currentPos]);//We insert the string character by character.
    currentPos++;
    while(!(acronym.top() == '/'))//Until we spot a /, we will keep inserting characters into our stack
    {
	acronym.push(thisLine[currentPos]);
	currentPos++;
    }
    acronym.pop();//We'll pop the / that we received at the end of our while loop.
    string acronymString;
    while(!(acronym.empty()))//We pop our string out; it will be backwards. Bear with me.
    {
	acronymString += acronym.top();
	acronym.pop();
    }

    flipString(acronymString);//We will flip the string obtained from the stack.

    string sequenceKey;
    sequenceMap current;
    current.updateEnzyme_Acronyms(acronymString);//The acronym obtained from the beginning is appended to all sequences

    do{
        //We will search for recognition sequences, up until the final // is encountered.
	if(!(thisLine[currentPos] == '/' && thisLine[currentPos+1] == '/')) acronym.push(thisLine[currentPos]);
	else break;
	currentPos++;
    	while(!(acronym.top() == '/'))//We will search for recognition sequences, up until the final // is encountered.
    	{
		acronym.push(thisLine[currentPos]);
                currentPos++;  
    	}
        acronym.pop();//After we find a recognition sequence, we will pop the final / out before the next string.
	while(!(acronym.empty()))
        {
		sequenceKey += acronym.top();
		acronym.pop();
        }
	flipString(sequenceKey);//We flip after we pop.
	current.updateRecognitionSequence(sequenceKey);//We will insert the obtained sequence into an object
	root.insert(current);//it will be inserted into the tree.
	sequenceKey.clear();
   }while(!(thisLine[currentPos-1] == '/' && thisLine[currentPos] == '/'));//And this code will run until a // is encountered.
}

void flipString(string& tobeFlipped)
//Does exactly what you think it does.
{
    char next;
    string newString;
    for(int i = tobeFlipped.size()-1; i >= 0 ; i--)
    {
	next = tobeFlipped[i];
	newString += next;
    }
    tobeFlipped = newString;
}

void newLine()
//newLine makes sure any unecessary characters are not read.
//EX: if the program asks for n, and the user enters "name name name"
//It will only read n and discard the rest.
{
    char symbol;

    do
    {
        cin.get(symbol);
    } while( symbol != '\n');
}

