#include <dirent.h>
#include <malloc.h>
#include <string.h>

int DirList(const char *name_dir, char ***get_list){
    struct dirent **scan = NULL;

    int scdr = scandir(name_dir, &scan, NULL, alphasort);

    if(-1 == scdr){
        //ошибка
        return 0;
    }

    (*get_list) = (char**) calloc(sizeof(char *), scdr);

    for(int i = 1; i < scdr; i++){
        (*get_list)[i - 1] = (char*) calloc(sizeof(char), 256);
        if(scan[i]->d_type == 4) (*get_list)[i - 1][0] = '/';
        strcat((*get_list)[i - 1],scan[i]->d_name);
    }

    return scdr - 1;
}