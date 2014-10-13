; 2004.06.05, 2004.09.20, 2004.10.22, 2004.11.20, 2004.12.12, 2004.12.28, 2005.01.04, 2005.01.12, 2005.01.26, 2005.03.01, 2005.07.29, 2005.12.28, 2006.08.02, 2007.08.16
;****************************************
;**  Copyright  (C)  W.ch  1999-2007   **
;**  Web:  http://www.winchiphead.com  **
;****************************************
;**  USB Host File Interface for CH375 **
;**  TC2.0@PC, KC7.0@MCS51             **
;****************************************
;
; CH375 �����ļ�ϵͳ�ӿ� V3.5 */
; ֧��: FAT12/FAT16/FAT32 */
; MCS51��Ƭ��, ��ѯ��ʽ�����жϷ�ʽ, ֧��С/��/��ģʽ���� */
; ֧��3�����ݴ�ȡ��ʽ: ��ͨ�ĵ�DPTR�л���ʽ, ATMEL/PHILIPS/SST�ȵ�Ƭ����˫DPTR�л���ʽ, ��P2+R0ָ��˿ڶ���DPTRָ���ⲿRAM�ķ�ʽ */
; U���ļ���д������ASM����ͷ�ļ� */
; CH375HF4��CH375HF6.LIB���Ż��棬��Ҫ���֧��CH375BоƬ����֧���ⲿ�ӳ����Ʒ�ʽ */
;
CH375_LIB_VER		EQU		35H

; *********************************************************************************************************************
; Ӳ������

CH375_MAX_DATA_LEN	EQU     40H							;������ݰ��ĳ���, �������ĳ���

; *********************************************************************************************************************
; �������

CMD_GET_IC_VER		EQU     01H							;��ȡоƬ���̼��汾
; ���: �汾��( λ7Ϊ1, λ6Ϊ0, λ5~λ0Ϊ�汾�� )
;           CH375B���ذ汾�ŵ�ֵΪ0B7H���汾��Ϊ37H

CMD_ENTER_SLEEP		EQU     03H							;����˯��״̬

CMD_SET_USB_SPEED	EQU     04H							;����USB�����ٶ�, ��ÿ��CMD_SET_USB_MODE����USB����ģʽʱ���Զ��ָ���12Mbpsȫ��
; ����: �����ٶȴ���
;           00H=12Mbpsȫ��FullSpeed��Ĭ��ֵ��, 01H=1.5Mbps�����޸�Ƶ�ʣ�, 02H=1.5Mbps����LowSpeed
CMD_SET_SYS_FREQ	EQU     CMD_SET_USB_SPEED

CMD_RESET_ALL		EQU     05H							;ִ��Ӳ����λ

CMD_CHECK_EXIST		EQU     06H							;���Թ���״̬
; ����: ��������
; ���: �������ݵİ�λȡ��

CMD_GET_TOGGLE		EQU     0AH							;��ȡOUT�����ͬ��״̬
; ����: ����1AH
; ���: ͬ��״̬
;           λ4Ϊ1��OUT����ͬ��, ����OUT����ͬ��

CMD_CHK_SUSPEND		EQU     0BH							;�豸��ʽ: ���ü��USB���߹���״̬�ķ�ʽ
; ����: ����10H, ��鷽ʽ
;                    00H=�����USB����, 04H=��50mSΪ������USB����, 05H=��10mSΪ������USB����

CMD_DELAY_100US		EQU     0FH							;���ڷ�ʽ: ��ʱ100uS
; ���: ��ʱ�ڼ����0, ��ʱ���������0

CMD_SET_USB_ID		EQU     12H							;�豸��ʽ: ����USB����VID�Ͳ�ƷPID
; ����: ����ID���ֽ�, ����ID���ֽ�, ��ƷID���ֽ�, ��ƷID���ֽ�

CMD_SET_USB_ADDR	EQU     13H							;����USB��ַ
; ����: ��ֵַ

CMD_SET_USB_MODE	EQU     15H							;����USB����ģʽ
; ����: ģʽ����
;       00H=δ���õ��豸��ʽ, 01H=�����õ��豸��ʽ����ʹ���ⲿ�̼�ģʽ, 02H=�����õ��豸��ʽ����ʹ�����ù̼�ģʽ
;       04H=δ���õ�������ʽ, 05H=�����õ�������ʽ, 06H=�����õ�������ʽ�����Զ�����SOF��, 07H=�����õ�������ʽ���Ҹ�λUSB����
; ���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� )

CMD_SET_ENDP2		EQU     18H							;�豸��ʽ: ����USB�˵�0�Ľ�����
; ����: ������ʽ
;           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ����
;           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL

CMD_SET_ENDP3		EQU     19H							;�豸��ʽ: ����USB�˵�0�ķ�����
; ����: ������ʽ
;           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ����
;           λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL

CMD_SET_ENDP4		EQU     1AH							;�豸��ʽ: ����USB�˵�1�Ľ�����
; ����: ������ʽ
;           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ����
;           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL

CMD_SET_ENDP5		EQU     1BH							;�豸��ʽ: ����USB�˵�1�ķ�����
; ����: ������ʽ
;           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ����
;           λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL

CMD_SET_ENDP6		EQU     1CH							;����USB�˵�2/�����˵�Ľ�����
; ����: ������ʽ
;           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ����
;           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-������������ACK, 1110-��æNAK, 1111-����STALL

CMD_SET_ENDP7		EQU     1DH							;����USB�˵�2/�����˵�ķ�����
; ����: ������ʽ
;           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ����
;           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-����������Ӧ��, 1110-��æNAK, 1111-����STALL

CMD_GET_STATUS		EQU     22H							;��ȡ�ж�״̬��ȡ���ж�����
; ���: �ж�״̬

CMD_UNLOCK_USB		EQU     23H							;�豸��ʽ: �ͷŵ�ǰUSB������

CMD_RD_USB_DATA0	EQU     27H							;�ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ�
; ���: ����, ������

CMD_RD_USB_DATA		EQU     28H							;�ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ�, ���ͷŻ�����, �൱�� CMD_RD_USB_DATA0 + CMD_UNLOCK_USB
; ���: ����, ������

CMD_WR_USB_DATA3	EQU     29H							;�豸��ʽ: ��USB�˵�0�ķ��ͻ�����д�����ݿ�
; ����: ����, ������

CMD_WR_USB_DATA5	EQU     2AH							;�豸��ʽ: ��USB�˵�1�ķ��ͻ�����д�����ݿ�
; ����: ����, ������

CMD_WR_USB_DATA7	EQU     2BH							;��USB�˵�2���������˵�ķ��ͻ�����д�����ݿ�
; ����: ����, ������

; **************************************************************************
; ������������USB������ʽ, ֻ��CH375֧��

CMD_SET_BAUDRATE	EQU     02H							;������ʽ & ���ڷ�ʽ: ���ô���ͨѶ������
; ����: �����ʷ�Ƶϵ��, �����ʷ�Ƶ����
; ���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� )

CMD_GET_MAX_LUN		EQU		0AH							;������ʽ: ��ȡUSB�洢������߼���Ԫ��
; ����: ����38H
; ���: ����߼���Ԫ��

CMD_SET_RETRY		EQU     0BH							;������ʽ: ����USB������������Դ���
; ����: ����25H, ���Դ���
;                    λ7Ϊ0���յ�NAKʱ������, λ7Ϊ1λ6Ϊ0���յ�NAKʱ��������, λ7Ϊ1λ6Ϊ1���յ�NAKʱ�������2��, λ5~λ0Ϊ��ʱ������Դ���

CMD_SET_DISK_LUN	EQU     0BH							;������ʽ: ����USB�洢���ĵ�ǰ�߼���Ԫ��
; ����: ����34H, �µĵ�ǰ�߼���Ԫ��(00H-0FH)

CMD_SET_PKT_P_SEC	EQU     0BH							;������ʽ: ����USB�洢����ÿ�������ݰ�����
; ����: ����39H, �µ�ÿ�������ݰ�����(08H,10H,20H,40H)

CMD_TEST_CONNECT	EQU     16H							;������ʽ: ���USB�豸����״̬
; ���: ״̬( USB_INT_CONNECT��USB_INT_DISCONNECT��USB_INT_USB_READY, ����ֵ˵������δ��� )

