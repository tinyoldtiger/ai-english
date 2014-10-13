/********************************
	uI:΢���û��ӿڹ���ģ��
	�ļ���:wnd.c
	
	о������� 2004-2007  ��Ȩ���� 
	ת���뱣����ע�����ڵ�ȫ������
	WEB: http://www.chipart.cn
	Email: chipart@qq.com
*******************************/

//�ڳ����е���CreateWndʱ�ܹ�Ϊ���ڷ���Ļ�������С
#define MAX_WND_BUF_SIZE 20

static PWND g_pCurrentWnd=0; //��ǰ����
static uint8_t g_WndBuffer[MAX_WND_BUF_SIZE];//����������õĻ�����
static uint8_t *g_pWndBuf=g_WndBuffer;//������䵱ǰλ��

//����:���ڶ���ָ��,����������,������ָ��,���ڻ�������С
void CreateWnd(PWND pWnd,                     \
				void (*kf)(PWND ,uint8_t) ,   \
				PWND parWnd,                  \
				uint8_t buf_size)
{
	uint8_t i;

	pWnd->KeyEvent=kf;	//������ʾ����
	pWnd->pParentWnd=(struct tag_WND *)parWnd;	//���ø�����
	pWnd->Load=0;
	pWnd->UnLoad=0;
	pWnd->TimerEvent=0;

	//���䴰�ڻ�����
	pWnd->Buf=g_pWndBuf;
	g_pWndBuf+=buf_size;
	//���ڻ���������
	for(i=0;i<buf_size;i++)
		pWnd->Buf[i]=0;
}

//���ô��ڻص����� ,�ֱ�����װ��ʱ���õ�Load,����ʱ���õ�UnLoad�ʹ��ڶ�ʱ�����¼�����
void SetCallBackWnd(PWND pWnd,\
										void (*Load)(PWND),\
										void (*UnLoad)(PWND),\
										void (*TimerEvent)(PWND,uint8_t))
{
	pWnd->Load=Load;
	pWnd->UnLoad=UnLoad;
	pWnd->TimerEvent=TimerEvent;
}

//���õ�ǰ��ʾ����
void SetCurrentWnd(PWND pWnd)
{
	//�����ǰ���������ٺ����͵���
	if(g_pCurrentWnd)
	{
		if(g_pCurrentWnd->UnLoad != 0)
			g_pCurrentWnd->UnLoad(g_pCurrentWnd);	
	}	
	g_pCurrentWnd = pWnd;
	if(pWnd->Load != 0)
		pWnd->Load(g_pCurrentWnd);
}

//�˳���ǰ��ʾ����
void ExitCurrentWnd(void)
{
	//�����ǰ���ڵĸ�������Ч��ִ��
	if(g_pCurrentWnd->pParentWnd == 0)
		return ;
	
	//������������Ϊ��ǰ����
	SetCurrentWnd(g_pCurrentWnd->pParentWnd);
}

//�����¼�������
void CurrentKeyEvent(uint8_t key)
{
	if(g_pCurrentWnd->KeyEvent != 0)
		g_pCurrentWnd->KeyEvent(g_pCurrentWnd,key);
}

//��ʱ�¼�������
void CurrentTimerEvent(void)
{
	static uint8_t flag=0;
	
	flag=!flag;
	
	if(g_pCurrentWnd->TimerEvent != 0)
		g_pCurrentWnd->TimerEvent(g_pCurrentWnd,flag);
}
