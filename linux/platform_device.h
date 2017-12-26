struct platform_device {
	const char *name;
};

struct platform_driver {
	int (*probe)(struct platform_device *);
	struct {
		const char *name;
		const char *owner;
		const struct of_device_id *of_match_table;
	} driver;
};

#define builtin_platform_driver(x) \
  __attribute__((constructor)) static void module_init() \
    { module_register(&x, #x); }
