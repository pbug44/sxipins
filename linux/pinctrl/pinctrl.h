struct pinctrl_pin_desc {
	unsigned number;
	const char *name;
};

#define PINCTRL_PIN(a, b) { .number = a, .name = b }
