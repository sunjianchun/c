#define MODULE
#include <linux/module.h>
#include <linux/init.h>

static int first_init(void) {
    printk(KERN_ALERT, "Hello, let's start!\n");
    return 0;
}

static void first_exit(void) {
    printk(KERN_ALERT, "GoodBye\n");
}

module_init(first_init);
module_exit(first_exit);
