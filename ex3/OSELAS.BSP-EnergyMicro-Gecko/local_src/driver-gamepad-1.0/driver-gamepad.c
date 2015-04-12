/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> 
#include <efm32gg.h>



static int my_release(struct inode *inode, struct file *filp)
static int my_open(struct inode *inode, struct file *filp)


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
	
	

	



	/*         Setup gamepad for input            */
	iowrite32(0x33333333, GPIO_PC_MODEL);
	iowrite32(0xFF, GPIO_PC_DOUT);
	iowrite32(0x22222222, GPIO_EXTIPSELL);
	iowrite32(0xFF, GPIO_IEN);
	iowrite32(0xFF, GPIO_IFC);
	iowrite32(0xFF, GPIO_EXTIFALL);


	request_irq(17, (irq_return_t)interrupt_handler, 0, "gamepad", &my_cdev);
	request_irq(18, (irq_return_t)interrupt_handler, 0, "gamepad", &my_cdev);

		
	


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

	free_irq(17, &driver_cdev);
	free_irq(18, &driver_cdev);

	 printk("Short life for a small module...\n");
}



static irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs) {
	printk(KERN_INFO "Handle interrupt\n");
	iowrite32(0xff, GPIO_IFC);

	if(async_queue) 
	{
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	}
		return IRQ_HANDLED;
}


static int my_open(struct inode *inode, struct file *filp) {
	printk(KERN_INFO "Opening gamepad driver.\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *filp) {
	printk(KERN_INFO "Closing gamepad driver.\n");
	return 0;
}



static ssize_t my_read(struct file *filp, char __user *buff,
size_t count, loff_t *offp)
{
	uint32_t data = ioread32(GPIO_PC_DIN); // Reads gamepad input
	copy_to_user(buff, &data, 1);	// Copy to buffer
	return 1;
}

static ssize_t my_write(struct file *filp, const char __user *buff,
size_t count, loff_t *offp)
{
	return 0;  // Shall not write to gamepad
}



module_init(template_init);
module_exit(template_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

