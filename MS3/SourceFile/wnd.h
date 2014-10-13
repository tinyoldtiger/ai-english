//wnd.h -  http://www.chipart.cn 

#ifndef WND_H
#define WND_H

//���ڽṹ
typedef struct tag_WND
{
	struct tag_WND * pParentWnd; //�ϼ�����
	uint8_t *Buf;								 //����ר��ȫ�ֿռ�

	void  (*Load)(struct tag_WND *pWnd);					//װ���¼�������
	void  (*UnLoad)(struct tag_WND *pWnd);				//�����¼�������
	void  (*KeyEvent)  (struct tag_WND *pWnd,uint8_t key); //����������
	void  (*TimerEvent)(struct tag_WND *pWnd,uint8_t flag);//ʱ�Ӵ�����
}WND,*PWND; 


void CreateWnd(PWND pWnd,             \
				void (*kf)(PWND ,uint8_t) ,   \
				PWND parWnd,                  \
				uint8_t buf_size);

void SetCallBackWnd(PWND pWnd,\
										void (*Load)(PWND),\
										void (*UnLoad)(PWND),\
										void (*TimerEvent)(PWND,uint8_t));
										

void SetCurrentWnd(PWND pWnd);
void ExitCurrentWnd(void);
void CurrentKeyEvent(uint8_t key);
void CurrentTimerEvent(void);

#endif
