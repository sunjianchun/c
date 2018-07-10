#define MODULE
#include <linux/module.h>

int int_module(void) {
    printk("<1>Hello, let's start!\n");
    return 0;
}

void cleanup_module(void) {
    printk("<1>GoodBye\n");
}

