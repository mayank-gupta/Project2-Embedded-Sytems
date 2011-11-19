#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){

	if((argc < 4)||(!strcmp(argv[1],"-C"))&&(!strcmp(argv[1],"-D"))){
		cout<<"Incorrect arguments to the program.\n Correct Format :: SIM -C  original.txt compressed.txt \n Or SIM -D compressed.txt decompressed.txt";
		return 0;
	}
	return 0;
}
