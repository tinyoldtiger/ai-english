/**************************************************************
ģ����:ch375.c 
����ʵ��:CH375Ӳ���ײ����ֲ����,���⻹���������ĸĽ�,����CH375�Ŀ⺯����д�Ƚϲ����淶, 
 		�ʴ�ģ�鸺��ѿ⺯�����·�װ���ļ���д��ͨ�ø�ʽ.����װ���д�ٶȻ������½�.�����Ҫ
 		�ϸ��ٵĲ���,���Լ�ȥ��ԭ�⺯��
 		***һ������,��Ӧ��ʹ��ԭ��ĺ���,����������ݴ���
����:���Ӱײ�




�汾��:V1.0 
�汾˵��:	1.CH375Ӳ����������.����IOָ����Ҫ���ӳ�,��������һ��Ӳdelay����,���Լ�����CPU���ٶ�,���ͺ����ٶ�,ʹϵͳ����
			2.��д����ʹ��ͨ�ø�ʽ,�������в�����������Ϊ��λ,�ʲ��ʺ�51֮��ʹ��,�м�ʹ���˻������,�ŵ�������ͨ����,ȱ���ǽ������ٶ�. 
		 	3.�����˴���Ŀ¼����  
����:2009-4-10
***************************************************************/


#include "..\STM32_PRJ\Libraries\CMSIS\stm32f10x.h"
#include "my375lib.h"


//�⼸��������Ҫ��375��ͷ�ļ�֮ǰ
#define CH375_INT_WIRE (GPIOB->IDR & GPIO_Pin_0)
#define FILE_DATA_BUF_LEN		MY_FILE_DATA_BUF_LEN
#define DISK_BASE_BUF_LEN		MY_DISK_BASE_BUF_LEN

#define NO_DEFAULT_CH375_F_ENUM		1		/* ����CH375FileEnumer*/
#define NO_DEFAULT_CH375_F_QUERY	1		/* ����CH375FileQuery*/
//#include "usb\\CH375HFM.h"
#include "CH375HFM.h"
#include "hal.h"

#include <string.h>
#include <stdio.h>


//��������
#define CS375_H		GPIOB->BSRR=GPIO_Pin_2;
#define CS375_L		GPIOB->BRR=GPIO_Pin_2;

#define WR375_H		GPIOB->BSRR=GPIO_Pin_10; 
#define WR375_L		GPIOB->BRR=GPIO_Pin_10;  

#define RD375_H		GPIOB->BSRR=GPIO_Pin_11; 
#define RD375_L		GPIOB->BRR=GPIO_Pin_11;  

#define ADD375_H	GPIOB->BSRR=GPIO_Pin_12; 	
#define ADD375_L	GPIOB->BRR=GPIO_Pin_12;  	

#define RST375_H	GPIOB->BSRR=GPIO_Pin_1;  
#define RST375_L    GPIOB->BRR=GPIO_Pin_1;   

//#define GET_INT		(GPIOB->IDR & GPIO_Pin_0)	/*��ȡINT��״̬*/

/**************************************************************
���������궨�����ڸı�IO�ڵ��������״̬,Ϊ������ٶ�,�������ֱ�Ӹı�Ĵ����İ취,����Ӧ�ø��� 
ʹ�õ�IO�ŵĲ�ͬ�����������,����ʹ��PA0-7��ΪDATA�� ,�ʲ����ļĴ���ΪGPIOA->CRL
***************************************************************/
#define SET_DATA_OUT		GPIOA->CRL=0x33333333	/*�������50MHZ�ٶ�?*/
#define SET_DATA_IN			GPIOA->CRL=0x44444444	/*��������*/
	
#define GET_DATA375()			(GPIOA->IDR&0xff)
#define SET_DATA375(dat)	GPIOA->BSRR=(dat|(((~dat)<<16)))

