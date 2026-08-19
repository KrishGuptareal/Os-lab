#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <signal.h>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 5)
	{
		cout <<"usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position>\nprovided arguments:\n";
		for(int i = 0; i < argc; i++)
			cout << argv[i] << "\n";
		return -1;
	}
	
	char *file_to_search_in = argv[1];
	char *pattern_to_search_for = argv[2];
	int search_start_position = atoi(argv[3]);
	int search_end_position = atoi(argv[4]);

    ifstream file(file_to_search_in);
    string line;
    getline(file,line);//single line file is there
    size_t pos=line.find(pattern_to_search_for);
    if(pos!=string::npos){
        cout << "["<<getpid()<<"] found at"<<pos<<"\n";
        // cout<<line.substr(pos,8)<<"\n";
    }
	else cout << "["<<getpid()<<"] didn't find\n";
	return 0;
}
