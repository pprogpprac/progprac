/////////////////////////// By Naveen R. Iyer      ////////////////////////
/////////////////////////// UFID: 60116379         ////////////////////////
/////////////////////////// Email: niyer@ufl.edu   ////////////////////////
/////////////////////////// Date: 23rd Feb, 2015   ////////////////////////

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/version.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");


#define ASPDEVSTR_NAME "mycdrv"
#define DEVNAME ASPDEVSTR_NAME "%d"
#define ramdisk_size (size_t) (16*PAGE_SIZE)


// ------------------ IOCTL (START) -------------------
#define MYCDRV_IOC_MAGIC 'Z'
#define ASP_CHGACCDIR  _IO(MYCDRV_IOC_MAGIC, 1)

unsigned long accmode = 7; // 1 for reverse, 0 for regular and 7 is just to keep track of initial value
unsigned long prev_accmode; // to store previous accmode
// ------------------ IOCTL (END) -------------------



int write_active = 0;

// Device count
static int devCount = 3;


// Global variable for the first device number
static dev_t first;


// Obtain device count at load time
module_param(devCount, int, S_IRUGO);


// My structure
struct asp_mycdrv
{
    struct list_head list;
    struct cdev dev; 				//renamed "dev" as "dev" just for my convenience
    char *ramdisk;
    struct semaphore sem;
    int devNo;
};


static struct asp_mycdrv *headNode;
static struct class *foo_class; 		//global variable for the device class


