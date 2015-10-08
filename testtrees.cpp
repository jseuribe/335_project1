/********************************************************************************************************************************************************
 Title: testTrees
 Author: Jose Antonio Uribe
 Created: October 15, 2014
 Purpose:This program fills up a tree of your choice(BST, AVL, LazyBST, LazyAVL) and tests it. A myriad of statistics are given, for that tree.
 Build with: g++ -o testTrees testTrees.cpp
Remember! All header files below contain their implementations!
********************************************************************************************************************************************************/


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>
#include "sequenceMap.h"
#include "BSTDNA.h"
#include "AVLDNA.h"
#include "BSTLAZYDNA.h"
#include "AVLLAZYDNA.h"
using namespace std;

void fileCheck(ifstream& file);//checks if the file name is valid.

template <class T>
void fillTree(T& root, ifstream& file);//fills the tree using the file stream.

bool checkForLegality(string thisLine);//checks if a string ends in //; a legal string to be used.

template <class T>
void createSequenceMaps(BinarySearchTree& root, string thisLine);//creates a sequenceMap using the data in thisLine

template <class T>
void evacuateEveryOtherItem(T& root, string fileName);

template <class T>
void querySequences(T root, string fileName);//Queries using the file name specified by fileName

void flipString(string& tobeFlipped);

float calculateRatio(float n, float depth);//calculates the ratio of avg depth/log2(n)

int main( int argc, char *argv[] )
{
	float n = 0, depth = 0;
	string fileName = argv[1];
	string query = argv[2];
	sequenceMap queryContainer;
	ifstream rebase210(fileName);
	fileCheck(rebase210);

	//If the parameter matches the if statement, that version of the code will run.
	string datatype = argv[3];
	if(datatype == "BST" ){
	   BinarySearchTree database;
	   fillTree<BinarySearchTree>(database, rebase210);
	   cout << "calls to insert: " << database.returnInsertionCalls() << endl;
	   n = database.numberOfNodes();
	   cout << "n, number of nodes is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   cout << "Querying using the specified file..." << endl;
	   querySequences<BinarySearchTree>(database, query);
	   //database.resetContainsCalls();
	   cout << "Removing every other sequence in your specified file " << endl;
           evacuateEveryOtherItem<BinarySearchTree>(database, query); 
	   n = database.numberOfNodes();
	   cout << "n, number of nodes after deletion is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth, after removal, is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   querySequences<BinarySearchTree>(database, query);
	}
	else if(datatype == "AVL" ){ 
	   AvlTree database;
	   fillTree<AvlTree>(database, rebase210);
           cout << "calls to insert: " << database.returnInsertionCalls() << endl;
	   n = database.numberOfNodes();
	   cout << "n, number of nodes is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   cout << "Querying using the specified file..." << endl;
	   querySequences<AvlTree>(database, query);
	   database.resetContainsCalls();
	   cout << "Removing every other sequence in your specified file " << endl;
           evacuateEveryOtherItem<AvlTree>(database, query);
	   n = database.numberOfNodes();
	   cout << "n, number of nodes after deletion is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth, after removal, is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   cout << "items in the tree: " << endl;
	   querySequences<AvlTree>(database, query);
	}
	else if(datatype == "LazyBST" ) {
	   LazyBinarySearchTree database;
	   fillTree<LazyBinarySearchTree>(database, rebase210);
	   cout << "calls to insert: " << database.returnInsertionCalls() << endl;
           n = database.numberOfNodes();
	   cout << "n, number of nodes is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   cout << "Querying using the specified file..." << endl;
	   querySequences<LazyBinarySearchTree>(database, query);
	   database.resetContainsCalls();
	   cout << "Removing every other sequence in your specified file " << endl;
           evacuateEveryOtherItem<LazyBinarySearchTree>(database, query);
	   n = database.numberOfNodes();
	   cout << "n, number of nodes after deletion is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth, after removal, is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   querySequences<LazyBinarySearchTree>(database, query);
	}
	else if(datatype == "LazyAVL") {
	   LazyAvlTree database;
	   fillTree<LazyAvlTree>(database, rebase210);
           cout << "calls to insert: " << database.returnInsertionCalls() << endl;
	   n = database.numberOfNodes();
	   cout << "n, number of nodes is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   cout << "Querying using the specified file..." << endl;
           cout << "average depth is " << n << "/" << "logbase2(" << n << ") =" << calculateRatio(n, depth) << endl;
	   cout << "Querying using the specified file..." << endl;
	   querySequences<LazyAvlTree>(database, query);
	   database.resetContainsCalls();
	   cout << "Removing every other sequence in your specified file " << endl;
           evacuateEveryOtherItem<LazyAvlTree>(database, query);
	   n = database.numberOfNodes();
	   cout << "n, number of nodes after deletion is: " << n << endl;
	   depth = database.depth();
	   cout << "the average depth, after removal, is: " << depth/n << endl;
           cout << "The ratio of the average depth to log2("<< n << ") is: "  << calculateRatio(n, depth) << endl;
	   querySequences<LazyAvlTree>(database, query);
	}
	else cout << "Parameter flag not valid" << endl;
	
	rebase210.close();
	return 0;
}

