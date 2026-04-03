/*
 * sched_test.c
 *
 * Run:
 *   ./sched_test <num-hogs> <runtime-seconds>
 *
 * Required behavior:
 *   1) fork+exec CPU hogs first
 *   2) fork+exec interactive last (passing runtime-seconds)
 *   3) waitpid() for interactive process
 *   4) kill hogs
 *   5) reap remaining children
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_hogs> <runtime_seconds>\n", argv[0]);
        return 1;
    }

    // TODO
    /*The core idea is that it needs to fork all the hogs and the one interactive process so that they run concurrently. 
    It then waits for the interactive process to finish, followed by killing and reaping (waiting on) all the CPU hogs. 
    */
    int numHogs = atoi(argv[1]);
    //int secondsRun = atoi(argv[2]);

    
    //fork and exec all CPU hogs first
    //int isChild = 0;
    char *cmd = "./cpu_hog";
    char *hogTerms[] = {"./cpu_hog", NULL};
    pid_t id[numHogs];
    pid_t ogLastID = id[numHogs-1];

    for(int i = 0; i<numHogs; i++){
        id[i] = fork();
        if(id[i] == 0){//child
            //isChild = 1;
            //id = i;
            //printf("hog creating...\n");
            execv(cmd, hogTerms);
            //printf("hog created\n");
            //i = numHogs;
        }
    }
    
    //how to ensure all hogs are created before parent moves on?
    //wait();
    /*int *status;
    waitpid(id[numHogs-1], status, WNOHANG);
    while(*status == -1){//wait for last hog to start
        ;
    }
    */
    if(numHogs>0){
        while(id[numHogs-1] == ogLastID){//wait for hogs to start
            ;
        }
    }


    //THEN the 1 interactive process last
    char *interCmd = "./interactive";
    char *interTerms[] = {"./interactive", argv[2], NULL};
    pid_t interID = fork();
    if(interID == 0){//new child
        //isChild = 1;
        //printf("interactive creating...\n");
        execv(interCmd, interTerms);
        //printf("interactive created\n");
        exit(0);
    }
        
    //wait() for interactive process to finish
    waitpid(interID, NULL, 0);
    //printf("finished waiting for interactive\n");

    //kill() and wait() hogs
    for(int i = 0; i<numHogs; i++){
        kill(id[i], SIGKILL);
        //printf("hog killed\n");
        wait(NULL);
        //printf("hog reaped\n");
    }

    return 0;
}