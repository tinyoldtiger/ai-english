#ifndef MY375LIB_H
#define MY375LIB_H

#define MY_FILE_DATA_BUF_LEN	1024	/*对应为FILE_DATA_BUF_LEN的大小*/
#define MY_DISK_BASE_BUF_LEN	1024	/*对应为DISK_BASE_BUF_LEN的大小*/

extern u8 InitUDisk(void);
extern u8 OpenFile(char* fil_name);
extern u8 CreateFile(char* fil_name);
extern u8 WriteFile(u8* buf,u32 len);
extern u8 CloseFile(void);
extern u8 MkDir( char* dir_name );
extern u8 ReadFile(u8* buf,u32 len,u32* br);
extern u8 WriteFile(u8* buf,u32 len);
extern u8 LocatFile(u32 offest);


#endif