//simply put, this function will check if the file is within the same directory as the executable.
//Otherwise, the program will end, prompting the changing of location of the file.
void fileCheck(ifstream& file)
{
    if(file.fail())
    {
        cerr << "Input file could not be opened. Check if the file is in the same directory"
             << " as the executable.\n";
        exit(1);
    }
}

//Using the already opened file stream, this will fill up the tree with the data inside
template <class T>
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

//A simple check. Since we parse files line by line, we will check if the string ends in //, the accepted format of the recog. sequence.
bool checkForLegality(string thisLine)
{
    if(thisLine[thisLine.size() - 2] == '/' && thisLine[(thisLine.size() - 1)] == '/') return true;
    else return false;
}

//Using a stack, we create, then insert, a sequenceMap for the current line obtained from filltree
template <class T>
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
   }while(!(thisLine[currentPos-1] == '/' && thisLine[currentPos] == '/'));
}

//Exactly what its name is.
void flipString(string& tobeFlipped)
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

//Using a file, we will parse through the tree, searching for the sequences.
//Assumed is a file with only sequences, and an empty line at the end.
template <class T>
void querySequences(T root, string fileName)
{
        int successes = 0;
	ifstream queries(fileName);
	fileCheck(queries);

	string current;
	sequenceMap container;
	while(queries >> current)
	{
		container.updateRecognitionSequence(current);

		if(root.contains(container))successes++;
	}
	int recursiveCalls = 0;
	recursiveCalls = root.returnContainsCalls();
	cout << "Number of recursive accesses: " << recursiveCalls <<endl;	

	cout << "Number of successes: " << successes << endl;
	queries.close();
}

//This will evacuate every other item. If the number is NOT divisible by 2, that is a sequence we will remove
template <class T>
void evacuateEveryOtherItem(T& root, string fileName)
{
	root.resetContainsCalls();
	ifstream queries(fileName);
	fileCheck(queries);
	int counter = 0;
	string current;
	sequenceMap container;
	while(queries >> current)
	{
		//cout << "item to be evacuated: " << current << endl;
		if(!root.isEmpty())
		{
			container.updateRecognitionSequence(current);
			if(counter % 2 != 0)root.remove(container);
			counter++;
		}
	}
	
	queries.close();
	cout << "Remove calls made: " << root.returnRemoveCalls() << endl;
        cout << "Successful removes: " << root.returnSuccessfulRemoves() << endl;
}

//The ratio is calculated.
float calculateRatio(float n, float depth)
{
	float averageDepth = depth/n;
 	float logbase2n = log(n);
	logbase2n = logbase2n/log(2);
	float ratio = averageDepth/logbase2n;
	return ratio;
}

