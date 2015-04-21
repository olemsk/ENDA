/*
 * This is a demo Linux kernel module.
 */
//#include <stdint.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> 
#include "efm32gg.h"
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <asm/signal.h>
#include <linux/poll.h>
#include <asm/siginfo.h>
#include <linux/signal.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/mm.h>
#include <linux/types.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;


static int my_release(struct inode *inode, struct file *filp);
static int my_open(struct inode *inode, struct file *filp);
static ssize_t my_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
static ssize_t my_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);
static irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs);
static void __exit template_cleanup(void);




static struct file_operations my_fops =
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
char input_value;
char* input_value_ptr = &input_value;

//char input_values[]={0,0,0,0,0,0,0,0};

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
	
	if(num < 0)
	{
		printk(KERN_INFO "Error: num < 0 ");
	
	}
	
	


	/* Initialize char device structure */
	cdev_init(&my_cdev, &my_fops);		//TODO
	my_cdev.owner = THIS_MODULE;		// TODO
	

	/* Register char device to kernel*/	
	num = cdev_add(&my_cdev, devno, 1);
	if(num < 0)
	{
		printk(KERN_INFO "Error: num < 0, not added to kernel ");
	
	}
	
	
	/* Make device visible in user space*/
	cl = class_create(THIS_MODULE, "gamepad");	//TODO
	device_create(cl, NULL, devno, NULL, "gamepad"); //TODO


	resource = request_mem_region(GPIO_PC_DIN, 1, "gamepad");
	
	if(resource != NULL)
	{

	printk(KERN_INFO "got mem region");
	}
	
	

	



	/*         Setup gamepad for input            */
	iowrite32(0x33333333, GPIO_PC_MODEL);
	iowrite32(0xFF, GPIO_PC_DOUT);
	iowrite32(0x22222222, GPIO_EXTIPSELL);
	iowrite32(0xFF, GPIO_IEN);
	iowrite32(0xFF, GPIO_IFC);
	iowrite32(0xFF, GPIO_EXTIFALL);


	request_irq(17, (irq_handler_t)interrupt_handler, 0, "gamepad", &my_cdev);
	request_irq(18, (irq_handler_t)interrupt_handler, 0, "gamepad", &my_cdev);

		
	


	printk(KERN_INFO "Hello World, here is your module speaking\n");
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
	
	cdev_del(&my_cdev);
	//release_mem_region(GPIO_PC_BASE, GPIO_IFC-GPIO_PA_BASE);
	release_mem_region(GPIO_PC_DIN, 1);
	unregister_chrdev_region(&devno, 1);

	free_irq(17, &my_cdev);
	free_irq(18, &my_cdev);

	 printk("Short life for a small module...\n");
}



static irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs) {
	//printk(KERN_INFO "Handle interrupt\n");
	
	uint32_t data = ioread32(GPIO_PC_DIN); // Reads gamepad input
	int i;
	iowrite32(0xff, GPIO_IFC);
	
		switch (data){
			case 0xFE:
				*input_value_ptr = 1;
				break;
			case 0xFD:
				*input_value_ptr = 2;
				break;
			case 0xFB:
				*input_value_ptr =3;
				break;
			case 0xF7:
				*input_value_ptr = 4;
				break;
			case 0xEF:
				*input_value_ptr = 5;
				break;
			case 0xDF:
				*input_value_ptr = 6;
				break;
			case 0xBF:
				*input_value_ptr = 7;
				break;
			case 0x7F:
				*input_value_ptr = 8;
				break;
			default:
				//printk("Data: %d \n",data);
				*input_value_ptr = 9;
				break;
		}
		/*
		if(data || 1<<i == 0)
		 {
			input_values[i] = 1;
		}
		else 
		{

		input_values[i] = 0; s
		}
		*/
	
	printk("Input value u: %p \n", *input_value_ptr);
	//printk("Input value m: %p \n", input_value_ptr);
	/*
	for( i =0; i<8;i++)
	{		
	printk(KERN_INFO "%d",input_values[i]);
	}*/
	
	/*
	if(async_queue) 
	{
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	}
	*/	
		
		//printk(KERN_INFO "Handle interrupt exit\n");
		
		
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
	
	
	printk("Copy to user: %d \n",copy_to_user(buff, input_value_ptr, 1));	// Copy to buffer
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