CMD_ABORT_NAK		EQU     17H							;������ʽ: ������ǰNAK������
;
CMD_CLR_STALL		EQU     41H							;������ʽ: ���ƴ���-����˵����
; ����: �˵��
; ����ж�

CMD_SET_ADDRESS		EQU     45H							;������ʽ: ���ƴ���-����USB��ַ
; ����: ��ֵַ
; ����ж�

CMD_GET_DESCR		EQU     46H							;������ʽ: ���ƴ���-��ȡ������
; ����: ����������
; ����ж�

CMD_SET_CONFIG		EQU     49H							;������ʽ: ���ƴ���-����USB����
; ����: ����ֵ
; ����ж�

CMD_AUTO_SETUP		EQU     4DH							;������ʽ: �Զ�����USB�豸
; ����ж�

CMD_ISSUE_TKN_X		EQU     4EH							;������ʽ: ����ͬ������, ִ������, ������ɴ��� CMD_SET_ENDP6/CMD_SET_ENDP7 + CMD_ISSUE_TOKEN
; ����: ͬ����־, ��������
;           ͬ����־��λ7Ϊ�����˵�IN��ͬ������λ, λ6Ϊ�����˵�OUT��ͬ������λ, λ5~λ0����Ϊ0
;           �������Եĵ�4λ������, ��4λ�Ƕ˵��
; ����ж�

CMD_ISSUE_TOKEN		EQU     4FH							;������ʽ: ��������, ִ������
; ����: ��������
;           ��4λ������, ��4λ�Ƕ˵��
; ����ж�

CMD_DISK_BOC_CMD	EQU     50H							;������ʽ: ��USB�洢��ִ��BulkOnly����Э�������
; ����ж�

CMD_DISK_INIT		EQU     51H							;������ʽ: ��ʼ��USB�洢��
; ����ж�

CMD_DISK_RESET		EQU     52H							;������ʽ: ���ƴ���-��λUSB�洢��
; ����ж�

CMD_DISK_SIZE		EQU     53H							;������ʽ: ��ȡUSB�洢��������
; ����ж�

CMD_DISK_READ		EQU     54H							;������ʽ: ��USB�洢�������ݿ�(������Ϊ��λ)
; ����: LBA������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH)
; ����ж�

CMD_DISK_RD_GO		EQU     55H							;������ʽ: ����ִ��USB�洢���Ķ�����
; ����ж�

CMD_DISK_WRITE		EQU     56H							;������ʽ: ��USB�洢��д���ݿ�(������Ϊ��λ)
; ����: LBA������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH)
; ����ж�

CMD_DISK_WR_GO		EQU     57H							;������ʽ: ����ִ��USB�洢����д����
; ����ж�

CMD_DISK_INQUIRY	EQU     58H							;������ʽ: ��ѯUSB�洢������
; ����ж�

CMD_DISK_READY		EQU     59H							;������ʽ: ���USB�洢������
; ����ж�

CMD_DISK_R_SENSE	EQU     5AH							;������ʽ: ���USB�洢������
; ����ж�

CMD_DISK_MAX_LUN	EQU     5DH							;������ʽ: ���ƴ���-��ȡUSB�洢������߼���Ԫ��
; ����ж�

; *********************************************************************************************************************
; ����״̬

CMD_RET_SUCCESS		EQU     51H							;��������ɹ�
CMD_RET_ABORT		EQU     5FH							;�������ʧ��

; *********************************************************************************************************************
; USB�ж�״̬

; ����״̬����Ϊ�����¼��ж�, ���ͨ��CMD_CHK_SUSPEND����USB���߹�����, ��ô���봦��USB���߹����˯�߻��ѵ��ж�״̬
USB_INT_USB_SUSPEND	EQU     05H							;USB���߹����¼�
USB_INT_WAKE_UP		EQU     06H							;��˯���б������¼�

; ����״̬����0XH����USB�豸��ʽ
;   ���ù̼�ģʽ��ֻ��Ҫ����: USB_INT_EP1_OUT, USB_INT_EP1_IN, USB_INT_EP2_OUT, USB_INT_EP2_IN
;   λ7-λ4Ϊ0000
;   λ3-λ2ָʾ��ǰ����, 00=OUT, 10=IN, 11=SETUP
;   λ1-λ0ָʾ��ǰ�˵�, 00=�˵�0, 01=�˵�1, 10=�˵�2, 11=USB���߸�λ
USB_INT_EP0_SETUP	EQU     0CH							;USB�˵�0��SETUP
USB_INT_EP0_OUT		EQU     00H							;USB�˵�0��OUT
USB_INT_EP0_IN		EQU     08H							;USB�˵�0��IN
USB_INT_EP1_OUT		EQU     01H							;USB�˵�1��OUT
USB_INT_EP1_IN		EQU     09H							;USB�˵�1��IN
USB_INT_EP2_OUT		EQU     02H							;USB�˵�2��OUT
USB_INT_EP2_IN		EQU     0AH							;USB�˵�2��IN
;USB_INT_BUS_RESET	EQU     0000XX11B					;USB���߸�λ
USB_INT_BUS_RESET1	EQU     03H							;USB���߸�λ
USB_INT_BUS_RESET2	EQU     07H							;USB���߸�λ
USB_INT_BUS_RESET3	EQU     0BH							;USB���߸�λ
USB_INT_BUS_RESET4	EQU     0FH							;USB���߸�λ

; ����״̬����2XH-3XH����USB������ʽ��ͨѶʧ�ܴ���, ��CH375֧��
;   λ7-λ6Ϊ00
;   λ5Ϊ1
;   λ4ָʾ��ǰ���յ����ݰ��Ƿ�ͬ��
;   λ3-λ0ָʾ����ͨѶʧ��ʱUSB�豸��Ӧ��: 0010=ACK, 1010=NAK, 1110=STALL, 0011=DATA0, 1011=DATA1, XX00=��ʱ
;USB_INT_RET_ACK	EQU     001X0010B					;����:����IN���񷵻�ACK
;USB_INT_RET_NAK	EQU     001X1010B					;����:����NAK
;USB_INT_RET_STALL	EQU     001X1110B					;����:����STALL
;USB_INT_RET_DATA0	EQU     001X0011B					;����:����OUT/SETUP���񷵻�DATA0
;USB_INT_RET_DATA1	EQU     001X1011B					;����:����OUT/SETUP���񷵻�DATA1
;USB_INT_RET_TOUT	EQU     001XXX00B					;����:���س�ʱ
;USB_INT_RET_TOGX	EQU     0010X011B					;����:����IN���񷵻����ݲ�ͬ��
;USB_INT_RET_PID	EQU     001XXXXXB					;����:δ����

; ����״̬����1XH����USB������ʽ�Ĳ���״̬����, ��CH375֧��

USB_INT_SUCCESS		EQU     14H							;USB������ߴ�������ɹ�
USB_INT_CONNECT		EQU     15H							;��⵽USB�豸�����¼�
USB_INT_DISCONNECT	EQU     16H							;��⵽USB�豸�Ͽ��¼�
USB_INT_BUF_OVER	EQU     17H							;USB���ƴ��������̫��, ���������
USB_INT_USB_READY	EQU     18H							;USB�豸�Ѿ�����ʼ�����ѷ���USB��ַ��
USB_INT_DISK_READ	EQU     1DH							;USB�洢�������ݿ�, �������ݶ���
USB_INT_DISK_WRITE	EQU     1EH							;USB�洢��д���ݿ�, ��������д��
USB_INT_DISK_ERR	EQU     1FH							;USB�洢������ʧ��

; *********************************************************************************************************************
; ����USB����

; USB�İ���ʶPID, ������ʽ�����õ�
DEF_USB_PID_NULL	EQU     00H							;����PID, δ����
DEF_USB_PID_SOF		EQU     05H
DEF_USB_PID_SETUP	EQU     0DH
DEF_USB_PID_IN		EQU     09H
DEF_USB_PID_OUT		EQU     01H
DEF_USB_PID_ACK		EQU     02H
DEF_USB_PID_NAK		EQU     0AH
DEF_USB_PID_STALL	EQU     0EH
DEF_USB_PID_DATA0	EQU     03H
DEF_USB_PID_DATA1	EQU     0BH
DEF_USB_PID_PRE		EQU     0CH

