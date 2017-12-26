#include <stdio.h>
#include <string.h>

#include <linux/platform_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-sunxi.h"


int
sunxi_pinctrl_init(struct platform_device *pdev,
    const struct sunxi_pinctrl_desc *desc)
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
		printf("\t{ SXIPIO_PIN(%c, %d), {\n",
		    desc->pins[i].pin.name[1],
		    desc->pins[i].pin.number % 32);
		func = desc->pins[i].functions;
		while (func->name) {
			printf("\t\t{ \"%s\", %d },\n", func->name,
			    func->muxval);
			func++;
		}
		printf("\t} },\n");
	}
	printf("};\n");

	return 0;
}

void
module_register(struct platform_driver *driver, const char *name)
{
	struct platform_device pdev;

	pdev.name = name;
	driver->probe(&pdev);
}

int
main(void)
{
}
