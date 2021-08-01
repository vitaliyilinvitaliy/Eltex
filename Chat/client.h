#ifndef _CLIENT_H_
#define _CLIENT_H_

#define POSIX 1
#define SYSTEM_V 2

#define REALIZATION 2

#if REALIZATION == POSIX
    #define ReceiveMessage ReceiveMessagePOSIX
    #define SendMessage SendMessagePOSIX
    #define struct_type parameters_POSIX
#endif //POSIX

#if REALIZATION ==  SYSTEM_V
    #define ReceiveMessage ReceiveMessageSystemV
    #define SendMessage SendMessageSystemV
    #define struct_type parameters_system_v
#endif //SYSTEM_V

#endif //_CLIENT_H_