; USB��������, ���ù̼�ģʽ�����õ�
DEF_USB_REQ_READ	EQU     80H							;���ƶ�����
DEF_USB_REQ_WRITE	EQU     00H							;����д����
DEF_USB_REQ_TYPE	EQU     60H							;������������
DEF_USB_REQ_STAND	EQU     00H							;��׼����
DEF_USB_REQ_CLASS	EQU     20H							;�豸������
DEF_USB_REQ_VENDOR	EQU     40H							;��������
DEF_USB_REQ_RESERVE	EQU     60H							;��������

; USB��׼�豸����, RequestType��λ6λ5=00(Standard), ������ʽ�����õ�
DEF_USB_CLR_FEATURE	EQU     01H
DEF_USB_SET_FEATURE	EQU     03H
DEF_USB_GET_STATUS	EQU     00H
DEF_USB_SET_ADDRESS	EQU     05H
DEF_USB_GET_DESCR	EQU     06H
DEF_USB_SET_DESCR	EQU     07H
DEF_USB_GET_CONFIG	EQU     08H
DEF_USB_SET_CONFIG	EQU     09H
DEF_USB_GET_INTERF	EQU     0AH
DEF_USB_SET_INTERF	EQU     0BH
DEF_USB_SYNC_FRAME	EQU     0CH

; *********************************************************************************************************************

; ���صĲ���״̬�� */
; �������ж�״̬��,������CH375IntStatus
; �������¼�֪ͨ״̬��,��⵽��ǰU���Ѿ����ӻ����Ѿ��Ͽ�,������Ϊ����״̬�� */
ERR_USB_CONNECT		EQU		015H	; ��⵽USB�豸�����¼�,�����Ѿ����� */
ERR_USB_DISCON		EQU		016H	; ��⵽USB�豸�Ͽ��¼�,�����Ѿ��Ͽ� */
; �����ǽ׶��Ե�״̬��,�����������ݽ���,�������յĲ���״̬ */
;USB_INT_DISK_READ	EQU		01DH	; USB�洢�������ݿ�,ֻ����CMD_FileRead����,�������ݶ��� */
;USB_INT_DISK_WRITE	EQU		01EH	; USB�洢��д���ݿ�,ֻ����CMD_FileWrite����,��������д�� */
ERR_USB_DISK_ERR	EQU		01FH	; USB�洢������ʧ��,�ڳ�ʼ��ʱ������USB�洢����֧��,�ڶ�д�����п����Ǵ����𻵻����Ѿ��Ͽ� */
; ����״̬�� */
ERR_SUCCESS			EQU		000H	; �����ɹ� */
ERR_CH375_ERROR		EQU		081H	; CH375Ӳ������,������Ҫ��λCH375 */
ERR_DISK_DISCON		EQU		082H	; ��⵽USB�豸�����¼�,�����Ѿ��Ͽ�,���ߴ�����δ���� */
ERR_STATUS_ERR		EQU		083H	; ����״̬����,�����������ӻ��߶Ͽ����� */
ERR_MBR_ERROR		EQU		091H	; ���̵���������¼��Ч,���ܴ�����δ����������δ��ʽ�� */
ERR_TYPE_ERROR		EQU		092H	; ���̷������Ͳ�֧��,ֻ֧��FAT12/FAT16/BigDOS/FAT32,��Ҫ�ɴ��̹����������·��� */
ERR_BPB_ERROR		EQU		0A1H	; ������δ��ʽ��,���߲�������,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
ERR_TOO_LARGE		EQU		0A2H	; ���̷�������ʽ��������������4GB,������������250GB,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
ERR_FAT_ERROR		EQU		0A3H	; ���̵��ļ�ϵͳ��֧��,ֻ֧��FAT12/FAT16/FAT32,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
ERR_DISK_FULL		EQU		0B1H	; �����ļ�̫��,ʣ��ռ�̫�ٻ����Ѿ�û��,��Ҫ�������� */
ERR_FDT_OVER		EQU		0B2H	; Ŀ¼���ļ�̫��,û�п��е�Ŀ¼��,FAT12/FAT16��Ŀ¼�µ��ļ���Ӧ������500��,��Ҫ�������� */
ERR_MISS_DIR		EQU		0B3H	; ָ��·����ĳ����Ŀ¼û���ҵ�,������Ŀ¼���ƴ��� */
ERR_FILE_CLOSE		EQU		0B4H	; �ļ��Ѿ��ر�,�����Ҫʹ��,Ӧ�����´��ļ� */
ERR_OPEN_DIR		EQU		041H	; ָ��·����Ŀ¼���� */
ERR_MISS_FILE		EQU		042H	; ָ��·�����ļ�û���ҵ�,�������ļ����ƴ��� */
ERR_FOUND_NAME		EQU		043H	; ��������ͨ�����ƥ����ļ���,�ļ�����������·�������������,�����Ҫʹ��,Ӧ�ô򿪸��ļ� */
; ����������δ���� */

; ********************************************************************************************************************* */
; ���̼��ļ�״̬,������CH375DiskStatus */
DISK_UNKNOWN		EQU		000H	; ��δ��ʼ��,δ֪״̬ */
DISK_DISCONNECT		EQU		001H	; ����û�����ӻ����Ѿ��Ͽ� */
DISK_CONNECT		EQU		002H	; �����Ѿ�����,������δ��ʼ�������޷�ʶ��ô��� */
DISK_MOUNTED		EQU		003H	; �����Ѿ���ʼ���ɹ�,������δ�����ļ�ϵͳ�����ļ�ϵͳ��֧�� */
DISK_READY			EQU		010H	; �Ѿ��������̵��ļ�ϵͳ�����ܹ�֧�� */
DISK_OPEN_ROOT		EQU		012H	; �Ѿ��򿪸�Ŀ¼,����ģʽ,ֻ��������Ϊ��λ��дĿ¼������,ʹ�ú����ر�,ע��FAT12/FAT16��Ŀ¼�ǹ̶����� */
DISK_OPEN_DIR		EQU		013H	; �Ѿ�����Ŀ¼,����ģʽ,ֻ��������Ϊ��λ��дĿ¼������ */
DISK_OPEN_FILE		EQU		014H	; �Ѿ����ļ�,����ģʽ,����������Ϊ��λ�������ݶ�д */
DISK_OPEN_FILE_B	EQU		015H	; �Ѿ����ļ�,�ֽ�ģʽ,�������ֽ�Ϊ��λ�������ݶ�д */

; ********************************************************************************************************************* */
; FAT���ͱ�־,������CMD_PARAM.Query.mDiskFat */
DISK_FS_UNKNOWN		EQU		0		; δ֪���ļ�ϵͳ */
DISK_FAT12			EQU		1		; FAT12�ļ�ϵͳ */
DISK_FAT16			EQU		2		; FAT16�ļ�ϵͳ */
DISK_FAT32			EQU		3		; FAT32�ļ�ϵͳ */

; ********************************************************************************************************************* */
; �ļ�����,������CMD_PARAM.Modify.mFileAttr */
ATTR_READ_ONLY		EQU		001H	; �ļ�Ϊֻ������ */
ATTR_HIDDEN			EQU		002H	; �ļ�Ϊ�������� */
ATTR_SYSTEM			EQU		004H	; �ļ�Ϊϵͳ���� */
ATTR_VOLUME_ID		EQU		008H	; ���� */
ATTR_DIRECTORY		EQU		010H	; ��Ŀ¼ */
ATTR_ARCHIVE		EQU		020H	; �ļ�Ϊ�浵���� */
;ATTR_LONG_NAME			( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )
; �ļ����� unsigned char */
; bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
;  ֻ   ��   ϵ   ��   Ŀ   ��   δ����   */
;  ��   ��   ͳ   ��   ¼   ��            */
; �ļ�ʱ�� unsigned short,������CMD_PARAM.Modify.mFileTime */
; Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
; �ļ����� unsigned short,������CMD_PARAM.Modify.mFileDate */
; Date = ((Year-1980)<<9) + (Month<<5) + Day */

