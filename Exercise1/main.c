#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>

#define MAXBG 20

char **get_input(char *input);
char check_pipe(char * input);
int cd(char *path);
void current_dir();
void print_user();
void print_date();
void print_help();
void signalHandlerChild(int s);
void signalHandlerInterrupt(int s);
void signalHandlerStp(int s);
char checkBackground(char* command);
char execBackground(char* command);

int pid = 0;
int lastStoppedProcess = 0;
int bgProcessess[MAXBG];
int backgroundFlag = 0;
pid_t child_pid, child_pid;

int main()
{
    char **command;
    char *input;

    int stat_loc;


    for(int i = 0  ; i < MAXBG; i++){
        bgProcessess[i] = 0;
    }

    hello_message();

    struct sigaction saChild;
    saChild.sa_handler = signalHandlerChild;
    saChild.sa_flags = 0;
    sigemptyset(&saChild.sa_mask);

    struct sigaction saI;
    saI.sa_handler = signalHandlerInterrupt;
    saI.sa_flags = 0;
    sigemptyset(&saI.sa_mask);

    struct sigaction saStp;
    saStp.sa_handler = signalHandlerStp;
    saStp.sa_flags = 0;
    sigemptyset(&saStp.sa_mask);


    sigaction(SIGINT, &saI, NULL);

    sigaction(SIGTSTP, &saStp, NULL);

    sigaction(SIGCHLD, &saChild, NULL);


    while (1) {
        printf("\n");
        print_user();
        printf(":");
        current_dir();

        input = readline(" > ");
        command = get_input(input);


        if(!command[0]){
            free(input);
            free(command);
            continue;
        }

        if(strcmp(command[0], "cd")==0){
            if(cd(command[1]) <0){
                perror(command[1]);
            }
            continue;
        }
        if(strcmp(command[0], "exit")==0){
            char exityn =NULL;
            int stop =0;

            while(stop == 0){
                printf("Do you really want to quit (y/n)? ");
                scanf("%s",&exityn);
                if(strcmp(&exityn,"y")==0){
                    exit(0);//or maybe kill or sigstop sigkill?
                }
                if(strcmp(&exityn,"n")==0){
                    stop =1;
                }
            }
            continue;
        }

        if(strcmp(command[0], "help")==0){
            print_help();
            continue;
        }
        if(strcmp(command[0], "date")==0){
            print_date();
            continue;
        }
        checkBackground(*command);
        if(backgroundFlag == 0){
            child_pid = fork();
            for(int i = 0; i < MAXBG; i++){
               if(bgProcessess[i] == 0){
                   bgProcessess[i] = child_pid;
                   break;
               }
              }
            if (child_pid < 0) {
                perror("Fork failed");
                exit(1);
            }
            if (child_pid == 0) {
                /* Never returns if the call is successful */
                if (execvp(command[0], command) < 0) {
                    perror(command[0]);
                }
            } else {
                waitpid(child_pid, &stat_loc, WUNTRACED);
                // using WUNTRACED will produce zombie and possible deadlock of the parent process when running e.g. SIGSTOP as child
                // https://stackoverflow.com/questions/33508997/waitpid-wnohang-wuntraced-how-do-i-use-these/34845669
                //
            }

            free(input);
            free(command);
        }
        else if (backgroundFlag == 1) {
            kill(lastStoppedProcess, SIGCONT);
            for(int i = 0; i < MAXBG; i++){
               if(bgProcessess[i] == 0){
                   bgProcessess[i] = lastStoppedProcess;
                   break;
               }
            }
            child_pid = fork();

            if (child_pid < 0) {
                perror("Fork failed");
                exit(1);
            }
            if (child_pid == 0) {
                /* Never returns if the call is successful */
                if (execvp(command[0], command) < 0) {
                    perror(command[0]);
                }

            } else {
                printf("%i\n", child_pid);
                waitpid(child_pid, &stat_loc, WNOHANG);
                // using WUNTRACED will produce zombie and possible deadlock of the parent process when running e.g. SIGSTOP as child
                // https://stackoverflow.com/questions/33508997/waitpid-wnohang-wuntraced-how-do-i-use-these/34845669
                //
            }
                /*if(child_pid == 0){
                setpgid(0, 0);
                //printf(child_pid, "\n");
                if (execvp(command[0], command) < 0) {
                    perror(command[0]);
                }
            }*/
        }
    }
    return 0;
}

int cd(char* path){
    return chdir(path);
}

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;


    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;
    return command;
}

void signalHandlerChild(int s){
    for(int i = 0; i < MAXBG; i++){
        if(bgProcessess[i] != 0){
            printf("terminiert: %i", bgProcessess[i], "\n");
        }
        if(waitpid(bgProcessess[i], NULL, WNOHANG)){
            bgProcessess[i] = 0;
        }
    }
}

void signalHandlerInterrupt(int s){
    fprintf("CAUGHT", SIGINT,"\n");
    if(child_pid == 0) {
        //logout();
        return;
    }
    kill(child_pid, SIGINT);
}

void signalHandlerStp(int s){
    fprintf("CAUGHT", SIGTSTP,"\n");
    if(child_pid == 0) return;
    kill(child_pid, SIGTSTP);
    lastStoppedProcess = child_pid;
    //printf("Process with ID is done: %i", lastStoppedProcess, "\n");
}

char checkBackground(char *command)
{

    for(int j = 0; j < 1000; j++){
        if(command[j] == '&'){
            command[j] = '/0';
            backgroundFlag = 1;
            break;
        }else
        {
            backgroundFlag = 0;
        }
    }
}


void hello_message(){
    printf("\n\n\n\n******************"
           "************************");
    printf("\n\n\n\t****MY MINISHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
           "***********************");
    //char* username = getenv("USER");
    //printf("\n\n\nUSER is: @%s", username);
    printf("\n\nTo exit write \"exit\" ");
    printf("\n");
    sleep(1);
}
void current_dir(){
    char dir[100];
    getcwd(dir, sizeof(dir));

    printf("%s",dir);

}
void print_user(){
    char* username = getenv("USER");
    printf("%s",username);
}
void print_date(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
void print_help(){
    printf("to be filled..\n");
}
