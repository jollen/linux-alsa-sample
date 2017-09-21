/*
 * Copyright (C) 2017 Moko365, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include <linux/fsl_devices.h>
#include <linux/gpio.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>
#include <sound/soc-dai.h>
#include <sound/pcm_params.h>

struct my_soc_data_t {
	int hw;
};

struct my_soc_data_t *my_soc_data;

static int my_soc_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *runtime = substream->private_data;
	struct snd_soc_dai *cpu_dai = runtime->cpu_dai;

	return 0;
}

static void my_soc_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *runtime = substream->private_data;
	struct snd_soc_dai *cpu_dai = runtime->cpu_dai;
}

static int my_soc_hw_free(struct snd_pcm_substream *substream)
{
	return 0;
}
static int my_soc_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *params)
{
	return 0;
}

static struct snd_soc_ops my_soc_ops = {
	.startup = my_soc_startup,
	.shutdown = my_soc_shutdown,
	.hw_params = my_soc_hw_params,
	.hw_free = my_soc_hw_free,
};

static const struct snd_soc_dapm_widget my_soc_dapm_widgets[] = {
	SND_SOC_DAPM_LINE("Line Out Jack", NULL),
	SND_SOC_DAPM_LINE("Line In Jack", NULL),
};

static const struct snd_soc_dapm_route audio_map[] = {
	/* Line out jack */
	{"Line Out Jack", NULL, "AOUT1L"},
	{"Line Out Jack", NULL, "AOUT1R"},

	/* Line in jack */	
	{"AIN1L", NULL, "Line In Jack"},
	{"AIN1R", NULL, "Line In Jack"},
};

static int my_soc_init(struct snd_soc_pcm_runtime *runtime)
{
	struct snd_soc_codec *codec = runtime->codec;

	snd_soc_dapm_new_controls(&codec->dapm, my_soc_dapm_widgets,
				  ARRAY_SIZE(my_soc_dapm_widgets));
	snd_soc_dapm_add_routes(&codec->dapm, audio_map, ARRAY_SIZE(audio_map));
	snd_soc_dapm_sync(&codec->dapm);

	return 0;
}

static struct snd_soc_dai_link my_soc_dai[] = {
	{
	.name = "HiFi",
	.stream_name = "HiFi",
	.codec_dai_name = "My SoC",
	.codec_name = "mysoc.1",
	.cpu_dai_name = "my-dai.0",
	.platform_name = "my-pcm-audio.0",
	.init = my_soc_init,
	.ops = &my_soc_ops,
	},
};

static struct snd_soc_card snd_my_soc_card = {
	.name = "my-audio",
	.dai_link = my_soc_dai,
	.num_links = ARRAY_SIZE(my_soc_dai),
};

/*
 * This function will register the snd_soc_pcm_link drivers.
 */
static int snd_my_soc_plat_probe(struct platform_device *pdev)
{
	my_soc_data = kzalloc(sizeof(struct my_soc_data_t), GFP_KERNEL);

	return 0;
}

static int snd_my_soc_plat_remove(struct platform_device *pdev)
{
	if (my_soc_data)
		kfree(my_soc_data);
	return 0;
}

static struct platform_driver my_soc_driver = {
	.probe = snd_my_soc_plat_probe,
	.remove = snd_my_soc_plat_remove,
	.driver = {
		.name = "my-soc-plat",
		.owner = THIS_MODULE,
    },
};

static struct platform_device *my_snd_device;

static int __init alsa_my_asoc_init(void)
{
	int ret;
	pr_info("my alsa asoc driver\n");

	ret = platform_driver_register(&my_soc_driver);
	if (ret < 0)
		goto exit;

	my_snd_device = platform_device_alloc("my-soc-audio", 1);
	if (!my_snd_device)
		goto err_device_alloc;

	platform_set_drvdata(my_snd_device, &snd_my_soc_card);
	ret = platform_device_add(my_snd_device);
	if (0 == ret)
		goto exit;

	platform_device_unregister(my_snd_device);
err_device_alloc:
	platform_driver_unregister(&my_soc_driver);
exit:
	return ret;
}

static void __exit alsa_my_asoc_exit(void)
{
	platform_driver_unregister(&my_soc_driver);
	platform_device_unregister(my_snd_device);
}

module_init(alsa_my_asoc_init);
module_exit(alsa_my_asoc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jollen Chen");
MODULE_DESCRIPTION("ALSA SoC Layer Driver Template");