; ********************************************************************************************************************* */
; �ļ���,������CMD_PARAM.?.mPathName */
PATH_WILDCARD_CHAR	EQU		02AH	; ·������ͨ��� '*' */
PATH_SEPAR_CHAR1	EQU		05CH	; ·�����ķָ��� '\' */
PATH_SEPAR_CHAR2	EQU		02FH	; ·�����ķָ��� '/' */
#ifndef MAX_PATH_LEN
MAX_PATH_LEN		EQU		30		; ���·������,������б�ָܷ�����С���������Լ�·��������00H */
#endif
#ifndef MAX_BYTE_IO
MAX_BYTE_IO			EQU		( MAX_PATH_LEN - 1 )	; ���ֽ�Ϊ��λ���ζ�д�ļ�ʱ����󳤶�,�����ó��ȿ��Էֶ�ζ�д */
#endif

; �ⲿ��������ṹ, �����ڵ���CH375������е��ӳ���ʱ�ṩ����
;typedef union _CMD_PARAM {
;	struct {
;		UINT8	mBuffer[ MAX_PATH_LEN ];
;	} Other;
;	struct {
;		UINT32	mReserved;
;		UINT32	mTotalSector;			/* ����: ��ǰ�߼��̵��������� */
;		UINT32	mFreeSector;			/* ����: ��ǰ�߼��̵�ʣ�������� */
;		UINT8	mDiskFat;				/* ����: ��ǰ�߼��̵�FAT���� */
;	} Query;							/* CMD_DiskQuery, ��ѯ������Ϣ */
;	struct {
;		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��...,������00H], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
;	} Open;								/* CMD_FileOpen, ���ļ� */
;	struct {
;		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��(��ͨ���*)...,ö�����], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILE*",00H */
;	} Enumer;							/* CMD_FileEnumer, ö���ļ�,�����ļ��� */
;	struct {
;		UINT8	mUpdateLen;				/* �������: �Ƿ��������³���: 0��ֹ,1���� */
;	} Close;							/* CMD_FileClose, �رյ�ǰ�ļ� */
;	struct {
;		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��...,������00H], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
;	} Create;							/* CMD_FileCreate, �½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
;	struct {
;		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��...,������00H], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
;	} Erase;							/* CMD_FileErase, ɾ���ļ����ر� */
;	struct {
;		UINT32	mFileSize;				/* �������: �µ��ļ�����,Ϊ0FFFFFFFFH���޸�, ����: ԭ���� */
;		UINT16	mFileDate;				/* �������: �µ��ļ�����,Ϊ0FFFFH���޸�, ����: ԭ���� */
;		UINT16	mFileTime;				/* �������: �µ��ļ�ʱ��,Ϊ0FFFFH���޸�, ����: ԭʱ�� */
;		UINT8	mFileAttr;				/* �������: �µ��ļ�����,Ϊ0FFH���޸�, ����: ԭ���� */
;	} Modify;							/* CMD_FileQuery, ��ѯ��ǰ�ļ�����Ϣ; CMD_FileModify, ��ѯ�����޸ĵ�ǰ�ļ�����Ϣ */
;	struct {
;		UINT32	mSectorOffset;			/* �������: ����ƫ��,0���ƶ����ļ�ͷ,0FFFFFFFFH���ƶ����ļ�β, ����: ��ǰ�ļ�ָ���Ӧ�ľ�������������, 0FFFFFFFFH���ѵ��ļ�β */
;	} Locate;							/* CMD_FileLocate, �ƶ���ǰ�ļ�ָ�� */
;	struct {
;		UINT8	mSectorCount;			/* �������: ��ȡ������, ����: ʵ�ʶ�ȡ������ */
;	} Read;								/* CMD_FileRead, �ӵ�ǰ�ļ���ȡ���� */
;	struct {
;		UINT8	mSectorCount;			/* �������: д��������, ����: ʵ��д�������� */
;	} Write;							/* CMD_FileWrite, ��ǰ�ļ�д������ */
;	struct {
;		UINT8	mSectorCount;			/* �������: ��ȡ������, ����: ʵ�ʶ�ȡ������ */
;		UINT8	mReserved[7];
;		PUINT8X	mDataBuffer;			/* �������: ��������ʼ��ַ, ����: ��������ǰ��ַ */
;	} ReadX;							/* CMD_FileReadX, �ӵ�ǰ�ļ���ȡ���ݵ�ָ�������� */
;	struct {
;		UINT8	mSectorCount;			/* �������: д��������, ����: ʵ��д�������� */
;		UINT8	mReserved[7];
;		PUINT8X	mDataBuffer;			/* �������: ��������ʼ��ַ, ����: ��������ǰ��ַ */
;	} WriteX;							/* CMD_FileWriteX, ��ǰ�ļ�д��ָ�������������� */
;	struct {
;		UINT32	mDiskSizeSec;			/* ����: �����������̵��������� */
;	} DiskSize;							/* CMD_DiskSize, ��ѯ�������� */
;	struct {
;		UINT32	mByteOffset;			/* �������: ���ֽ�Ϊ��λ��ƫ����, ���ֽ�Ϊ��λ���ļ�ָ��, ����: ��ǰ�ļ�ָ���Ӧ�ľ�������������, 0FFFFFFFFH���ѵ��ļ�β */
;	} ByteLocate;						/* CMD_ByteLocate, ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
;	struct {
;		UINT8	mByteCount;				/* �������: ׼����ȡ���ֽ���,���ô���MAX_BYTE_IO, ����: ʵ�ʶ������ֽ��� */
;		UINT8	mByteBuffer[ MAX_BYTE_IO ];	/* ����: ���������ݿ� */
;	} ByteRead;							/* CMD_ByteRead, ���ֽ�Ϊ��λ�ӵ�ǰ�ļ���ȡ���ݿ� */
;	struct {
;		UINT8	mByteCount;				/* �������: ׼��д����ֽ���,���ô���MAX_BYTE_IO, ����: ʵ��д����ֽ��� */
;		UINT8	mByteBuffer[ MAX_BYTE_IO ];	/* �������: ׼��д������ݿ� */
;	} ByteWrite;						/* CMD_ByteWrite, ���ֽ�Ϊ��λ��ǰ�ļ�д�����ݿ� */
;	struct {
;		UINT8	mSaveVariable;			/* �������: Ϊ0��ָ�����U�̵ı���,Ϊ0x80��ָ����U�̵ı���,����ֵ�򱸷�/������� */
;		UINT8	mReserved[3];
;		PUINT8X	mBuffer;				/* �������: ָ���ӳ����ı����ı��ݻ�����,���Ȳ�С��80���ֽ� */
;	} SaveVariable;						/* CMD_SaveVariable, ����/����/�ָ��ӳ����ı��� */
;	union {
;		struct {
;			UINT32	mCBW_Sig;
;			UINT32	mCBW_Tag;
;			UINT8	mCBW_DataLen;		/* ����: ���ݴ��䳤��,��Чֵ��0��255 */
;			UINT8	mCBW_DataLen1;
;			UINT8	mCBW_DataLen2;
;			UINT8	mCBW_DataLen3;
;			UINT8	mCBW_Flag;			/* ����: ���䷽��ȱ�־ */
;			UINT8	mCBW_LUN;
;			UINT8	mCBW_CB_Len;		/* ����: �����ĳ���,��Чֵ��1��16 */
;			UINT8	mCBW_CB_Buf[6];		/* ����: �����,�û��������Ϊ16���ֽ� */
;		} mCBW;							/* BulkOnlyЭ��������, ����CBW�ṹ */
;		struct {
;			UINT32	mCSW_Sig;
;			UINT32	mCSW_Tag;
;			UINT32	mCSW_Residue;		/* ����: ʣ�����ݳ��� */
;			UINT8	mCSW_Status;		/* ����: ����ִ�н��״̬ */
;			UINT8	mReserved;
;		} mCSW;							/* BulkOnlyЭ�������״̬��, ���CSW�ṹ */
;	} BOC;								/* CMD_BulkOnlyCmd, ִ�л���BulkOnlyЭ�������, ��������ݴ�����ô������pDISK_BASE_BUF�� */
;} CMD_PARAM;

