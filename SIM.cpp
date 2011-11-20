//============================================================================
// Name        : SIM.cpp
// Author      : Mayank Gupta
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <fstream>
#include <ext/hash_map>
#include <sstream>
#include <cstdlib>
//#include <boost/algorithm/string.hpp>


#define MAX_FILE_NAME_LENGTH 200
#define DICTIONARY_SIZE 4
#define ERROR_CODE 0
#define MAX_ELEMENTS 1000
#define SUCCESS 1

using namespace std;
using namespace __gnu_cxx;

struct eqstr{
	bool operator()( const char* s1,  const char* s2) const
	{
		return strcmp(s1, s2) == 0;
	}
};

/*class Dictionary{

public:
	hash_map<const char*, const char*, hash<const char* >, eqstr> entries;
};*/

/*struct values{
	int index;
	int count;
};*/
class CompDecomp{

public:
	char *inputFileName;
	char *outputFileName;
	ifstream inputFile;
	ofstream outputFile;
	hash_map<const char*, int, hash<const char* >, eqstr> entries;
	CompDecomp(char* , char*);
	virtual ~CompDecomp();
	virtual int runAlgorithm()=0;
	/*		void checkShow(){
			cout<<inputFile<<outputFile;
		}
	 */
};

class Compress: public CompDecomp{

private:
	int findDictionary(string inputFromFile[], int);
	int findDifference(char *toCompress);
	int implementOneBitMismatch(char* toCompress, char* dictionaryEntry );
	int implementTwoBitConsecMismatch(char * , char*);
	int implementFourBitMismatch(char*, char*);
	int writeToFile(char*);
	//Dictionary dict;
public:
	Compress(char* , char*);
	~Compress();
	int runAlgorithm();

};

class Decompress: public CompDecomp{
private:
	//Dictionary extractDictItems();
	int deCompressByDictEntry(char* );
	int deCompressBySingleBitMismatch(char*);
	int deCompressByTwoBitMismatch(char*);
	int deCompressByFourBitMismatch(char*);
	//Dictionary dict;
	int writeToFile(char*);
public:
	Decompress(char* , char*);
	~Decompress();
	int runAlgorithm();


};

CompDecomp::CompDecomp(char *input, char *output){
	inputFileName = new char[MAX_FILE_NAME_LENGTH];
	outputFileName = new char[MAX_FILE_NAME_LENGTH];
	inputFileName = input;
	outputFileName = output;
	inputFile.open(inputFileName);

};

CompDecomp::~CompDecomp(){
	inputFile.close();
	delete inputFileName;
	delete outputFileName;
};

Compress:: Compress(char *input, char* output):CompDecomp(input,output){
	//Initialize dictionaries and stuff here
};

Compress:: ~Compress(){
	//Destroy dictionaries and all local data here

};

int Compress::runAlgorithm(){

	//find dictionary items
	string line;
	int i = 0;
	string itemsInFile[MAX_ELEMENTS];
	//string space;
	if(!inputFile.is_open()){
		cout<<__LINE__<<" Cannot open input file.\n";
		return ERROR_CODE;
	}

	if(!getline(inputFile,line)){
		cout<<__LINE__<<" Incorrect format.\n";
		//cout<<line<<endl;
		return ERROR_CODE;
	}
	//stringstream parser (stringstream ::in|stringstream ::out)
	//parser<<line<<space;
	//itemsInFile[i++] = line;
	//cout<<"Element "<<i<<" => "<<itemsInFile[i]<<endl;

	do{
		//Fill array then pass that as argument to find dictionary function
		/*stringstream parser (stringstream ::in|stringstream ::out);
			parser<<line<<space;*/
		itemsInFile[i++] = line.erase(line.find_last_not_of(" \n\r\t")+1);
		;
		cout<<"Element "<<i<<" => "<<itemsInFile[i]<<endl;


	}while(getline(inputFile,line));
	//string endOfLine = "\0";

	//itemsInFile[i] = itemsInFile[i] + endOfLine;


	for(int j = 0;j <i;j++){
		cout<<"Element "<<j<<" => "<<itemsInFile[j]<<endl;
	}
	//cout<<"Print new line "<<itemsInFile[i];
	if(findDictionary(itemsInFile,i)==0){
		cout<<__LINE__<<" Problem in finding dictionary.\n";
	}
	//find difference
	//Encode for each item
	//write to file
	return 1;

}