//Ӳ�ӳٺ���,�ɸ���CPU�ٶ��𲽵���������ٶȵ��ٽ��
void delay(u16 t)
{
	u8 i;
	while(t--)
	{
		for(i=0;i<20;i++);
	}
}


/****************************************
** ������:Init375 
** ����:��ʼ��375
** ע������:RST����Ϊ��λ,Ȼ��ѿ��ƽŶ���Ϊ��Ч,IO��Ϊ��������
****************************************/
void Init375(void)
{
	RST375_H;
	CS375_H;
	RD375_H;
	WR375_H;
	Timer1=400;
	while(Timer1);
	RST375_L;
}
/***************************************
** ������:xWriteCH375Cmd 
** ���� :д����
** ע������: ADD=1Ϊ����,����ʱ������Ҫ��4US
***************************************/
void xWriteCH375Cmd(u8 cmd)
{
	//�ӳ�2US
	delay(1);
	SET_DATA_OUT;
	ADD375_H;
	WR375_L;
	SET_DATA375(cmd);
	CS375_L;
	//�ȴ�����2US
	delay(1);
	WR375_H;
	CS375_H;
}
/**************************************************************
** ������:xWriteCH375Data
** ����:д����
** ע������:ADD=0ʱΪд����
***************************************************************/
void xWriteCH375Data(u8 dat)
{
	//�ӳ�2US
	delay(1);
	SET_DATA_OUT;
	ADD375_L;
	WR375_L;
	SET_DATA375(dat);
	CS375_L;
	//�ȴ�����2US
	delay(1);
	WR375_H;
	CS375_H;
}

/**************************************************************
** ������:xReadCH375Data
** ����:������
** ע������:ADD=0ʱΪ����
***************************************************************/
u8 xReadCH375Data(void)
{
	u8 tmp;
	//�ӳ�2US
	delay(1);
	SET_DATA_IN;
	ADD375_L;
	RD375_L;
	CS375_L;
	//�ȴ�����2US
	delay(1);
	tmp=GET_DATA375();
	RD375_H;
	CS375_H;
	return tmp;
}

/**************************************************************
** ������:InitUDisk
** ����:��ʼ��U��
** ע������:����Ӳ�����ֳ�ʼ��375,�ٵ��������ʼ��U��-ע�⺯������һ��200MS���ӳ�
***************************************************************/
u8 InitUDisk(void)
{
	u8 rtn,i;
	Init375();					//375Ӳ����ʼ��

	rtn = CH375LibInit( ); 		//375�����ʼ��
	if(rtn!=ERR_SUCCESS)
		return(rtn);

	rtn=CH375DiskConnect();		//����Ƿ�����
	if(rtn!=ERR_SUCCESS)
		return(rtn);
	
	for(i=0;i<5;i++)
	{
		Timer1=500;
		while(Timer1);
		//���U���Ƿ�׼����-������һ����,��ɼ��ݴ����U��
		rtn=CH375DiskReady();
		if(rtn==ERR_SUCCESS)
		{
			return rtn;
		}
	}
	return(rtn);
}

/**************************************************************
    ���º����������375�⺯��,֮����Ҫ���±�д��ЩOPENFILE֮��ĺ���,
 	����Ϊ375�Ŀ�д�Ĳ��Ǻܹ淶---һЩ��д����Ҫͨ��ֱ�Ӳ����ṹ�����ܵ��ù��ܺ���,
 	�������º�����375�Ŀ���·�װ�ɱ�׼��FAT32����,���������ô�����΢���˵�,������STM32 72M�������ٶ���˵,���Խ���
	v1.0��-ֻΪISP100ϵ�ж����ļ��װ汾
***************************************************************/

//���¼���������ΪISP100ϵͳ������
//static u32 Read_File_Left_Size;		//�ļ�ʣ�¶��û��ȡ
//static u32 Read_Sector_Cnt;			//ÿ����Ҫ��ȡ��������
//static u32 Read_Each_Size;			//ÿ�ο��Զ�ȡ�Ĵ�С
static u32 File_Size;				//�ļ���С,��ֵʵʱ����
//static u32 File_Offset;				//�ļ�ָ��ƫ��,��ֵʵʱ����


