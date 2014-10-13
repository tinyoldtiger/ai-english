//wnd.h -  http://www.chipart.cn 

#ifndef WND_H
#define WND_H

//窗口结构
typedef struct tag_WND
{
	struct tag_WND * pParentWnd; //上级窗口
	uint8_t *Buf;								 //窗口专用全局空间

	void  (*Load)(struct tag_WND *pWnd);					//装入事件处理函数
	void  (*UnLoad)(struct tag_WND *pWnd);				//销毁事件处理函数
	void  (*KeyEvent)  (struct tag_WND *pWnd,uint8_t key); //按键处理函数
	void  (*TimerEvent)(struct tag_WND *pWnd,uint8_t flag);//时钟处理函数
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