int Compress::findDictionary(string itemsInFile[MAX_ELEMENTS], int noOfElements){

	hash_map< const char*, int, hash<const char*>, eqstr> localMap;
	hash_map< const char*,int,hash<const char*>,eqstr >:: iterator checkEntry;
	//struct values val;
	int count = 1;
	//char* tempElement;
	//cout<<"No. of elements "<<noOfElements<<endl;
	//tempElement = new char[200];

	//Setting count for each entry
	for(int i=0;i<noOfElements;i++){
		//For each element check if it is there in hash_map
		//strcpy(tempElement,itemsInFile[i].c_str());
		//strcat(tempElement,"\n");
		//cout<<"Element "<<i<<" "<<tempElement<<endl;
		checkEntry = localMap.find(itemsInFile[i].c_str());

		if(checkEntry == localMap.end()){
			//Means not found
			//val.count = 1;
			//val.index = localMap.size();
			localMap[itemsInFile[i].c_str()] = 1;
			cout<<" New entry => "<<localMap[itemsInFile[i].c_str()]<<endl;
		}else{
			//Means found
			cout<<"Iterator "<<checkEntry->first;
			count = localMap[itemsInFile[i].c_str()]+1;
			//val.index = entries[itemsInFile[i].c_str()].index;
			localMap[itemsInFile[i].c_str()] = count;
			cout<<" Old Entry  => "<<localMap[itemsInFile[i].c_str()]<<endl;
		}
		//delete tempElement;
		//tempElement = NULL;
		//tempElement = new char[200];

	}
	//delete tempElement;
	cout<<"Size of the array generated "<<localMap.size()<<endl;
	int max = 1;

	for(checkEntry = localMap.begin(); checkEntry != localMap.end(); checkEntry++){
		cout<<"Key "<<checkEntry->first<<" :: value "<<checkEntry->second<<endl;
	}

	char *element;
	//Finding the most frequent ones
	for (int i =0;i <DICTIONARY_SIZE; i++){

		element= new char[33];
		max = 0;
		cout<<i<<endl;
		for(checkEntry = localMap.begin(); checkEntry != localMap.end(); checkEntry++){
			//		cout<<checkEntry->first<<" "<<checkEntry->second<<endl;

			//cout<<"From map "<<checkEntry->first<<endl;
			if(localMap[checkEntry->first] >max){
				//delete element;
				//element = new char[100];
				strcpy(element,checkEntry->first);
				//element = checkEntry->first;
				//cout<<"Element "<<element<<" from map "<<checkEntry->first<<endl;
				max = localMap[checkEntry->first];


			}
			cout<<i<< "th element is "<<element<<endl;
		}
		entries[element] = i;
		localMap.erase(element);
		cout<<"Size of the array generated "<<localMap.size()<<endl;
		//delete element;

	}
	//delete element;
	cout<<"Size of dictionary "<<entries.size()<<endl;
	for(checkEntry = entries.begin(); checkEntry != entries.end(); checkEntry++){
		cout<<checkEntry->first<<endl;
	}
	return SUCCESS;
}

Decompress:: Decompress(char *input, char* output):CompDecomp(input,output){
	//Initialize dictionaries and stuff here
};

Decompress:: ~Decompress(){
	//Destroy dictionaries and all local data here
}

int Decompress::runAlgorithm(){
	return 1;
}

int main(int argc, char* argv[]){

	if((argc < 4)||((strcmp(argv[1],"-C"))&&(strcmp(argv[1],"-D")))){
		cout<<"Incorrect number of arguments to the program or incorrect arguments to the program.\nCorrect Format ::\nFor Compression => SIM -C  original.txt compressed.txt \nFor Decompression => SIM -D compressed.txt decompressed.txt\n";
		return 0;
	}

	CompDecomp* obj;
	if(!strcmp(argv[1],"-C")){
		obj = new Compress(argv[2],argv[3]);
	}else if(!strcmp(argv[1],"-D")){
		obj = new Decompress(argv[1], argv[2]);
	}

	obj->runAlgorithm();
	//	obj->checkShow();

	return 0;
}

