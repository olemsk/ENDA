/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> 
#include <efm32gg.h>


static struct file_operations my_fops=
{
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release
};

struct cdev my_cdev;
struct class *cl;
dev_t devno;
struct resource *resource; 

/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */


static int __init template_init(void)
{

	int num = alloc_chrdev_region(&devno, 0,1,"gamepad");
	
	/* Register char device to kernel*/	
	num = cdev_add(%my_cdev, devno, 1);


	/* Initialize char device structure */
	cdev_init(&my_cdev, &my_fops);		//TODO
	my_cdev.owner = THIS_MODULE;		// TODO

	/* Make device visible in user space*/
	cl = class_create(THIS_MODULE, "gamepad");	//TODO
	device_create(cl, NULL, devno, NULL, "gamepad"); //TODO


	resource = request_mem_region(GPIO_PC_BASE, GPIO_IFC - GPIO_PA_BASE, "gamepad");
	
	if(resource != NULL)
	{

	printk("got mem region");
	}
	


	printk("Hello World, here is your module speaking\n");
	return 0;

}














/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit template_cleanup(void)
{	
	release_mem_region(GPIO_PC_BASE, GPIO_IFC-GPIO_PA_BASE);
	unregister_chrdev_region(&devno, 1);
	 printk("Short life for a small module...\n");
}

module_init(template_init);
module_exit(template_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

