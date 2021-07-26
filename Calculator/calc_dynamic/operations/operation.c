#include "operation.h"
#include "../interface/gotoxy.h"
#include "../interface/keyboard.h"
#include "../interface/clearbuf.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <dlfcn.h>
#include <dirent.h>

static long long (*func_ptr[4])(const long long int op1, const long long int op2);
static void *handle[4];
static unsigned int count_library = 0;

void plugin(void){
    DIR *dir = NULL;
    struct dirent *entry;

    const char *pathplug = "./libs_dynamic";
    const char *buttons = "-+/*";
    

    dir = opendir(pathplug);

    if(!dir){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    int lendir = 0;

    while((entry = readdir(dir)) != NULL){
        

        lendir = strlen(entry->d_name);

        if(lendir > 3){
            if(entry->d_name[lendir-3] == '.' && entry->d_name[lendir-2] == 's'&& entry->d_name[lendir-1] == 'o'){
                char module[100] = "./libs_dynamic/";            
                strcat(module,entry->d_name);

                printf("%d - %s [%d] %d\n",
                entry->d_ino, module/*entry->d_name*/, entry->d_type, entry->d_reclen);

                handle[count_library] = dlopen(module,RTLD_LAZY);

                if(!handle[count_library]){
                    perror("dlopen");
                    exit(EXIT_FAILURE);
                }
                
                func_ptr[count_library] = dlsym(handle[count_library],"func");

                if(func_ptr[count_library] == NULL){
                    perror("dlsym");
                    exit(EXIT_FAILURE);
                }

                setbutton(count_library,buttons[count_library]);
                count_library++;
            }
        }

    }

    setcountoper(count_library);
    closedir(dir);
}    

void setfuncptr(void){
    char name_library[4][100];
    char name_func[4][100];
    char flag_end = 0;
    
    for(int i = 0; i < 4; i++){
        printf("\nInput name library - %d:",i);
        scanf("%s", name_library[i]);
        clear_buffer();

        handle[i] = dlopen(name_library[i],RTLD_LAZY);

        if(!handle[i]){
            printf("Library %s - not found\n",name_library[i]);
            exit(EXIT_FAILURE);
        }

        printf("\nInput name function - %d:",i);
        scanf("%s", name_func[i]);
        clear_buffer();

        func_ptr[i] = dlsym(handle[i],name_func[i]);

        if(func_ptr[i] == NULL){
            printf("Function %s - not found\n",name_func[i]);
            exit(EXIT_FAILURE);
        }

        char key_sym = ' ';

        printf("\nInput key symbol - %d :",i);
        scanf("%c", &key_sym);
        clear_buffer();
        setbutton(i,key_sym);

        printf("\nContinue / save configuration - (y/n)?: ");
        scanf("%c", &flag_end);
        clear_buffer();

        count_library = i + 1;

        if(flag_end == 'n'){
            break;
        }
    }

    setcountoper(count_library);
}

void closehandle(void){
    for(int i = 0; i < 4; i++){
        if(handle[i]){
            dlclose(handle[i]);
        }
    }
}


void operationshandler(const char *operand1,const char *operand2, char sign, char *result){
    long long int op1 = atoi(operand1);
    long long int op2 = atoi(operand2);
    long long int res = 0;


    switch (sign)
    {
    case '+':
        res = func_ptr[0](op1,op2);
        sprintf(result,"%lld",res);
        break;
    case '-':
        if(count_library > 1){
            res = func_ptr[1](op1,op2);
            sprintf(result,"%lld",res);
        }
        break;
    case '/':
        if(count_library > 2){
            if(op2 != 0){
                res = func_ptr[2](op1,op2);
                sprintf(result,"%lld",res);
            }else{
                strcpy(result,"inf");
            }
        }
        break;
    case '*':
        if(count_library > 3){
            res = func_ptr[3](op1,op2);
            sprintf(result,"%lld",res);
        }
        break;
    default:
        break;
    }
}