#include <linux/module.h>
#include <linux/platform_device.h>

static struct resource ldt_resource[] = {
};

static void ldt_dev_release(struct device *dev)
{
}

static struct platform_device ldt_platform_device = {
	.name	= "snd_pi_i2s_pcm",
	.id	= -1,
};

static int ldt_plat_dev_init(void)
{
	return platform_device_register(&ldt_platform_device);
}

static void ldt_plat_dev_exit(void)
{
	platform_device_unregister(&ldt_platform_device);
}

module_init(ldt_plat_dev_init);
module_exit(ldt_plat_dev_exit);

MODULE_LICENSE("GPL");
