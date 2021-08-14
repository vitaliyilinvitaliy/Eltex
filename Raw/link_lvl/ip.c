#include "../config.h"
#include "ip.h"
#include "udp.h"
#include "chsum.h"

#include <netinet/in.h>
#include <string.h>
#include <malloc.h>
#include <arpa/inet.h>

int FillIpHeader(char *ip_header, unsigned short payload_len){
    
    short n_ver_ihl = 0x45;
    /*
    VER - 4 бита. Версия - IPv4 = 4 = 0100(в двоичной системе)
    IHL - 4 бита. Длина заголовка пакета в 32 битных словах.
        32 бита = 4 байта
        длина заголовка 20 байт => 5 слов по 32 бита
        5 = 0101
        Итоговое число - 1 байт: 0100 01001 = 0x45
    */
    short n_ds = 0x00;
    /*
    1 байт
    DS - (Набор флагов) Differentiated Services Field: 0x00 (DSCP: CS0, ECN: Not-ECT)
    */
    short n_length = htons(IP_SIZEOF + UDP_SIZEOF + payload_len);
    /*
    2 байта
    Length - длина пакета в октетах(8 двоичных разрядов(1 байт)), включая заголовок и данные
    */
    short n_identification = htons(0x1234);
    /*
    2 байта
    Identification - значение назначаемое отправителем пакета и предназначенное
    для определения корректной последовательности фрагментов при сборке пакета
    */
    short n_flags_offset = htons(0x4000);
    /*
    2 байта
    1 bit: всегда 0. Зарезервированный бит
    2 bit: определяет возможность фрагментации пакета (не фрагментировать - 1. фрагментировать - 0)
    3 bit: показывает не является ли этот пакет последним в цепочке пакетов
    остальные 13 бит задают 8 байтные смещения в общем сегменте
    0х4000 = 0100 0000 0000 0000
    2 bit == 0 => не фрагментируем
    */
    short n_ttl = 255;
    /*
    1 байт
    TTL - число маршрутизаторов через которые может пройти пакет.
    */
    short n_protocol = 17;
    /*
    1 байт
    Поле протокола верхнего уровня занимает один байт и содержит идентификатор, 
    указывающий, какому протоколу верхнего уровня принадлежит информация, 
    размещенная в поле данных пакета.
    6 - TCP, 
    17 - UDP, 
    1 - ICMP
    */
    short n_checksum = htons(0);
    /*
    Контрольная сумма заголовка занимает 2 байта (16 бит) и рассчитывается только 
    по заголовку. Поскольку некоторые поля заголовка меняют свое значение 
    в процессе передачи пакета по сети (например, поле времени жизни), 
    контрольная сумма проверяется и повторно рассчитывается на каждом маршрутизаторе 
    и конечном узле как дополнение к сумме всех 16-битных слов заголовка. 
    При вычислении контрольной суммы значение самого поля контрольной суммы 
    устанавливается в нуль. Если контрольная сумма неверна, то пакет отбрасывается, 
    как только обнаруживается ошибка.
    */
    struct in_addr addr_ip , source_addr, destination_addr;

    if(inet_aton("127.0.0.1", &addr_ip) == 0){
        handle_error("inet_aton");
    }

    if(inet_aton("172.17.0.1", &source_addr) == 0){
        handle_error("inet_aton");
    }

    if(inet_aton("172.17.0.3", &destination_addr) == 0){
        handle_error("inet_aton");
    }

    int n_sourse_ip = source_addr.s_addr;//addr_ip.s_addr;
    /*
    Адрес источника 4 байта
    */
    int n_destanation_ip = destination_addr.s_addr;//addr_ip.s_addr;
    /*
    Адрес приемника 4 байта
    */

    memcpy((void*)ip_header + VER_IHL_OFFSET, ((void*)&n_ver_ihl), VER_IHL_SIZEOF);
    memcpy((void*)ip_header + DS_OFFSET, ((void*)&n_ds), DS_SIZEOF);
    memcpy((void*)ip_header + LENGTH_OFFSET, (void*)&n_length, IP_LENGTH_SIZEOF);
    memcpy((void*)ip_header + IDENTIFICATION_OFFSET, (void*)&n_identification, IDENTIFICATION_SIZEOF);
    memcpy((void*)ip_header + FLAGS_OFFS_OFFSET, (void*)&n_flags_offset, FLAGS_OFFS_SIZEOF);
    memcpy((void*)ip_header + TTL_OFFSET, ((void*)&n_ttl), TTL_SIZEOF);
    memcpy((void*)ip_header + PROTOCOL_OFFSET, ((void*)&n_protocol), PROTOCOL_SIZEOF);
    memcpy((void*)ip_header + CHECKSUM_OFFSET, (void*)&n_checksum, IP_CHECKSUM_SIZEOF);
    memcpy((void*)ip_header + SOURCE_IP_OFFSET, (void*)&n_sourse_ip, SOURCE_IP_SIZEOF);
    memcpy((void*)ip_header + DESTINATION_IP_OFFSET, (void*)&n_destanation_ip, DESTINATION_IP_SIZEOF);

    n_checksum = CheckSum(ip_header);

    memcpy((void*)ip_header + CHECKSUM_OFFSET, (void*)&n_checksum, IP_CHECKSUM_SIZEOF);


    return 0;
}