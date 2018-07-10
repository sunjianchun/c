#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/string.h>

char *SPLIT = "------------------------";
static __init int print_pid(void)
{
    struct task_struct *task,*p;
    struct list_head *pos;
    int total_count = 0,  run_count = 0, inter_count = 0, uninter_count = 0, dead_count = 0, zombie_count = 0, other_count = 0;
    //struct task_struct *run_name = (struct task_struct *)malloc(100 * struct task_struct);
    //struct task_struct *inter_name = (struct task_struct *)malloc(100 * struct task_struct);
    //struct task_struct *uninter_name = (struct task_struct *)malloc(100 * struct task_struct);
    //struct task_struct *dead_name = (struct task_struct *)malloc(100 * struct task_struct);
    //struct task_struct *zombie_name = (struct task_struct *)malloc(100 * struct task_struct);
    //struct task_struct  *other_name = (struct task_struct *)malloc(100 * struct task_struct);
    struct task_struct run_name[100];
    struct task_struct inter_name[100];
    struct task_struct uninter_name[100];
    struct task_struct dead_name[100];
    struct task_struct zombie_name[100];
    struct task_struct other_name[100];
    int i;
    
    task=&init_task;
    list_for_each(pos,&task->tasks)
    {
        p=list_entry(pos, struct task_struct,tasks);
        total_count++;
        switch (p -> state) {
            case TASK_RUNNING:
                memcpy(&run_name[run_count], p, sizeof(p));
                run_count++;
                break;
            case TASK_INTERRUPTIBLE:
                memcpy(&inter_name[inter_count], p, sizeof(p));
                inter_count++;
                break;
            case TASK_UNINTERRUPTIBLE:
                memcpy(&uninter_name[uninter_count], p, sizeof(p));
                uninter_count++;
                break;
            case EXIT_DEAD:
                memcpy(&dead_name[dead_count], p, sizeof(p));
                dead_count++;
                break;
            case EXIT_ZOMBIE:
                memcpy(&zombie_name[zombie_count], p, sizeof(p));
                zombie_count++;
                break;
            default:
                memcpy(&other_name[other_count], p, sizeof(p));
                other_count++;
                break;
        }
    }
    
    printk("系统的进程信息如下：\n");
    printk("%s\n", SPLIT);

    printk("TASK_RUNNING\t%d\n", run_count);
    printk("%s\n", SPLIT);
    for(i = 0; i < run_count; i++) {
        printk("command: %s\t pid: %d\n", (run_name + i) -> comm, (run_name + i) -> pid);
    }
    printk("%s\n", SPLIT);

    printk("TASK_INTERRUPTIBLE\t%d\n", inter_count);
    printk("%s\n", SPLIT);
    for(i = 0; i < inter_count; i++) {
        printk("command: %s\t pid: %d\n", (inter_name + i) -> comm, (inter_name + i) -> pid);
    }
    printk("\n");

    printk("TASK_UNINTERRUPTIBLE\t%d\n", uninter_count);
    printk("%s\n", SPLIT);
    for(i = 0; i < uninter_count; i++) {
        printk("command: %s\t pid: %d\n", (uninter_name + i) -> comm, (uninter_name + i) -> pid);
    }
    printk("\n");

    printk("EXIT_DEAD\t%d\n", dead_count);
    printk("%s\n", SPLIT);
    for(i = 0; i < dead_count; i++) {
        printk("command: %s\t pid: %d\n", (dead_name + i) -> comm, (dead_name + i) -> pid);
    }
    printk("\n");

    printk("EXIT_ZOMBIE\t%d\n", zombie_count);
    printk("%s\n", SPLIT);
    for(i = 0; i < zombie_count; i++) {
        printk("command: %s\t pid: %d\n", (zombie_name + i) -> comm, (zombie_name + i) -> pid);
    }
    printk("\n");

    printk("TASK_OTHER\t%d\n", other_count);
    printk("%s\n", SPLIT);
    for(i = 0; i < other_count; i++) {
        printk("command: %s\t pid: %d\n", (other_name + i) -> comm, (other_name + i) -> pid);
    }
    printk("\n");

    printk("\t\t\t\t总进程数%d\n", total_count);
    return 0;
}
static __exit void print_exit(void)
{
    printk("<0>end!\n");
}
module_init(print_pid);
module_exit(print_exit);
