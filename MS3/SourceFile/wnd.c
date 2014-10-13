/********************************
	uI:微型用户接口管理模块
	文件名:wnd.c
	
	芯艺设计室 2004-2007  版权所有 
	转载请保留本注释在内的全部内容
	WEB: http://www.chipart.cn
	Email: chipart@qq.com
*******************************/

//在程序中调用CreateWnd时总共为窗口分配的缓冲区大小
#define MAX_WND_BUF_SIZE 20

static PWND g_pCurrentWnd=0; //当前窗口
static uint8_t g_WndBuffer[MAX_WND_BUF_SIZE];//分配给窗口用的缓冲区
static uint8_t *g_pWndBuf=g_WndBuffer;//缓冲分配当前位置

//参数:窗口对象指针,按键处理函数,父窗口指针,窗口缓冲区大小
void CreateWnd(PWND pWnd,                     \
				void (*kf)(PWND ,uint8_t) ,   \
				PWND parWnd,                  \
				uint8_t buf_size)
{
	uint8_t i;

	pWnd->KeyEvent=kf;	//设置显示函数
	pWnd->pParentWnd=(struct tag_WND *)parWnd;	//设置父窗口
	pWnd->Load=0;
	pWnd->UnLoad=0;
	pWnd->TimerEvent=0;

	//分配窗口缓冲区
	pWnd->Buf=g_pWndBuf;
	g_pWndBuf+=buf_size;
	//窗口缓冲区清零
	for(i=0;i<buf_size;i++)
		pWnd->Buf[i]=0;
}

//设置窗口回调函数 ,分别设置装入时调用的Load,销毁时调用的UnLoad和窗口定时触发事件函数
void SetCallBackWnd(PWND pWnd,\
										void (*Load)(PWND),\
										void (*UnLoad)(PWND),\
										void (*TimerEvent)(PWND,uint8_t))
{
	pWnd->Load=Load;
	pWnd->UnLoad=UnLoad;
	pWnd->TimerEvent=TimerEvent;
}

//设置当前显示窗口
void SetCurrentWnd(PWND pWnd)
{
	//如果当前窗口有销毁函数就调用
	if(g_pCurrentWnd)
	{
		if(g_pCurrentWnd->UnLoad != 0)
			g_pCurrentWnd->UnLoad(g_pCurrentWnd);	
	}	
	g_pCurrentWnd = pWnd;
	if(pWnd->Load != 0)
		pWnd->Load(g_pCurrentWnd);
}

//退出当前显示窗口
void ExitCurrentWnd(void)
{
	//如果当前窗口的父窗口有效才执行
	if(g_pCurrentWnd->pParentWnd == 0)
		return ;
	
	//将父窗口设置为当前窗口
	SetCurrentWnd(g_pCurrentWnd->pParentWnd);
}

//按键事件处理函数
void CurrentKeyEvent(uint8_t key)
{
	if(g_pCurrentWnd->KeyEvent != 0)
		g_pCurrentWnd->KeyEvent(g_pCurrentWnd,key);
}

//定时事件处理函数
void CurrentTimerEvent(void)
{
	static uint8_t flag=0;
	
	flag=!flag;
	
	if(g_pCurrentWnd->TimerEvent != 0)
		g_pCurrentWnd->TimerEvent(g_pCurrentWnd,flag);
}
