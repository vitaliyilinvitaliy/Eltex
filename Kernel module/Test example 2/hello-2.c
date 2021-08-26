#include <linux/init.h>//требуется для макросов (__init __exit)
#include <linux/kernel.h>
#include <linux/module.h>

static int __init start_mod(void){
    pr_info("!_!_Start_!_!\n");
    return 0;
}

static void __exit finish_mod(void){
    pr_info("finish");
}

module_init(start_mod);
module_exit(finish_mod);

MODULE_LICENSE("GPLv2");
MODULE_DESCRIPTION("Test module 1");