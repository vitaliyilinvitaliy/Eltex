#ifndef _HANDLER_ERROR_H_
#define _HANDLER_ERROR_H_

#define handler_error(str) do{\
    perror(str);\
    return 1;}while(0)


#endif //_HANDLER_ERROR_H_