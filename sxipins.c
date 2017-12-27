#include <stdio.h>
#include <string.h>

#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-sunxi.h"

int
sunxi_pinctrl_init_with_variant(struct platform_device *pdev,
    const struct sunxi_pinctrl_desc *desc, unsigned long variant)
{
	static int header = 1;
	struct sunxi_desc_function *func;
	char *name, *p;
	int i;

	name = strdup(pdev->name);
	p = strrchr(name, '_');
	*p = 0;
	p = strrchr(name, '_');
	*p = 0;

	/* Linux developers need a bit more OCD. */
	if (strcmp(name, "a64") == 0)
		name = "sun50i_a64";

	if (header) {
		printf("/* Public Domain */\n");
		printf("\n");
		header = 0;
	}

	printf("\n");

	printf("struct sxipio_pin %s_pins[] = {\n", name);
	for (i = 0; i < desc->npins; i++) {
		if (desc->pins[i].variant != 0 &&
		    (desc->pins[i].variant & variant) == 0)
			continue;
		printf("\t{ SXIPIO_PIN(%c, %d), {\n",
		    desc->pins[i].pin.name[1],
		    desc->pins[i].pin.number % 32);
		func = desc->pins[i].functions;
		while (func->name) {
			if (func->variant == 0 || func->variant & variant) {
				printf("\t\t{ \"%s\", %d },\n",
				    func->name, func->muxval);
			}
			func++;
		}
		printf("\t} },\n");
	}
	printf("};\n");

	return 0;
}

void
driver_register(struct platform_driver *driver, const char *name)
{
	struct platform_device pdev;
	int i;

	for (i = 0; driver->driver.of_match_table[i].compatible; i++) {
		const struct of_device_id *of_match_table =
		    &driver->driver.of_match_table[i];

		pdev.dev.variant = (unsigned long)of_match_table->data;
		switch (pdev.dev.variant) {
		case PINCTRL_SUN5I_A10S:
			pdev.name = "sun5i_a10s_pinctrl_driver";
			break;
		case PINCTRL_SUN5I_A13:
			pdev.name = "sun5i_a13_pinctrl_driver";
			break;
		case PINCTRL_SUN5I_GR8:
			pdev.name = "sun5i_gr8_pinctrl_driver";
			break;
		case PINCTRL_SUN7I_A20:
			pdev.name = "sun7i_a20_pinctrl_driver";
			break;
		case PINCTRL_SUN8I_R40:
			pdev.name = "sun8i_r40_pinctrl_driver";
			break;
		default:
			pdev.name = name;
			break;
		}
		driver->probe(&pdev);
	}
}

int
main(void)
{
}
