#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstdio>

using namespace std;



void solve(int l,int r,int threshold,char *file_to_search_in,char *pattern_to_search_for){
    pid_t my_pid=getpid();
    cout << "[" << my_pid << "] start position = " << l << " ; end position = " << r << "\n";
    if(r-l+1<=threshold){
        /*
            create child process-->exec
        */
        pid_t pid=fork();
        
        if(pid<0){
            perror("fork");
            exit(1);
        }
        else if(pid>0){
            //parent process
            pid_t searcher_pid=pid;
            cout << "[" << my_pid << "] forked searcher child " << searcher_pid << "\n";
            wait(NULL);
            cout << "[" << my_pid << "] searcher child returned \n";
        }
        else{
            //child process now search
            char l_str[20],r_str[20];
            sprintf(l_str, "%d", l);
            sprintf(r_str, "%d", r);
            execl("./part2_searcher.out","./part2_searcher.out", file_to_search_in,pattern_to_search_for,l_str,r_str,NULL);
            perror("execl");
            exit(1);
        }
        return;
    }
    int mid=(l+r)/2;
    pid_t left=fork();
    if(left<0){
        perror("fork");
        exit(1);
    }
    else if(left>0){
        cout << "[" << my_pid << "] forked left child " << left << "\n";
    }
    else{
        //child
        solve(l,mid,threshold,file_to_search_in,pattern_to_search_for);
        exit(0);
    }

    pid_t right=fork();
    if(right<0){
        perror("fork");
        exit(1);
    }
    else if(right>0){
        cout << "[" << my_pid << "] forked right child " << right << "\n";
    }
    else{
        //child
        solve(mid+1,r,threshold,file_to_search_in,pattern_to_search_for);
        exit(0);
    }
    waitpid(left,NULL,0);
    cout << "[" << my_pid << "] left child returned\n";
    waitpid(right,NULL,0);
    cout << "[" << my_pid << "] right child returned\n";


}
int main(int argc, char **argv)
{
	if(argc != 6)
	{
		cout <<"usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position> <max-chunk-size>\nprovided arguments:\n";
		for(int i = 0; i < argc; i++)
			cout << argv[i] << "\n";
		return -1;
	}
	char *file_to_search_in = argv[1];
	char *pattern_to_search_for = argv[2];
	int search_start_position = atoi(argv[3]);
	int search_end_position = atoi(argv[4]);
	int max_chunk_size = atoi(argv[5]);
	
	
	
    solve(search_start_position,search_end_position,max_chunk_size,file_to_search_in,pattern_to_search_for);
	
	// cout << "[" << my_pid << "] received SIGTERM\n"; //applicable for Part III of the assignment

	return 0;
}
