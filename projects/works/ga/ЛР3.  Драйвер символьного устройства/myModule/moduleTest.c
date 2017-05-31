#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gizzatullina Anzhela");
MODULE_DESCRIPTION("test modules");

static int __init md_init(void) {
	printk("Hello, world\n");
	return 0;
}

static void __exit md_exit(void) {
	printk("Goodbye, cruel world\n");
}

module_init(md_init);
module_exit(md_exit);


