#ifndef DRIVER_COMMAND
#define DRIVER_COMMAND

void driver_write(int lba, unsigned int data);
char *driver_read(int lba);
void driver_fullwrite(unsigned int data);
void driver_fullread();
int testapp1();
int testapp2();


#endif