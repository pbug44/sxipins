#define MODULE_DEVICE_TABLE(x, y)

struct platform_driver;
void module_register(struct platform_driver *, const char *);
#define module_platform_driver(x) \
  __attribute__((constructor)) static void module_init() \
    { module_register(&x, #x); }

#define MODULE_AUTHOR(x)
#define MODULE_DESCRIPTION(x)
#define MODULE_LICENSE(x)
