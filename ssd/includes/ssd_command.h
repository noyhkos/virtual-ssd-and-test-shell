#ifndef NAND_CMD_H
#define NAND_CMD_H

// ssd command modules
void ssd_read(int lba);
void ssd_write(int lba, unsigned int data);

#endif // NAND_CMD_H
