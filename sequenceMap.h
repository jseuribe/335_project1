/********************************************************************************************************************************************************
 Title: sequenceMap
 Author: Jose Antonio Uribe
 Created: October 15, 2014
 Purpose:A datatype that holds a key, a recognition Sequence, and a vector of strings, the acronyms associated with the sequence.
 Build with: g++ -o programname "Your_Main_Function_Holding_File_Here".cpp
 Given that this is simply a header with implementations inside, just include in your main function file.
********************************************************************************************************************************************************/

#ifndef SEQUENCEMAP_H
#define SEQUENCEMAP_H

using namespace std;

class sequenceMap
{
    public:
        sequenceMap();
        sequenceMap(const sequenceMap& source);
	sequenceMap(sequenceMap && source);
        sequenceMap& operator=(const sequenceMap& source);
        bool operator<( sequenceMap rhs);
        void setValues(string inputSequence, vector<string>inputEnzymes);
        void updateRecognitionSequence(string inputSequence);
        void updateEnzyme_Acronyms(string newAcronym);
        string& getRecognitionSequence();
        vector<string> getAllEnzymeAcronyms();
        void mergeObjects(sequenceMap& source);
        void setRecognitionSequence(string source);
        void setEnzyme_Acronyms(vector<string> source);
	void print();
        void printAcronyms();
	friend ostream& operator<<(ostream& out, sequenceMap& c);
        //~sequenceMap(); Most likely not necessary. Need to address eventually.
    private:
        string recognition_Sequence;
        vector<string> enzyme_Acronyms;

};

sequenceMap::sequenceMap()
{

}

sequenceMap::sequenceMap(const sequenceMap& source)
{
    if( source.recognition_Sequence.length() == 0 )
    {
        //recognition_Sequence = "";
    }
    else
    {
        this->enzyme_Acronyms = source.enzyme_Acronyms;
        this->recognition_Sequence = source.recognition_Sequence;
    }
}

sequenceMap::sequenceMap(sequenceMap && source)
{
    recognition_Sequence = source.recognition_Sequence;
    source.recognition_Sequence = "";
    
    while( !source.enzyme_Acronyms.empty() )
    {
        int i = source.enzyme_Acronyms.size() - 1;
        this->enzyme_Acronyms.push_back( source.enzyme_Acronyms[i] );//Check if this works.
        source.enzyme_Acronyms.pop_back();
        i--;
    }
}

sequenceMap& sequenceMap::operator=(const sequenceMap& source)
{
    if( this != &source )
    {
        this->enzyme_Acronyms = source.enzyme_Acronyms;
        this->recognition_Sequence = source.recognition_Sequence;
        return *this;
    }
    else return *this;
}

void sequenceMap::setValues(string inputSequence, vector<string>inputEnzymes)
{
    this->recognition_Sequence = inputSequence;
    this->enzyme_Acronyms = inputEnzymes;
}

//If this has been called, source and this sequenceMap share the same sequence. As such, source's acronyms are all loaded into
//this sequenceMap
void sequenceMap::mergeObjects(sequenceMap& source)
{
    while( !source.enzyme_Acronyms.empty() )
    {
        int i = source.enzyme_Acronyms.size() - 1;
        this->enzyme_Acronyms.push_back( source.enzyme_Acronyms[i] );//Check if this works.
        source.enzyme_Acronyms.pop_back();
        i--;
    }
}

bool sequenceMap::operator<( sequenceMap rhs)
{  
    if(recognition_Sequence.compare(rhs.recognition_Sequence) == 0) return false;
    else if(recognition_Sequence.compare(rhs.recognition_Sequence) < 0) return true;
    else if(recognition_Sequence.compare(rhs.recognition_Sequence) > 0 ) return false;
}

void sequenceMap::setRecognitionSequence(string source)
{
    this->recognition_Sequence = source;
}

void sequenceMap::setEnzyme_Acronyms(vector<string> source)
{
    this->enzyme_Acronyms = source;
}

void sequenceMap::updateRecognitionSequence(string inputSequence)
{
    this->recognition_Sequence = inputSequence;
}

void sequenceMap::updateEnzyme_Acronyms(string newAcronym)
{
    enzyme_Acronyms.push_back(newAcronym);
}

string& sequenceMap::getRecognitionSequence()
{
    return recognition_Sequence;
}

vector<string> sequenceMap::getAllEnzymeAcronyms()
{
    return this->enzyme_Acronyms;
}

ostream& operator<<(ostream& out, sequenceMap& c)
{
    out << c.recognition_Sequence;
    return out;
}

void sequenceMap::print()
{
	cout << recognition_Sequence << endl;
}

void sequenceMap::printAcronyms()
{
    cout << "Enzyme Acronyms associated with: " << recognition_Sequence << endl;
     if(enzyme_Acronyms.size() != 0) {
	for(int i = 0; i < enzyme_Acronyms.size(); i++)
	{
	    cout << enzyme_Acronyms[i] << endl;
	}
     }
}
#endif // SEQUENCEMAP_H