#define EN_DISK_WRITE			1
#define EN_DISK_FAT12			1
#define EN_DISK_FAT32			1		;ʹ��CH375HF4.LIBʱ���ֹ�ó�������
#define EN_BYTE_ACCESS			1
;#define EN_SAVE_VARIABLE		1
;#define EXT_BLK_INTERFACE		1
#define EN_SEC_SIZE_AUTO		1

; ********************************************************************************************************************* */
; �ζ���
CH375LIB_CODE			SEGMENT		CODE
CH375LIB_IDATA			SEGMENT		IDATA

; ********************************************************************************************************************* */
; �ӳ�������ṩ�ı��� */
	EXTRN	DATA (CH375IntStatus)	;CH375�������ж�״̬
	EXTRN	DATA (CH375DiskStatus)	;���̼��ļ�״̬
	EXTRN	DATA (CH375LibConfig)	;CH375���������,����˵��
; λ7: CH375��INT#�������ӷ�ʽ: 0��ѯ��ʽ,1�жϷ�ʽ */
; λ6: ��λΪ1��CH375Version2Ϊ1��оƬΪCH375B */
; λ5: ��д�����������Ƿ���ʱ: 0д����ʱ,1����ʱ */
; λ4: ���������ݺ��Ƿ��Զ������ļ�����: 0������,1�Զ����� */
; λ3λ2: ����ļ���д�Ķ��������ݵĸ��Ʒ�ʽ: 00��DPTR����, 01��DPTR����, 10˫DPTR����, 11��DPTR��P2+R0���� */
; λ1λ0: ��Դ��̶�д�ĵ��������ݵĸ��Ʒ�ʽ: 00��DPTR����, 01��DPTR����, 10˫DPTR����, 11��DPTR��P2+R0���� */

; ���CH375��INT#�������ӵ���Ƭ�����ж��������Ų���׼��ʹ���жϷ�ʽ,��ôLIB_CFG_INT_EN����Ϊ1,������Ϊ0�ɵ�Ƭ����ѯINT#���� */
; ����MCS51��Ƭ�������ⲿRAM�е�����ʱ�Ƚ���,����CH375�ĳ�����ṩ�����Ż��ٶȵķ�ʽ,��LIB_CFG_FILE_IO��LIB_CFG_DISK_IO�ж���:
;   ��ʽ0:
;   ��ʽ1:"��DPTR����", �������ݸ��Ʒ�ʽ, ʹ��һ��DPTR�����л�, ÿ����һ���ֽ���Ҫ16����������, �ٶ�����, ����������MCS51��Ƭ��,
;   ��ʽ2:"˫DPTR����", ����ض�Ӳ�������ݸ��Ʒ�ʽ, ʹ������DPTR, ÿ����һ���ֽ���Ҫ8.5����������, �ٶȽϿ�, ������ATMEL/PHILIPS/SST�Ⱦ���˫DPTR�ĵ�Ƭ��,
;   ��ʽ3:"��DPTR��P2+R0����", ��P2+R0ָ��CH375��I/O�˿ڲ�����DPTRָ���ⲿRAM�������ݸ���, ÿ����һ���ֽ���Ҫ6.25����������, �ٶ����,
;                       ���������б�׼��MCS51��Ƭ��, ����ĳЩ��Ƭ�����������õ��ⲿRAMʱ��ر�P2+R0�Ĺ���, ���Կ��ܲ�����,
;   �����ļ����ݶ�д,Ҳ����Ӧ�ó������CH375FileReadX��CH375FileWriteX�ӳ���ʱ:
;     �ڷ�ʽ1,2,3��,Ӧ�ó���ÿ�ε���CH375FileReadX��CH375FileWriteXʱ,CH375�ĳ���ⶼ���ָ������������ʼ��ַ��ʼ��д����,
;     ����: ĳ�ļ�����Ϊ1K(ռ��2������), �������CH375FileReadXʱ��1K(ָ��mCmdParam.Read.mSectorCountΪ2), ��ô1K����ȫ����ָ����������,
;           �����������Сֻ��0.5K, ��ô�����ζ�ȡ, ��һ�ε���CH375FileReadXʱ��0.5K, ��������0.5K���ݺ��ٵ���CH375FileReadX����һ��0.5K������

	EXTRN	DATA (CH375vDiskFat)	;�߼��̵�FAT��־:1=FAT12,2=FAT16,3=FAT32
	EXTRN	DATA (CH375vSecPerClus)	;�߼��̵�ÿ��������
	EXTRN	DATA (CH375vStartCluster)	;��ǰ�ļ�����Ŀ¼����ʼ�غ�,UINT32
	EXTRN	DATA (CH375vFileSize)	;��ǰ�ļ��ĳ���,UINT32
	EXTRN	DATA (CH375vCurrentOffset)	;��ǰ�ļ�ָ��,��ǰ��дλ�õ��ֽ�ƫ��

; FAT���������ļ�Ŀ¼��Ϣ */
;typedef struct _FAT_DIR_INFO {
;	UINT8	DIR_Name[11];				/* 00H,�ļ���,��11�ֽ�,���㴦��ո� */
;	UINT8	DIR_Attr;					/* 0BH,�ļ�����,�ο�ǰ���˵�� */
;	UINT8	DIR_NTRes;					/* 0CH */
;	UINT8	DIR_CrtTimeTenth;			/* 0DH,�ļ�������ʱ��,��0.1�뵥λ���� */
;	UINT16	DIR_CrtTime;				/* 0EH,�ļ�������ʱ�� */
;	UINT16	DIR_CrtDate;				/* 10H,�ļ����������� */
;	UINT16	DIR_LstAccDate;				/* 12H,���һ�δ�ȡ���������� */
;	UINT16	DIR_FstClusHI;				/* 14H */
;	UINT16	DIR_WrtTime;				/* 16H,�ļ��޸�ʱ��,�ο�ǰ��ĺ�MAKE_FILE_TIME */
;	UINT16	DIR_WrtDate;				/* 18H,�ļ��޸�����,�ο�ǰ��ĺ�MAKE_FILE_DATA */
;	UINT16	DIR_FstClusLO;				/* 1AH */
;	UINT32	DIR_FileSize;				/* 1CH,�ļ����� */
;} FAT_DIR_INFO;							/* 20H */

	EXTRN	BIT		(CH375Version2)		;оƬ�汾:0-CH375,1-CH375A/B
	EXTRN	XDATA	(CH375vDataStart)	;�߼��̵������������ʼLBA,UINT32
	EXTRN	DATA	(CH375vFdtLba)		;��ǰFDT���ڵ�LBA��ַ,UINT32
	EXTRN	DATA	(CH375vFdtOffset)	;��ǰFDT�������ڵ�ƫ�Ƶ�ַ,UINT16
	EXTRN	XDATA	(CH375vDiskRoot)	;����FAT16��Ϊ��Ŀ¼ռ��������,����FAT32��Ϊ��Ŀ¼��ʼ�غ�,UINT32
#ifdef EN_SEC_SIZE_AUTO
	EXTRN	XDATA	(CH375vSectorSize)	;���̵�������С,UINT16
#else
#define	CH375vSectorSize	512			;���̵�������С
#endif
	EXTRN	DATA	(pDISK_BASE_BUF)	;ָ���ⲿRAM�Ĵ������ݻ�����,���������Ȳ�С��CH375vSectorSize,��Ӧ�ó����ʼ��,UINT16,PUINT8X

	EXTRN	CODE	(CH375ReadBlock)	; �Ӵ��̶�ȡ������������ݵ��ⲿ�ӿڽ����� */
#ifdef EN_DISK_WRITE
	EXTRN	CODE	(CH375WriteBlock)	; ���ⲿ�ӿڽ������Ķ�����������ݿ�д����� */
#endif

#ifndef LIB_CFG_VALUE
#define	LIB_CFG_VALUE			05H		; CH375���������ֵ */
#endif

