#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void MyHandler(){}

unsigned int mysleep(unsigned int nsecs){
    //set MyHandler, save previous information
    struct sigaction new_action, old_action;
    new_action.sa_handler = MyHandler;
    new_action.sa_flags = 0;
    sigemptyset(&new_action.sa_mask);
    sigaction(SIGALRM, &new_action, &old_action);

    //block SIGALRM and save current signal mask;
    sigset_t new_mask, old_mask;
    sigemptyset(&new_mask);
    sigprocmask(SIG_BLOCK, new_mask,old_mask);

    alarm(nsecs);

    sigset_t suspmask = old_mask;
    sigdelset(SIGALRM, &suspmask); //make sure SIGALRM isn't blocked
    sigsuspend(&suspmask);         //wait for anysignal to be caught

    //some signal has been caught
    unsigned int unslept = alarm(0);

    //reset
    sigaction(SIGALRM, &old_mask, NULL);
    sigprocmask(SIG_SETMASK, &old_action, NULL);
}

int main(){
    mysleep(5);
    return  0;
}
