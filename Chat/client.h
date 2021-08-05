#ifndef _CLIENT_H_
#define _CLIENT_H_

#define POSIX 1
#define SYSTEM_V 2
#define SHARED_MEMORY_SYSTEM_V 3
#define SHARED_MEMORY_POSIX 4

#define REALIZATION 1

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

#if REALIZATION ==  SHARED_MEMORY_SYSTEM_V
    #define ReceiveMessage ReceiveMessageShMemSystemV
    #define SendMessage SendMessageShMemSystemV
    #define struct_type parameters_shmem_system_v
#endif //SHARED_MEMORY_SYSTEM_V

#if REALIZATION ==  SHARED_MEMORY_POSIX
    #define ReceiveMessage ReceiveMessageShMemPOSIX
    #define SendMessage SendMessageShMemPOSIX
    #define struct_type parameters_shmem_POSIX
#endif //SHARED_MEMORY_POSIX


#endif //_CLIENT_H_

