#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

static struct proc_dir_entry *count;

static int count_procs(void) {
	struct task_struct *process;
	int acount = 0;
	for_each_process(process) {
		acount++;
	}
	return acount;
}

static int show(struct seq_file *s, void *v) {
	int procs = count_procs();
	seq_printf(s, "%d\n", procs);
	return 0;
}

static int __init proc_count_init(void)
{
	pr_info("proc_count: init\n");
	count = proc_create_single("count", 0, NULL, show);
	return 0;

}

static void __exit proc_count_exit(void)
{
	proc_remove(count);
	pr_info("proc_count: exit\n");
}

module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Michael Tao");
MODULE_DESCRIPTION("Kernel module to count the number of running processes");
MODULE_LICENSE("GPL");