; ********************************************************************************************************************* */
; �ӳ�������ṩ���ӳ���, ������ɺ󷵻�״̬����R7�� */
; �����ӳ�����, �ļ������ӳ���CH375File*�ʹ��̲�ѯ�ӳ���CH375DiskQuery�����ܻ��õ��������ݻ�����pDISK_BASE_BUF,
;   �����п�����pDISK_BASE_BUF�б����˴�����Ϣ, ���Ա��뱣֤pDISK_BASE_BUF��������������;,
;   ���RAM����, Ҫ��pDISK_BASE_BUF��ʱ����������;, ��ô����ʱ�����������CH375DirtyBuffer������̻�����
	EXTRN	CODE (CH375GetVer)			; ��ȡ��ǰ�ӳ����İ汾�� */
	EXTRN	CODE (CH375Reset)			; ��λCH375 */
	EXTRN	CODE (CH375Init)			; ��ʼ��CH375 */
	EXTRN	CODE (CH375DiskConnect)		; �������Ƿ����� */
	EXTRN	CODE (CH375DiskReady)		; ��ѯ�����Ƿ�׼���� */
	EXTRN	CODE (CH375DirtyBuffer)		; ������̻����� */
	EXTRN	CODE (CH375FileOpen)		; ���ļ�����ö���ļ� */
	EXTRN	CODE (CH375FileClose)		; �رյ�ǰ�ļ� */
#ifdef EN_DISK_WRITE
	EXTRN	CODE (CH375FileErase)		; ɾ���ļ����ر� */
	EXTRN	CODE (CH375FileCreate)		; �½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
#endif
	EXTRN	CODE (CH375FileModify)		; ��ѯ�����޸ĵ�ǰ�ļ�����Ϣ */
	EXTRN	CODE (CH375FileLocate)		; �ƶ���ǰ�ļ�ָ�� */
	EXTRN	CODE (CH375FileReadX)		; �ӵ�ǰ�ļ���ȡ���ݵ�ָ�������� */
#ifdef EN_DISK_WRITE
	EXTRN	CODE (CH375FileWriteX)		; ��ǰ�ļ�д��ָ�������������� */
#endif
#ifdef EN_BYTE_ACCESS
	EXTRN	CODE (CH375ByteLocate)		; ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
	EXTRN	CODE (CH375ByteRead)		; ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
#ifdef EN_DISK_WRITE
	EXTRN	CODE (CH375ByteWrite)		; ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
#endif
#endif
	EXTRN	CODE (CH375DiskSize)		; ��ѯ�������� */
	EXTRN	CODE (CH375DiskQuery)		; ��ѯ������Ϣ */
#ifdef EN_SAVE_VARIABLE
	EXTRN	CODE (CH375SaveVariable)	; ����/����/�ָ��ӳ����ı���,�����ӳ�����ڶ��CH375оƬ֮������л� */
#endif
	EXTRN	CODE (CH375BulkOnlyCmd)		; ִ�л���BulkOnlyЭ������� */
	EXTRN	CODE (CH375sDiskReady)		; ��ѯ�����Ƿ�׼����,֧��CH375S */

; ��ͷ�ļ�����ΪCH375�ӳ��������Ҫ��I/O���ڴ���Դ,��������Ҫ����Ӳ���йص�Ŀ�����,
; ������ļ��Ǳ�������Ŀ�Ķ��Դ���������Ϊͷ�ļ�,��ôӦ��ֻ����һ��ͷ�ļ�������Դ�Ͳ�������,
; ����֮���ͷ�ļ�Ӧ�ñ����ȶ���CH375HF_NO_CODE,�Ӷ���ֹ��ͷ�ļ������ظ���Ŀ�����,����:
; #define	CH375HF_NO_CODE		1
; $include	(CH375HF?.INC)

#ifdef CH375HF_NO_CODE

	EXTRN	IDATA (mCmdParam)			; ������� */
	EXTRN	XDATA (CH375_CMD_PORT)		; CH375����˿ڵ�I/O��ַ */
	EXTRN	XDATA (CH375_DAT_PORT)		; CH375���ݶ˿ڵ�I/O��ַ */
#ifdef DISK_BASE_BUF_LEN
	EXTRN	XDATA (DISK_BASE_BUF)		; �ⲿRAM�Ĵ������ݻ�����,����������Ϊһ�������ĳ��� */
#endif
#ifdef FILE_DATA_BUF_LEN
	EXTRN	XDATA (FILE_DATA_BUF)		; �ⲿRAM���ļ����ݻ�����,���������Ȳ�С��һ�ζ�д�����ݳ��� */
	EXTRN	CODE (CH375FileRead)		; �ӵ�ǰ�ļ���ȡ���� */
#ifdef EN_DISK_WRITE
	EXTRN	CODE (CH375FileWrite)		; ��ǰ�ļ�д������ */
#endif
#endif
#ifndef NO_DEFAULT_CH375_F_ENUM
	EXTRN	CODE (CH375FileEnumer)		; ö���ļ� */
#endif
#ifndef NO_DEFAULT_CH375_F_QUERY
	EXTRN	CODE (CH375FileQuery)		; ��ѯ��ǰ�ļ�����Ϣ */
#endif
	EXTRN	CODE (xQueryInterrupt)		; �ⲿ����ı�CH375�������õ��ӳ���,��ѯCH375�жϲ������ж�״̬ */
	EXTRN	CODE (xDelay100uS)			; �ⲿ����ı�CH375�������õ��ӳ���,��ʱ100uS */
#ifdef EN_DISK_WRITE
	EXTRN	CODE (xDelayAfterWrite)		; �ⲿ����ı�CH375�������õ��ӳ���,д��������ʱ */
#endif
	EXTRN	CODE (xFileNameEnumer)		; �ⲿ����ı�CH375�������õ��ӳ���,�ļ���ö�ٻص��ӳ��� */
	EXTRN	CODE (CH375LibInit)			; ��ʼ��CH375������CH375оƬ

#else

; ********************************************************************************************************************* */
; �ⲿ����ı�CH375�������õı���
	PUBLIC	mCmdParam					; ������� */
	PUBLIC	CH375_CMD_PORT				; CH375����˿ڵ�I/O��ַ */
	PUBLIC	CH375_DAT_PORT				; CH375���ݶ˿ڵ�I/O��ַ */
#ifdef DISK_BASE_BUF_LEN
	PUBLIC	DISK_BASE_BUF				; �ⲿRAM�Ĵ������ݻ�����,����������Ϊһ�������ĳ��� */
#endif
#ifdef FILE_DATA_BUF_LEN
	PUBLIC	FILE_DATA_BUF				; �ⲿRAM���ļ����ݻ�����,���������Ȳ�С��һ�ζ�д�����ݳ��� */
#endif

; ********************************************************************************************************************* */
; ��������
	RSEG  CH375LIB_IDATA
 mCmdParam:   DS   MAX_PATH_LEN			; ������� */

	XSEG  AT  CH375_CMD_PORT_ADDR
 CH375_CMD_PORT:   DS   1				; CH375����˿ڵ�I/O��ַ */

	XSEG  AT  CH375_DAT_PORT_ADDR
 CH375_DAT_PORT:   DS   1				; CH375���ݶ˿ڵ�I/O��ַ */

#ifdef DISK_BASE_BUF_LEN
	XSEG  AT  DISK_BASE_BUF_ADDR
  DISK_BASE_BUF:   DS   DISK_BASE_BUF_LEN	; �ⲿRAM�Ĵ������ݻ�����,����������Ϊһ�������ĳ��� */
#endif

#ifdef FILE_DATA_BUF_LEN
	XSEG  AT  FILE_DATA_BUF_ADDR
  FILE_DATA_BUF:   DS   FILE_DATA_BUF_LEN	; �ⲿRAM���ļ����ݻ�����,���������Ȳ�С��һ�ζ�д�����ݳ��� */
#endif

; ********************************************************************************************************************* */
; Ĭ�ϵı�CH375�������õ��ӳ�����
; ���³�����Ը�����Ҫ�޸�, �����ϸ���ݿ��Բο�C����ͷ�ļ�CH375HF6.H
	RSEG  CH375LIB_CODE

#ifdef FILE_DATA_BUF_LEN
	PUBLIC	CH375FileRead				; �ӵ�ǰ�ļ���ȡ���� */
; �ӵ�ǰ�ļ���ȡ����
CH375FileRead:		MOV		R0,#mCmdParam+8			;mCmdParam.ReadX.mDataBuffer
					MOV		@R0,#HIGH FILE_DATA_BUF	;ָ���ļ����ݻ�����
					INC		R0
					MOV		@R0,#LOW FILE_DATA_BUF
					LJMP	CH375FileReadX
