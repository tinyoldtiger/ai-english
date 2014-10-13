#include <reg52.h>
#include <stdio.h>

#define	USER_KEY_IN				INT1	/* P3.3, INT1, Ĭ��Ϊ�ߵ�ƽ, ���û�������Ϊ�͵�ƽ, �����������ѯ */

/* ���¶������ϸ˵���뿴CH375HF4.H�ļ� */
#define LIB_CFG_DISK_IO			1		/* ���̶�д�����ݵĸ��Ʒ�ʽ,1Ϊ"��DPTR����",2Ϊ"˫DPTR����",3Ϊ"��DPTR��P2+R0����" */
#define LIB_CFG_FILE_IO			1		/* �ļ���д�����ݵĸ��Ʒ�ʽ,0Ϊ"�ⲿ�ӳ���",1Ϊ"��DPTR����",2Ϊ"˫DPTR����",3Ϊ"��DPTR��P2+R0����" */
#define LIB_CFG_INT_EN			0		/* CH375��INT#�������ӷ�ʽ,0Ϊ"��ѯ��ʽ",1Ϊ"�жϷ�ʽ" */

#define CH375_CMD_PORT_ADDR		0xBeF1	/* CH375����˿ڵ�I/O��ַ */
#define CH375_DAT_PORT_ADDR		0xBCF0	/* CH375���ݶ˿ڵ�I/O��ַ */
/* ֻʹ�õ�Ƭ�����õ�1KB�ⲿRAM: 0000H-01FFH Ϊ���̶�д������, ���ֽ�Ϊ��λ��д�ļ�����Ҫ�ļ����ݶ�д������FILE_DATA_BUF */
#define	DISK_BASE_BUF_ADDR		0x0000	/* �ⲿRAM�Ĵ������ݻ���������ʼ��ַ,�Ӹõ�Ԫ��ʼ�Ļ���������ΪSECTOR_SIZE */

#define CH375_INT_WIRE			INT0	/* P3.2, INT0, CH375���ж���INT#����,����CH375��INT#����,���ڲ�ѯ�ж�״̬ */

#define NO_DEFAULT_CH375_F_ENUM		1		/* δ����CH375FileEnumer����ʽ�ֹ�Խ�Լ���� */
#define NO_DEFAULT_CH375_F_QUERY	1		/* δ����CH375FileQuery����ʽ�ֹ�Խ�Լ���� */

#include "CH375HF4.H"				/* �������Ҫ֧��FAT32,��ô��ѡ��CH375HF4.H */

#ifdef __C51__
#pragma NOAREGS
#endif

/* ��P1.4����һ��LED���ڼ����ʾ����Ľ���,�͵�ƽLED��,��������ʱ��,����ʱ�� */
sbit P1_4  = P1^4;
#define LED_OUT_INIT( )		{ P1_4 = 1; }	/* P1.4 �ߵ�ƽ */
#define LED_OUT_ACT( )		{ P1_4 = 0; }	/* P1.4 �͵�ƽ����LED��ʾ */
#define LED_OUT_INACT( )	{ P1_4 = 1; }	/* P1.4 �͵�ƽ����LED��ʾ */
sbit P1_5  = P1^5;
/* ��P1.5����һ��LED���ڼ����ʾ����Ľ���,�͵�ƽLED��,��U�̲������ */
#define LED_UDISK_IN( )		{ P1_5 = 0; }	/* P1.5 �͵�ƽ����LED��ʾ */
#define LED_UDISK_OUT( )	{ P1_5 = 1; }	/* P1.5 �͵�ƽ����LED��ʾ */
sbit P1_6  = P1^6;
/* ��P1.6����һ��LED���ڼ����ʾ����Ľ���,�͵�ƽLED��,����U��д����ʱ�� */
#define LED_WR_NOW( )		{ P1_6 = 0; }	/* P1.6 �͵�ƽ����LED��ʾ */
#define LED_NOT_WR( )		{ P1_6 = 1; }	/* P1.6 �͵�ƽ����LED��ʾ */
sbit P1_7  = P1^7;
/* ��P1.7����һ��LED���ڼ�ص�ǰUSBģʽ,��ΪUSB�豸��ʽ,��ΪUSB������ʽ */
#define LED_DEVICE( )		{ P1_7 = 0; }	/* P1.7 �͵�ƽ����LED��ʾ */
#define LED_HOST( )			{ P1_7 = 1; }	/* P1.7 �͵�ƽ����LED��ʾ */

/* �����ӳ��� */
void	mDelaymS( UINT8 delay );
UINT8	IsKeyPress( void );
void	device( void );
void	host( void );