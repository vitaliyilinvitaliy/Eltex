#ifndef _SEND_MESSAGE_H_
#define _SEND_MESSAGE_H_

#include "message.h"

#include <stdlib.h>
#include <mqueue.h>

int SendMessageSystemV(char *, struct my_parameters);
int SendMessagePOSIX(char *, struct my_parameters);

#endif //_SEND_MESSAGE_H_