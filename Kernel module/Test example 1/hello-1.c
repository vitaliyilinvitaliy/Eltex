#include <linux/kernel.h> /* Needed for pr_info() */ 
#include <linux/module.h> /* Needed by all modules */ 
 
/*
Функция инициализации, вызывается, когда модуль загружается
в ядро.
*/
int init_module(void) 
{ 
    pr_info("Hello world 1.\n"); 
    /* A non 0 return means init_module failed; module can't be loaded. */ 
    return 0; 
} 
 
/*
Функция очистки, вызывается непосредственно при выгрузке модуля
из ядра
*/ 
void cleanup_module(void) 
{ 
    pr_info("Goodbye world 1.\n"); 
} 
 
MODULE_LICENSE("GPLv2");//при неопределенной лицензии модуль может не загрузиться
MODULE_DESCRIPTION("Test module 1");
MODULE_AUTHOR("Vitaliy Ilin");

/*
Утилиты для работы с модулями ядра
1. lsmod - просмотр списка загруженных модулей.
2. modinfo <modul_name> - получение информации о загруженном модуле.
3. insmod <modul_name> - загрузка модуля.
4. rmmod <modul_name> - выгрузка модуля.
5. depmod - нахождение завсисмостей между модулями
6. modprobe - загрузка модуля с аргументами и теми модулями, от которых он зависит

Вывод происходит в журнад ядра.
dmesg - просмотр журанала ядра.

Изменяя ядро, вы рискуете потерять данные. Поэтому лучше всего
проводить эксперименты на отдельной физической или виртуальной машине.

*/
