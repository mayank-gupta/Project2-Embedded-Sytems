#include <iostream>
#include <string.h>

#define MAX_FILE_NAME_LENGTH 200
using namespace std;

class Dictionary{

};

class CompDecomp{
	
	public:
		char *inputFile;
		char *outputFile;
		
		
		CompDecomp(char* , char*);
		virtual ~CompDecomp();
/*		void checkShow(){
			cout<<inputFile<<outputFile;
		}
*/		
};

class Compress: public CompDecomp{
	private:

	public:
		Compress(char* , char*);
		~Compress();
		

};

class Decompress: public CompDecomp{
	private:

	public:
		Decompress(char* , char*);
		~Decompress();
		

};

CompDecomp::CompDecomp(char *input, char *output){
	inputFile = new char[MAX_FILE_NAME_LENGTH];
	outputFile = new char[MAX_FILE_NAME_LENGTH];
	inputFile = input;
	outputFile = output;
};

CompDecomp::~CompDecomp(){
	delete inputFile;
	delete outputFile;
};

Compress:: Compress(char *input, char* output):CompDecomp(input,output){
	//Initialize dictionaries and stuff here
};

Compress:: ~Compress(){
	//Destroy dictionaries and all local data here
	
};

Decompress:: Decompress(char *input, char* output):CompDecomp(input,output){
	//Initialize dictionaries and stuff here
};

Decompress:: ~Decompress(){
	//Destroy dictionaries and all local data here
}

int main(int argc, char* argv[]){

	if((argc < 4)||((strcmp(argv[1],"-C"))&&(strcmp(argv[1],"-D")))){
		cout<<"Incorrect number of arguments to the program or incorrect arguments to the program.\nCorrect Format ::\nFor Compression => SIM -C  original.txt compressed.txt \nFor Decompression => SIM -D compressed.txt decompressed.txt\n";
		return 0;
	}

	CompDecomp* obj = new CompDecomp(argv[2],argv[3]);
//	obj->checkShow();

	return 0;
}