#ifdef EN_DISK_WRITE
	PUBLIC	CH375FileWrite				; ��ǰ�ļ�д������ */
; ��ǰ�ļ�д������
CH375FileWrite:		MOV		R0,#mCmdParam+8			;mCmdParam.WriteX.mDataBuffer
					MOV		@R0,#HIGH FILE_DATA_BUF	;ָ���ļ����ݻ�����
					INC		R0
					MOV		@R0,#LOW FILE_DATA_BUF
					LJMP	CH375FileWriteX
#endif
#endif
;
#ifndef NO_DEFAULT_CH375_F_ENUM
; ��Ӧ�ó����ж���NO_DEFAULT_CH375_F_ENUM���Խ�ֹĬ�ϵ�ö���ļ�����,Ȼ�������б�д�ĳ�������� */
	PUBLIC	CH375FileEnumer				; ö���ļ� */
; ö���ļ�
CH375FileEnumer:	LCALL	CH375FileOpen
					CJNE	R7,#ERR_FOUND_NAME,CH375FileEnumer_0
					MOV		R7,#ERR_SUCCESS		; �����ɹ� */
CH375FileEnumer_0:	RET
#endif
;
#ifndef NO_DEFAULT_CH375_F_QUERY
; ��Ӧ�ó����ж���NO_DEFAULT_CH375_F_QUERY���Խ�ֹĬ�ϵĲ�ѯ��ǰ�ļ�����Ϣ����,Ȼ�������б�д�ĳ�������� */
	PUBLIC	CH375FileQuery				; ��ѯ��ǰ�ļ�����Ϣ */
; ��ѯ��ǰ�ļ�����Ϣ
CH375FileQuery:		MOV		R0,#mCmdParam
					MOV		R7,#10
CH375FileQuery_1:	MOV		@R0,#0FFH	; �������ȫ����Ч,����ѯ���޸� */
					INC		R0
					DJNZ	R7,CH375FileQuery_1
					LJMP	CH375FileModify
#endif
;
#ifndef NO_DEFAULT_CH375_INT
; ��Ӧ�ó����ж���NO_DEFAULT_CH375_INT���Խ�ֹĬ�ϵ��жϴ�������,Ȼ�������б�д�ĳ�������� */
	PUBLIC	xQueryInterrupt				; �ⲿ����ı�CH375�������õ��ӳ���,��ѯCH375�жϲ������ж�״̬ */
; CH375�жϷ������,��CH375��INT#�ĵ͵�ƽ�����½��ش�����Ƭ���ж�
;xQueryInterrupt:	MOV		A,CH375IntStatus		; ���ӳ�������"�жϷ�ʽ",��ѯ�ж�״̬,�ȴ�Ӳ���ж�
;					JZ		xQueryInterrupt			; �ӳ������ø��ӳ���֮ǰCH375IntStatus=0,Ӳ���жϺ�,���жϷ��������Ϊ��0��ʵ���ж�״̬�󷵻�
;					RET
InterruptHandle:	PUSH    PSW						; �жϷ������,���ʹ��"�жϷ�ʽ",�����ж�������ִ��һ����ת����
					PUSH    ACC
					PUSH    DPL
					PUSH    DPH
					CALL    xQueryInterrupt_1
					POP     DPH
					POP     DPL
					POP     ACC
					POP     PSW
					RETI
; ��ѯCH375�жϲ������ж�״̬
#ifdef CH375_INT_WIRE
xQueryInterrupt:	JB   	CH375_INT_WIRE,$		; ���ӳ�������"��ѯ��ʽ",��ѯCH375��INT#����,���CH375���ж���������ߵ�ƽ��ȴ�
#else
xQueryInterrupt:	MOV  	DPTR,#CH375_CMD_PORT	; ���ӳ�������"��ѯ��ʽ",��ѯCH375��INT#����,���CH375���ж���������ߵ�ƽ��ȴ�
					MOVX  	A,@DPTR					; ����CH375BоƬ�����Բ�ѯ����˿ڵ�λ7
					JB   	ACC.7,xQueryInterrupt	; ��ѯCH375B������˿ڵ�λ7Ϊ1˵���ж���������ߵ�ƽ��ȴ�
#endif
xQueryInterrupt_1:	MOV  	DPTR,#CH375_CMD_PORT
					MOV  	A,#CMD_GET_STATUS
					MOVX 	@DPTR,A					; ��ȡ��ǰ�ж�״̬ */
					INC     DPTR
					INC     DPTR					; ����������,����������ʱ2uS */
					INC     DPTR
					MOV  	DPTR,#CH375_DAT_PORT
					MOVX 	A,@DPTR					; ��ȡ�ж�״̬ */
					MOV  	CH375IntStatus,A
					CJNE 	A,#ERR_USB_DISCON,QUERY_INT_DISCON
					MOV  	CH375DiskStatus,#DISK_DISCONNECT	; ��⵽USB�豸�Ͽ��¼� */
					RET
QUERY_INT_DISCON:	CJNE 	A,#ERR_USB_CONNECT,QUERY_INT_CONNECT
					MOV  	CH375DiskStatus,#DISK_CONNECT	; ��⵽USB�豸�����¼� */
					RET
QUERY_INT_CONNECT:	RET
#endif

#ifndef NO_DEFAULT_DELAY_100US
; ��Ӧ�ó����ж���NO_DEFAULT_DELAY_100US���Խ�ֹĬ�ϵ���ʱ100uS�ӳ���,Ȼ�������б�д�ĳ�������� */
	PUBLIC	xDelay100uS					; �ⲿ����ı�CH375�������õ��ӳ���,��ʱ100uS */
; ��ʱ100uS
xDelay100uS:		MOV		R7,#150
xDelay100uS_1:		DJNZ	R7,xDelay100uS_1	; ��ʱ100uS,2x333nS@36MHz&12T */
					RET
#endif
;
#ifdef EN_DISK_WRITE
#ifndef NO_DEFAULT_DELAY_WRITE
; ��Ӧ�ó����ж���NO_DEFAULT_DELAY_WRITE���Խ�ֹĬ�ϵ�д��������ʱ����,Ȼ�������б�д�ĳ�������� */
	PUBLIC	xDelayAfterWrite			; �ⲿ����ı�CH375�������õ��ӳ���,д��������ʱ */
; д��������ʱ
xDelayAfterWrite:	MOV		R7,#250
xDelayAfterWrite_1:	DJNZ	R7,xDelayAfterWrite_1	; ��ʱ200uS���� */
					RET
#endif
#endif
;
#ifndef NO_DEFAULT_FILE_ENUMER
; ��Ӧ�ó����ж���NO_DEFAULT_FILE_ENUMER���Խ�ֹĬ�ϵ��ļ���ö�ٻص�����,Ȼ�������б�д�ĳ�������� */
	PUBLIC	xFileNameEnumer				; �ⲿ����ı�CH375�������õ��ӳ���,�ļ���ö�ٻص��ӳ��� */
; �ļ���ö�ٻص��ӳ���
; ���ָ��ö�����CH375vFileSizeΪ0xFFFFFFFF�����FileOpen����ôÿ������һ���ļ�FileOpen������ñ��ص�����
; �ص�����xFileNameEnumer���غ�FileOpen�ݼ�CH375vFileSize������ö��ֱ�����������ļ�����Ŀ¼�����������ǣ�
; �ڵ���FileOpen֮ǰ����һ��ȫ�ֱ���Ϊ0����FileOpen�ص�������󣬱�������CH375vFdtOffset�õ��ṹFAT_DIR_INFO��
; �����ṹ�е�DIR_Attr�Լ�DIR_Name�ж��Ƿ�Ϊ�����ļ�������Ŀ¼������¼�����Ϣ������ȫ�ֱ�������������
; ��FileOpen���غ��жϷ���ֵ�����ERR_MISS_FILE��ERR_FOUND_NAME����Ϊ�����ɹ���ȫ�ֱ���Ϊ����������Ч�ļ�����
; ����ڱ��ص�����xFileNameEnumer�н�CH375vFileSize��Ϊ1����ô����֪ͨFileOpen��ǰ���������������ǻص���������
xFileNameEnumer:	MOV		A,pDISK_BASE_BUF+1	; �ο�CH375HF6.H�еĳ���
#if 0
					ADD		A,CH375vFdtOffset+1
					MOV		DPL,A
					MOV		R7,A
					MOV		A,pDISK_BASE_BUF
					ADDC	A,CH375vFdtOffset		; ��ǰFDT����ʼ��ַ
					MOV		DPH,A					; DPTRָ���ļ���,pFileDir -> DIR_Name[0]
					MOV		R6,A
					MOVX	A,@DPTR
					MOV		R4,A					; �ļ������ַ�
					INC		DPTR
					MOVX	A,@DPTR
					MOV		R5,A					; �ļ������ַ�
