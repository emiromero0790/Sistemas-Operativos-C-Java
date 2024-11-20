#include <stdio.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(){
    pid_t pid = fork();

    if(pid == 0){
        //Proceso hijo
        printf("Proceso hijo con PID: %d\n", getpid());

    } else{
        //Proceso padre
        //wait(NULL);
        printf("Proceso padre con PID: %d, el hijo terminó.\n", getpid());
    }
    return 0;
}