/**************************************************************
** ������:OpenFile,CloseFile
** ����:���ļ�
** ע������:�����ļ�������Ϊ��д,����375��Ĺ涨~~, �������Ҫ���ļ�,���ļ���СCH375vFileSize����Ӵ�(һ������-1)�ֽ�
** ����:�������
***************************************************************/
u8 OpenFile(char* fil_name)
{
	u8 rtn;
	strcpy( (char *)mCmdParam.Open.mPathName, fil_name);
	rtn=CH375FileOpen();

	File_Size=CH375vFileSize;
	CH375vFileSize += CH375vSectorSize-1;	//CH375ϵͳ�ر𲿷�,�ļ���СҪ�Ӵ�һ��,
	return(rtn);
}

u8 CreateFile(char* fil_name)
{
	u8 rtn;
	strcpy( (char *)mCmdParam.Open.mPathName, fil_name);
	rtn=CH375FileCreate();
	File_Size=0;
//	File_Offset=0;
	return rtn;
}
/**************************************************************
	�ر��ļ�
***************************************************************/
u8 CloseFile(void)
{
	return(CH375FileClose());
}

/**************************************************************
** ������:MkDir
** ����:����Ŀ¼
** ע������:CH375�ĺ����Ȿ��û�д���Ŀ¼�ĺ���,����ǹٷ����ڲ�©�ĺ���,�ڲ��漰��һЩFAT�ĵײ����
***************************************************************/
const char* DirConstData=".          \x10\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x21\x30\x0\x0\x0\x0\x0\x0..         \x10\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x21\x30\x0\x0\x0\x0\x0\x0";
u8	MkDir( char* dir_name )
{
	u8	i, j;
	u16	count;
	u32	UpDirCluster;
	u8*	DirXramBuf;
	
	strcpy((char*)mCmdParam.Create.mPathName,(const char*)dir_name);

	j = 0xFF;
	for (i = 0; i != sizeof( mCmdParam.Create.mPathName ); i ++) 
	{  /* ���Ŀ¼·�� */
		if (mCmdParam.Create.mPathName[ i ] == 0) 
			break;
		if (mCmdParam.Create.mPathName[ i ] == PATH_SEPAR_CHAR1 || mCmdParam.Create.mPathName[ i ] == PATH_SEPAR_CHAR2) 
			j = i;  /* ��¼�ϼ�Ŀ¼ */
	}
	i = ERR_SUCCESS;
	if( j == 0 || j == 2 && mCmdParam.Create.mPathName[1] == ':' ) 
		UpDirCluster = 0;  /* �ڸ�Ŀ¼�´�����Ŀ¼ */
	else 
	{
		if (j != 0xFF) 
		{  /* ���ھ���·��Ӧ�û�ȡ�ϼ�Ŀ¼����ʼ�غ� */
			mCmdParam.Create.mPathName[ j ] = 0;
			i = CH375FileOpen( );  /* ���ϼ�Ŀ¼ */
			if (i == ERR_SUCCESS) i = ERR_MISS_DIR;  /* ���ļ�����Ŀ¼ */
			else if (i == ERR_OPEN_DIR) i = ERR_SUCCESS;  /* �ɹ����ϼ�Ŀ¼ */
			mCmdParam.Create.mPathName[ j ] = PATH_SEPAR_CHAR1;  /* �ָ�Ŀ¼�ָ��� */
		}
		UpDirCluster = CH375vStartCluster;  /* �����ϼ�Ŀ¼����ʼ�غ� */
	}
	if (i == ERR_SUCCESS) 
	{  /* �ɹ���ȡ�ϼ�Ŀ¼����ʼ�غ� */
		i = CH375FileOpen();  /* �򿪱�����Ŀ¼ */
		if (i == ERR_SUCCESS) 
			i = ERR_FOUND_NAME;  /* ���ļ�����Ŀ¼ */
		else if (i == ERR_OPEN_DIR) 
			i = ERR_SUCCESS;  /* Ŀ¼�Ѿ����� */
		else if (i == ERR_MISS_FILE) 
		{  /* Ŀ¼������,�����½� */
			i = CH375FileCreate();  /* �Դ����ļ��ķ�������Ŀ¼ */
			if (i == ERR_SUCCESS) 
			{
//				if ( &FILE_DATA_BUF[0] == &DISK_BASE_BUF[0] ) CH375DirtyBuffer( );  /* ���FILE_DATA_BUF��DISK_BASE_BUF���������������̻����� */
				DirXramBuf = &FILE_DATA_BUF[0];  /* �ļ����ݻ����� */
				for ( i = 0x40; i != 0; i -- ) 
				{  /* Ŀ¼�ı�����Ԫ,�ֱ�ָ��������ϼ�Ŀ¼ */
					*DirXramBuf = *DirConstData;
					DirXramBuf ++;
					DirConstData ++;
				}

				FILE_DATA_BUF[0x1A] = (u8)CH375vStartCluster;  /* �������ʼ�غ� */
				FILE_DATA_BUF[0x1B] = (u8)(CH375vStartCluster>>8);
				FILE_DATA_BUF[0x14] = (u8)(CH375vStartCluster>>16);
				FILE_DATA_BUF[0x15] = (u8)(CH375vStartCluster>>24);
				FILE_DATA_BUF[0x20+0x1A] = (u8)UpDirCluster;  /* �ϼ�Ŀ¼����ʼ�غ� */
				FILE_DATA_BUF[0x20+0x1B] = (u8)(UpDirCluster>>8);
				FILE_DATA_BUF[0x20+0x14] = (u8)(UpDirCluster>>16);
				FILE_DATA_BUF[0x20+0x15] = (u8)(UpDirCluster>>24);

				for ( count = 0x40; count != CH375vSectorSize; count ++ ) 
				{  /* ���Ŀ¼��ʣ�ಿ�� */
					*DirXramBuf = 0;
					DirXramBuf ++;
				}
				mCmdParam.Write.mSectorCount = 1;
				i = CH375FileWrite( );  /* дĿ¼�ĵ�һ������ */
				if ( i == ERR_SUCCESS ) 
				{
					DirXramBuf = &FILE_DATA_BUF[0];
					for ( i = 0x40; i != 0; i -- ) 
					{  /* ���Ŀ¼�� */
						*DirXramBuf = 0;
						DirXramBuf ++;
					}
					for ( j = 1; j != CH375vSecPerClus; j ++ ) 
					{
//						if ( &FILE_DATA_BUF[0] == &DISK_BASE_BUF[0] ) CH375DirtyBuffer( );  /* ���FILE_DATA_BUF��DISK_BASE_BUF���������������̻����� */
						mCmdParam.Write.mSectorCount = 1;
						i = CH375FileWrite( );  /* ���Ŀ¼��ʣ������ */
						if ( i != ERR_SUCCESS ) break;
					}
					if ( j == CH375vSecPerClus ) 
					{  /* �ɹ����Ŀ¼ */
						mCmdParam.Modify.mFileSize = 0;  /* Ŀ¼�ĳ�������0 */
						mCmdParam.Modify.mFileDate = 0xFFFF;
						mCmdParam.Modify.mFileTime = 0xFFFF;
						mCmdParam.Modify.mFileAttr = 0x10;  /* ��Ŀ¼���� */
						i = CH375FileModify( );  /* ���ļ���Ϣ�޸�ΪĿ¼ */
					}
				}
			}
		}
	}
	return( i );
}
/**************************************************************
** ������:ReadFile
** ����:��ȡ�ļ���ָ��������
** ע������:��Ҫ���ļ�����ܵ���, 
** ����ֵΪ�������,buf:����ָ��,len Ҫ��ȡ��ֵ,cnt�Ѷ�ȡ��ֵ
** ����ʹ�ö������ķ�ʽ��ȡ�ļ�,����ļ���ƫ���ǿ�������,����� 
** �ڲ��ж�Ӧ�Ĵ���ʽ 
**		���û��д,�ٵ���˵~
***************************************************************/
u8 ReadFile(u8* buf,u32 len,u32* cnt)
{
	return ERR_SUCCESS;
}