;					......
					MOV		A,R7
					ADD		A,#11
					MOV		DPL,A
					MOV		A,R6
					ADDC	A,#0
					MOV		DPH,A					; DPTRָ���ļ�����,pFileDir -> DIR_Attr
					MOVX	A,@DPTR
;					JB		ACC.4,��Ŀ¼
;					JNB		ACC.4,���ļ�
#endif
					RET
#endif
;
#ifdef EXT_BLK_INTERFACE
#ifdef FILE_DATA_BUF_LEN
	PUBLIC	_xWriteToExtBuf				; �ⲿ����ı�CH375�������õ��ӳ���,��CH375��ȡ�ļ����ݵ��ⲿ������ */
; ���ӳ�����CH375���ӳ�������,���ڴ�CH375��ȡ�ļ����ݵ��ⲿ������,��CH375FileRead���� */
_xWriteToExtBuf:	RET								;����ļ���д�����ݵĸ��Ʒ�ʽ����"�ⲿ�ӳ���",�򲻻���ø��ӳ���
;
#ifdef EN_DISK_WRITE
	PUBLIC	_xReadFromExtBuf			; �ⲿ����ı�CH375�������õ��ӳ���,���ⲿ��������ȡ�ļ����ݵ�CH375 */
; ���ӳ�����CH375���ӳ�������,���ڴ��ⲿ��������ȡ�ļ����ݵ�CH375,��CH375FileWrite���� */
_xReadFromExtBuf:	RET								;����ļ���д�����ݵĸ��Ʒ�ʽ����"�ⲿ�ӳ���",�򲻻���ø��ӳ���
#endif
#endif
#endif
;
; ********************************************************************************************************************* */
; ����������õ��ӳ���
	PUBLIC	CH375LibInit
; ��ʼ��CH375������CH375оƬ, ������ɺ󷵻�״̬����R7��, �����ɹ�����0
CH375LibInit:		MOV  	A,SP
					SETB  	C
					SUBB 	A,#0F0H					; CH375�ӳ������������7���ӳ���,��ѯ��ʽ�����Ҫ14�ֽڵĶ�ջ�ռ�,�����ṩ����
					JC  	CH375LibInit_SP			; ��Ƭ���Ķ�ջ�ռ䲻��
					MOV  	R7,#0FCH				; ��ǰ�ӳ����İ汾��̫���򷵻ش���
					RET
CH375LibInit_SP:	MOV  	CH375LibConfig,#LIB_CFG_VALUE	; CH375���������ֵ
					LCALL	CH375GetVer				; ��ȡ��ǰ�ӳ����İ汾��
					MOV  	A,R7
					CLR  	C
					SUBB 	A,#CH375_LIB_VER
					JNC  	CH375LibInit_GOON
					MOV  	R7,#0FFH				; ��ǰ�ӳ����İ汾��̫���򷵻ش���
					RET
CH375LibInit_GOON:
#ifdef DISK_BASE_BUF_LEN
					MOV  	pDISK_BASE_BUF,#HIGH DISK_BASE_BUF	; ָ���ⲿRAM�Ĵ������ݻ�����
					MOV  	pDISK_BASE_BUF+1,#LOW DISK_BASE_BUF
#endif
					LCALL	CH375Init				; ��ʼ��CH375
					RET
;
; ********************************************************************************************************************* */
; ���±�CH375������õ����ӳ���,����C51�ĳ����C51S.LIB
; ���û��������Щ�ӳ���(����ע�͵�), ��ô���ӷ�����: LX51  CH375HFT.OBJ , CH375HF6.LIB, C51S.LIB
; �����������Щ�ӳ���, ��ô���ӷ�����: LX51  CH375HFT.OBJ , CH375HF6.LIB
; ����, ���Ӧ�ó���Ҳ�õ�C51S.LIB�е��ӳ���, ��ô��������Щ����ע�͵�, ��ֹ����ʱ����ͬ����ͻ
	PUBLIC	?C?ULCMP
?C?ULCMP:			MOV   A,R3
					SUBB  A,R7
					MOV   B,A
					MOV   A,R2
					SUBB  A,R6
					ORL   B,A
					MOV   A,R1
					SUBB  A,R5
					ORL   B,A
					MOV   A,R0
					SUBB  A,R4
					ORL   A,B
					RET
	PUBLIC	?C?ULSHR
?C?ULSHR:			MOV   A,R0
					JZ    ?C?ULSHR_RET
?C?ULSHR_LOOP:		MOV   A,R4
					CLR   C
					RRC   A
					MOV   R4,A
					MOV   A,R5
					RRC   A
					MOV   R5,A
					MOV   A,R6
					RRC   A
					MOV   R6,A
					MOV   A,R7
					RRC   A
					MOV   R7,A
					DJNZ  R0,?C?ULSHR_LOOP
?C?ULSHR_RET:		RET
	PUBLIC	?C?LSHL
?C?LSHL:			MOV   A,R0
					JZ    ?C?LSHL_RET
?C?LSHL_LOOP:		MOV   A,R7
					CLR   C
					RLC   A
					MOV   R7,A
					MOV   A,R6
					RLC   A
					MOV   R6,A
					MOV   A,R5
					RLC   A
					MOV   R5,A
					MOV   A,R4
					RLC   A
					MOV   R4,A
					DJNZ  R0,?C?LSHL_LOOP
?C?LSHL_RET:		RET
	PUBLIC	?C?LLDIDATA
?C?LLDIDATA:		MOV   A,@R0
					MOV   R4,A
					INC   R0
					MOV   A,@R0
					MOV   R5,A
					INC   R0
					MOV   A,@R0
					MOV   R6,A
					INC   R0
					MOV   A,@R0
					MOV   R7,A
					RET
	PUBLIC	?C?LLDIDATA0
?C?LLDIDATA0:		MOV   A,@R0
					MOV   R3,A
					INC   R0
					MOV   A,@R0
					MOV   R1,A
					INC   R0
					MOV   A,@R0
					MOV   R2,A
					INC   R0
					MOV   A,@R0
					XCH   A,R3
					MOV   R0,A
					RET
	PUBLIC	?C?LSTIDATA
?C?LSTIDATA:		MOV   A,R4
					MOV   @R0,A
					INC   R0
					MOV   A,R5
					MOV   @R0,A
					INC   R0
					MOV   A,R6
					MOV   @R0,A
					INC   R0
					MOV   A,R7
					MOV   @R0,A
					RET
	PUBLIC	?C?LSTXDATA
?C?LSTXDATA:		MOV   A,R4
					MOVX  @DPTR,A
					INC   DPTR
					MOV   A,R5
					MOVX  @DPTR,A
					INC   DPTR
					MOV   A,R6
					MOVX  @DPTR,A
					INC   DPTR
					MOV   A,R7
					MOVX  @DPTR,A
					RET
	PUBLIC	?C?LSTKIDATA
?C?LSTKIDATA:		POP   DPH
					POP   DPL
					CLR   A
					MOVC  A,@A+DPTR
					MOV   @R0,A
					INC   R0
					MOV   A,#01H
					MOVC  A,@A+DPTR
					MOV   @R0,A
					INC   R0
					MOV   A,#02H
					MOVC  A,@A+DPTR
					MOV   @R0,A
					INC   R0
					MOV   A,#03H
					MOVC  A,@A+DPTR
					MOV   @R0,A
					MOV   A,#04H
					JMP   @A+DPTR
; �����Ǳ�CH375������õ����ӳ���,����C51�ĳ����C51S.LIB,���ȥ����Щ�ӳ���,��ô����ʱҪ����C51S.LIB
;
#endif
;