struct platform_device;

struct platform_driver {
	int (*probe)(struct platform_device *);
	struct {
		const char *name;
		const char *owner;
		const struct of_device_id *of_match_table;
	} driver;
};

struct device {
	unsigned long variant;
};

struct platform_device {
	const char *name;
	struct device dev;
};

void driver_register(struct platform_driver *, const char *);

#define builtin_platform_driver(x) \
  __attribute__((constructor)) static void driver_init() \
    { driver_register(&x, #x); }

#define module_platform_driver(x) \
  __attribute__((constructor)) static void driver_init() \
    { driver_register(&x, #x); }