/**************************************************************
** ������:WriteFile
** ����:д�ļ�
** ע������:1.�����˹��ɵĻ�����,��Ȼ�����ٶȻ������½�,������ʹ����д�ĸ��淶������������ֲ 
**  		
**  		2.Ϊ���ܼӿ��ٶ�,���ɻ���ֻ���ڴ���д�뻺������һ�����������,Ҳ����˵,���len����һ������,��������������
**  		����ֱ��д�뷽ʽ
			3.�˺�����Ч�ʻ��д����
***************************************************************/
u8 WriteFile(u8* buf,u32 len)
{
	u32 i;
	u8* tmp_buf;
	u8 rtn;
	
	if(len==0)
	{
		return ERR_SUCCESS;
	}

	//ÿ��ֻд��һ������
	i=0;
	tmp_buf=buf;
	mCmdParam.Write.mSectorCount=1;
	//��Ƭ����д��
	while(len>=CH375vSectorSize)
	{
		len-=CH375vSectorSize;
		mCmdParam.WriteX.mDataBuffer =tmp_buf;
		i++;
		tmp_buf=buf+i*CH375vSectorSize;
		rtn=CH375FileWriteX();
		if(rtn!=ERR_SUCCESS)
		{
			return rtn;
		}
		//ʵʱ�޸��ļ���С
		File_Size+=CH375vSectorSize;
	}
	//����д��
	if(len)
	{
		//���˵����ɻ�����
		for(i=0;i<len;i++)
		{
			FILE_DATA_BUF[i]=*tmp_buf++;
		}
		mCmdParam.WriteX.mDataBuffer=FILE_DATA_BUF;
		rtn=CH375FileWriteX();
		if(rtn!=ERR_SUCCESS)
		{
			return rtn;
		}
		//ʵʱ�޸��ļ���С
		File_Size+=len;

		//����д�����޸�FAT�ײ㲿��,ʹ���СΪ��ʵ��С
		mCmdParam.Modify.mFileSize = File_Size;   /* �������: �µ��ļ�����,����ģʽ���漰����ͷ���ݲ����Զ����³��� */
		mCmdParam.Modify.mFileAttr = 0xff;  /* �������: �µ��ļ�����,Ϊ0FFH���޸� */
		mCmdParam.Modify.mFileTime = 0xffff;  /* �������: �µ��ļ�ʱ��,Ϊ0FFH���޸� */
		mCmdParam.Modify.mFileDate = 0xffff;  /* �������: �µ��ļ�����,Ϊ0FFH���޸� */
		rtn=CH375FileModify();   /* �޸ĵ�ǰ�ļ�����Ϣ,�޸��ļ����� */

	}

	return(rtn);
}

/**************************************************************
** ������:LocatFile
** ����:��λ�ļ�ָ��
** ע������:0xffffffffΪ�ƶ����ļ�ĩβ
***************************************************************/
u8 LocatFile(u32 offest)
{
	mCmdParam.Locate.mSectorOffset = offest;
	return(CH375FileLocate());
}
u32 GetLocat(void)
{
	return 0;
}
/**************************************************************

***************************************************************/
u8 ReadOneSector(u8* buf)
{
	mCmdParam.WriteX.mDataBuffer =buf;
	return( CH375FileReadX( ) );
}