/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////               OPEN                    ////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// This function is called whenever a user application tries to open your device using open() syscall
static int mycdrv_open(struct inode *inode, struct file *file)
{
    struct asp_mycdrv *aspdevStrInFnc;

    aspdevStrInFnc = container_of(inode->i_cdev, struct asp_mycdrv, dev);
    file->private_data = aspdevStrInFnc;

    // Lock the device so that only one user app can open the device at a time
    /*if (down_interruptible(&aspdevStrInFnc->sem))
            return -ERESTARTSYS;*/

    pr_info(" ------------------ OPENING mycdrv%d ----------------\n", iminor(inode));
    pr_info(" OPENED device with major number = %d and minor number = %d:\n", imajor(inode), iminor(inode));
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////               RELEASE                 ////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// This function is called whenever a user application tries to close your device using close() syscall
static int mycdrv_release(struct inode *inode, struct file *file)
{
    //struct asp_mycdrv *aspdevStrInFnc = file->private_data;

    // Unlock the device
    //up(&aspdevStrInFnc->sem);

    pr_info(" CLOSED device with major number = %d and minor number = %d:\n", imajor(inode), iminor(inode));
    pr_info(" -------------- CLOSING mycdrv%d ---------------\n\n", iminor(inode));
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////               READ                    ////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Called whenever a read operation is requested by user app using read() syscall
static ssize_t mycdrv_read(struct file *file, char __user * buf, size_t lbuf, loff_t * ppos)
{
    // To access the private data of each of the devices. In this case, the "ramdisk" struct member
    struct asp_mycdrv *aspdevStrInFnc = file->private_data;
    int nbytes = 0;
    int i =0;
    //msleep(7000);
    //pr_info("Driver: Read func: lbuf = %zu and *ppos = %lld\n", lbuf, *ppos);

    while(write_active == 1)
    {
        mdelay(500);
        // Lock the device so that only one user app can open the device at a time
        /*if (down_interruptible(&aspdevStrInFnc->sem))
                return -ERESTARTSYS;*/
    }
    // Unlock the device
    //up(&aspdevStrInFnc->sem);
    /*if (down_interruptible(&aspdevStrInFnc->sem))
            return -ERESTARTSYS;*/

    if ((lbuf + file->f_pos) > ramdisk_size) //modification here
    {
        pr_info("trying to read past end of device,"
            "aborting because this is just a stub!\n");
        return 0;
    }

    if(accmode == 1) //reverse read
    {
        pr_info("**** Driver: Reverse mode of access selected ! ****\n");
        for(i = 0; i < lbuf; i++)
        {
            //memcpy(&buf[i], aspdevStrInFnc->ramdisk + *ppos - i, 1);
            copy_to_user(&buf[i], aspdevStrInFnc->ramdisk + *ppos - i, 1);
            //pr_info("Iteration %d: buf[%d] = %c and copy to user = %ld\n", i, i, buf[i], copy_to_user(&buf[i], aspdevStrInFnc->ramdisk + *ppos - i, 1));
            //pr_info("Iteration %d: aspdevStrInFnc->ramdisk + *ppos - %d = %s\n", i, i, aspdevStrInFnc->ramdisk + *ppos - i);
        }
    }
    else             //regular read
    {
        pr_info("**** Driver: Regular mode of access selected ! ****\n");
        //nbytes = lbuf - copy_to_user(buf, aspdevStrInFnc->ramdisk + *ppos, lbuf);
        for(i = 0; i < lbuf; i++)
        {
            copy_to_user(&buf[i], aspdevStrInFnc->ramdisk + *ppos + i, 1);
            //pr_info("Iteration %d: buf[%d] = %c and copy to user = %ld\n", i, i, buf[i], copy_to_user(&buf[i], aspdevStrInFnc->ramdisk + *ppos + i, 1));
            //pr_info("Iteration %d: aspdevStrInFnc->ramdisk + *ppos + %d = %s\n", i, i, aspdevStrInFnc->ramdisk + *ppos + i);
        }
    }
    nbytes = lbuf - nbytes;
    *ppos += nbytes;
    //pr_info(" READING function, nbytes=%d, pos=%lld, f_pos = %lld\n", nbytes, *ppos, file->f_pos);
    return nbytes;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////               WRITE                   ////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Called whenever a write operation is requested by user app using write() syscall
static ssize_t mycdrv_write(struct file *file, const char __user * buf, size_t lbuf, loff_t * ppos)
{
    // To access the private data of each of the devices. In this case, the "ramdisk" struct member
    struct asp_mycdrv *aspdevStrInFnc = file->private_data;
    int nbytes = 0;
    int i = 0;

    write_active = 1;

    // Lock the device so that only one user app can open the device at a time
    if (down_interruptible(&aspdevStrInFnc->sem))
            return -ERESTARTSYS;

    // Uncomment the following lines of code if you are using multiple terminals to test concurrency
    //3 seconds delay just like that
    pr_info("Delay for 3 seconds enabled !\n");
    msleep(3000);


    if ((lbuf + file->f_pos) > ramdisk_size)
    {
        pr_info("trying to write past end of device,"
            "aborting because this is just a stub!\n");
        return 0;
    }

    if(accmode == 1) //reverse write
    {
        //pr_info("**** Driver: Writer func: Reverse mode of access selected ! ****\n");
        for(i = 0; i < lbuf; i++)
        {
            //memcpy(aspdevStrInFnc->ramdisk + *ppos - i, &buf[i], 1);
            nbytes += copy_from_user(aspdevStrInFnc->ramdisk + *ppos - i, &buf[i], 1);
            //pr_info("Iteration %d: buf[%d] = %c and copy FROM user = %ld\n", i, i, buf[i],copy_from_user(aspdevStrInFnc->ramdisk + *ppos - i, &buf[i], 1));
            //pr_info("Iteration %d: aspdevStrInFnc->ramdisk + *ppos - %d = %s\n", i, i, aspdevStrInFnc->ramdisk + *ppos - i);
        }
    }
    else            //regular write
    {
        //pr_info("**** Driver: Writer func:  Regular mode of access selected ! ****\n");
        //nbytes = lbuf - copy_from_user(aspdevStrInFnc->ramdisk + *ppos, buf, lbuf);
        for(i = 0; i < lbuf; i++)
        {
            copy_from_user(aspdevStrInFnc->ramdisk + *ppos + i, &buf[i], 1);
            //pr_info("Iteration %d: buf[%d] = %c and copy FROM user = %ld\n", i, i, buf[i],copy_from_user(aspdevStrInFnc->ramdisk + *ppos + i, &buf[i], 1));
            //pr_info("Iteration %d: aspdevStrInFnc->ramdisk + *ppos + %d = %s\n", i, i, aspdevStrInFnc->ramdisk + *ppos + i);
        }
    }

    nbytes = lbuf - nbytes;
    *ppos += nbytes;
    //pr_info(" WRITING function, nbytes=%d, pos=%lld, f_pos = %lld\n", nbytes, *ppos, file->f_pos);

    // Unlock the device
    up(&aspdevStrInFnc->sem);

    write_active = 0;

    return nbytes;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////               LSEEK                   ////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
static loff_t mycdrv_lseek(struct file *file, loff_t offset, int orig)
{
    loff_t new_pos = 0;
    printk(KERN_INFO " mycdrv: lseek function in work\n");
    //pr_info(" offset = %lld\n", offset);
    //pr_info(" BEFORE: f_pos = %lld\n", file->f_pos);
    //pr_info(" BEFORE: new_pos = %lld\n", new_pos);
    //pr_info(" ramdisk_size = %ld\n", ramdisk_size);
    switch(orig)
    {
        case 0 : /*seek set*/
            new_pos = offset;
            break;
        case 1 : /*seek cur*/
            new_pos = file->f_pos + offset;
            break;
        case 2 : /*seek end*/
            new_pos = ramdisk_size + offset;
            break;
    }
    if(new_pos > (loff_t) ramdisk_size)
    {
        pr_info(" Out of bounds ! Setting to closest boundary !\n");
        //pr_info(" new_pos = %lld and ramdisk_size = %ld\n", new_pos, ramdisk_size);
        new_pos = ramdisk_size;
    }
    if(new_pos < 0)
    {
        pr_info(" Negative boundary detected ! Setting to zero !\n");
        //pr_info(" new_pos = %lld and ramdisk_size = %ld\n", new_pos, ramdisk_size);
        new_pos = 0;
    }
    file->f_pos = new_pos;
    //pr_info(" AFTER: f_pos is %lld\n", file->f_pos);
    //pr_info(" AFTER: new_pos = %lld\n", new_pos);
    return new_pos;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////               IOCTL                   ////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int mycdrv_ioctl(struct inode *inode, struct file *f, unsigned int cmd, unsigned long arg)
#else
static long mycdrv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
#endif
//int mycdrv_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
    //struct asp_mycdrv *aspdevStrInFnc = file->private_data;
    //int err = 0;
    //unsigned long prev_accmode = 0;

    prev_accmode = accmode;

    pr_info("Driver: mycdrv_ioctl: unsigned int cmd = %d and unsigned long arg = %ld\n", cmd, arg);
    if(arg == 1)
    {
        pr_info(" ||||||||||||||| REVERSE MODE $$$$$$$$$$$$$$ \n");
    }
    else
    {
        pr_info(" ||||||||||||||| REGULAR MODE $$$$$$$$$$$$$$ \n");
    }

    if(prev_accmode == 7)
    {
        pr_info("Driver: No previous access mode ! First time !\n");
    }
    else if(prev_accmode == 1)
    {
        pr_info("Driver: Previous access mode of the devices was Reverse !\n");
    }
    else
    {
        pr_info("Driver: Previous access mode of the devices was Regular !\n");
    }

    switch(cmd)
    {
          case ASP_CHGACCDIR:
            pr_info("Driver: Inside ioctl function!\n");
            accmode = (int) arg;
            //accmode = 0;
            break;

          default:  /* redundant, as cmd was checked against MAXNR */
            return -ENOTTY;
    }
    return prev_accmode;
}


// Define the file operations any user app can perform on your device
static const struct file_operations mycdrv_fops =
{
    .owner = THIS_MODULE,
    .read = mycdrv_read,
    .write = mycdrv_write,
    .open = mycdrv_open,
    .release = mycdrv_release,
    .llseek = mycdrv_lseek,
    #if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
    .ioctl = mycdrv_ioctl
    #else
    .unlocked_ioctl = mycdrv_ioctl
    #endif
};

// Called once when insmod command is used, creates as many devices as requested
static int __init my_init(void)
{
    int i = 0;
    int ret;
    struct asp_mycdrv *aspdevStrNode;

    ret = alloc_chrdev_region(&first, 0, devCount, ASPDEVSTR_NAME);
    if(ret < 0)
    {
        printk(KERN_INFO "Err: alloc_chrdev_region failed\n");
        return -1;
    }

    foo_class = class_create(THIS_MODULE, "NRI_CLASS");
    if(foo_class == NULL)
    {
        printk(KERN_INFO "Err: failed create class\n");
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////             FOR EACH OF THE NODES IN THE KERNEL LINKED LIST          //////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    for(i = 0; i < devCount; i++)
    {
        // Allocate Kernel memory and zet it to zero using kzalloc()
        aspdevStrNode = kzalloc(sizeof(struct asp_mycdrv), GFP_KERNEL);
        //memset(aspdevStrNode, 0, sizeof(struct asp_mycdrv));

        // Do the same for the "ramdisk" struct member
        aspdevStrNode->ramdisk = kzalloc(ramdisk_size, GFP_KERNEL);

        // Assign the minor number of the device based on the loop iteration
        aspdevStrNode->devNo = i;
        sema_init(&(aspdevStrNode->sem), 1);
        //aspdevStrNode->dev = cdev_alloc();
        cdev_init(&(aspdevStrNode->dev), &mycdrv_fops);

        if(device_create(foo_class, NULL, MKDEV(MAJOR(first), MINOR(first) + i), NULL, DEVNAME, i)  == NULL )
        {
            printk(KERN_INFO "Err: failed create device\n");
            return -1;
        }

        ret = cdev_add(&(aspdevStrNode->dev), MKDEV(MAJOR(first), MINOR(first) + i), 1);
        if(ret<0)
        {
            printk(KERN_INFO "Err: failed to add device\n");
            return -1;
        }

        if(i == 0)
        {
            // Allocate Kernel memory and zet it to zero using kzalloc()
            //headNode = kzalloc(sizeof(struct asp_mycdrv), GFP_KERNEL);
            //memset(aspdevStrNode, 0, sizeof(struct asp_mycdrv));

            // Do the same for the "ramdisk" struct member
            //headNode->ramdisk = kzalloc(ramdisk_size, GFP_KERNEL);
            headNode = aspdevStrNode;
            INIT_LIST_HEAD(&(headNode->list));
        }
        else
        {
            list_add(&(aspdevStrNode->list),&(headNode->list));
        }

        pr_info("Node created ! Major number = %d and Minor number = %d\n", MAJOR(first), aspdevStrNode->devNo);
    }

    // Print the details of the newly created character device
    //printk(KERN_INFO "Major number is %d", MAJOR(first));
    pr_info("Succeeded in registering character device %s with major number %d !\n", ASPDEVSTR_NAME, MAJOR(first));
    return 0;
}

// Called once when rmmod command is used, gracefully destroys all devices created
static void __exit my_exit(void)
{
    struct list_head *pos, *var;			//var necessary since list_del modifies pos variable internally
    struct asp_mycdrv *aspdevStrNode;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //////       Safely delete and free memory from each node in the kernel linked list      ///////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    list_for_each_safe(pos, var, &(headNode->list))
    {
        // Use list_entry macro to map a list_head structure pointer back into a pointer to the structure that contains it
        aspdevStrNode = list_entry(pos, struct asp_mycdrv, list);

        // Firstly: Remove the node's cdev structure from the system
        cdev_del(&(aspdevStrNode->dev));

        // Secondly: Remove the node device created using device_create()
        device_destroy(foo_class, MKDEV(MAJOR(first), MINOR(first) + aspdevStrNode->devNo));

        // Thirdly: Free the node's ramdisk memory from Kernel
        kfree(aspdevStrNode->ramdisk);

        // Lastly: Free the node's device structure
        kfree(aspdevStrNode);

        // Print message on dmesg command
        pr_info("Device with major number %d and minor number %d unregistered !\n", MAJOR(first), MINOR(first) + aspdevStrNode->devNo);
    }

    // Do the same for the last node in the list
    // Firstly: Remove the node's cdev structure from the systeme
    cdev_del(&(headNode->dev));

    // Secondly: Remove the node device created using device_create()
    device_destroy(foo_class, MKDEV(MAJOR(first), MINOR(first)));

    // Thirdly: Free the node's ramdisk memory from Kernel
    kfree(headNode->ramdisk);

    // Lastly: Free the node's device structur
    kfree(headNode);

    // Destroy the entire class of the device and then unregister !
    class_destroy(foo_class);
    unregister_chrdev_region(first, devCount);

    pr_info("Last device with major number %d and minor number %d unregistered !\n", MAJOR(first), MINOR(first));
}

module_init(my_init);
module_exit(my_exit);
