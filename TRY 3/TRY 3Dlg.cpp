
// TRY 3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "TRY 3.h"
#include "TRY 3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}


Node *List()
{
	Node* L=new Node;
	L=NULL;
	return L;
}

Node **new_array2D(int wx1,int wy1,int wt1,int wb1,int a[500][2],int sx,int sy,int ex,int ey)
{
	int x=(wy1-wx1)/20;
	int y=(wb1-wt1)/20;
	Node ** map;
	map=new Node*[x];
	for(int i=0;i<x;++i)
		map[i]=new Node[y];

	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
		{
			map[i][j].data = 0;
			for(int b=0;b<x;b++)
					{
						if(((a[b][0]-20)==(i*20))&&((a[b][1]-20)==(j*20)))
						{map[i][j].data = 1;break;}
						
					}
					if((sx-20==i*20)&&(sy-20==j*20))
						map[i][j].data =2;
					if(ex-20==i*20&&ey-20==j*20)
						map[i][j].data =3;
					map[i][j].F=0;
					map[i][j].G=0;
					map[i][j].H=0;
					map[i][j].x=i*20+wx1;
					map[i][j].y=j*20+wt1;
					map[i][j].Open_flag= 0;
					map[i][j].close_flag =0;
					map[i][j].next =NULL;
					map[i][j].final_next = NULL;
			}
		
		return map;
}
					
void free_array2D(Node **arr)
{
	delete []arr;
}
/*Node* sort(LinkList List)
{
	Node *p0;
	Node *p1;
	Node *p2;
	Node *head;
	bool flag=false;
	p0=p1=head=List;
	while(p0->next->next!=NULL)
	{
		if(p0->F >p0->next->F )
		{
			p1=p0;
			p2=p0->next->next;
			p0=p0->next;
			p0->next=p1;
			p0->next->next=p2;
		}

}*/
Node* insert(Node* list,Node *node)
{
	if(node->close_flag ==1)return list;
	Node *p;Node *q=NULL;Node *head;
	head=q=p=list;
	if(list==NULL){list=node;return list;}
	while(node->F>p->F&&p->next!=NULL)
	{
		if(node==p)return list;
		q=p;p=p->next;
	}
	if(node->F <=p->F )
	{
		if(p==head)head=node;
		else q->next=node;
		node->next=p;
	}
	else {
		p->next=node;
		node->next=NULL;
	}
	list=head;
	return list;
}

int count_G(Node *ParentNode)
{

	return ParentNode->G+20;
}
int count_H(Node *curNode,Node *endNode)
{
	int H;
	H=fabs((endNode->x-curNode->x)*1.0)+fabs((endNode->y-curNode->y)*1.0);
	return H;
}

int count_F(Node *curNode)
{
	int F;
	F=curNode->G+curNode->H;
	return F;
}
/*bool InTheOpenList(Node *node)
{
	return node->Open_flag;
}
//bool InTheCloseList(Node *node)
{
	return node->close_flag;
}
*/

int check_around( Node* curNode,Node endNode,Node* &openlist,Node **map,int wx,int wy,int wt,int wb)
{
	if(openlist!=NULL)
	openlist=openlist->next;
	Node *node1,*node2,*node3,*node4;
	//node1=new Node;
	node1=NULL;
//	node2=new Node;
	node2=NULL;
//	node3=new Node;
	node3=NULL;
//	node4=new Node;
	node4=NULL;
	if((curNode->x-wx*2)!=0){

	node1=&map[(curNode->x)/20-2][(curNode->y)/20-1];
	if(node1->close_flag !=1&&node1->Open_flag !=1)
	{
	if(node1->data ==3)return 1;
	node1->final_next = curNode;
	node1->G=count_G(curNode);
	node1->H =count_H(node1,&endNode);
	node1->F=count_F(node1);
	if(node1->data ==0)
		{ node1->Open_flag =1;
			openlist=insert(openlist,node1);
	}
	}
	}
	
	if(curNode->y-wt*2!=0){
	node2=&map[(curNode->x)/20-1][(curNode->y)/20-2];
	if(node2->close_flag !=1&&node2->Open_flag !=1)
	{
	if(node2->data ==3)return 2;
	node2->final_next =curNode;
	node2->G=count_G(curNode);
	node2->H =count_H(node2,&endNode);
	node2->F=count_F(node2);
	if(node2->data ==0){node2->Open_flag =1;
	openlist=insert(openlist,node2);}
	}
	}

	if(curNode->x-20<wy){
	node3=&map[(curNode->x)/20][(curNode->y)/20-1];
	if(node3->close_flag !=1&&node3->Open_flag !=1)
	{
	if(node3->data ==3)return 3;
	node3->final_next =curNode;
	node3->G=count_G(curNode);
	node3->H =count_H(node3,&endNode);
	node3->F=count_F(node3);
	if(node3->data ==0){
		node3->Open_flag =1;
		openlist=insert(openlist,node3);
	}
	}
	}

	if(curNode->y-20<wb){
	node4=&map[(curNode->x)/20-1][(curNode->y)/20];
	if(node4->close_flag !=1&&node4->Open_flag !=1)
	{
	if(node4->data ==3)return 4;
	node4->final_next =curNode;
	node4->G=count_G(curNode);
	node4->H =count_H(node4,&endNode);
	node4->F=count_F(node4);
	if(node4->data ==0){
		node4->Open_flag =1;
		openlist=insert(openlist,node4);}
	}
	}


	/*delete []node1;
	delete [] node2;
	delete [] node3;
	delete [] node4;*/
	return 0;
	}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTRY3Dlg dialog




CTRY3Dlg::CTRY3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTRY3Dlg::IDD, pParent)
{
	easy=FALSE;
	normal=FALSE;
	move=FALSE;
	start=TRUE;
	m_oldFont=NULL;
	left=FALSE;
	right=FALSE;
	up=FALSE;
	down=FALSE;
	turnup=FALSE;
	turnleft=FALSE;
	turnup=FALSE;
	turndown=FALSE;
	turn=FALSE;
	FIND =FALSE;
	up1=FALSE;
	down1=FALSE;
	left1=FALSE;
	right1=FALSE;
	a1=0;a2=0;a3=0;a4=0;a5=0;
	a[0][0]=100	;a[0][1]=200;
	str=_T("**>");
		foodX=300;foodY=300;
	for(int i=1;i<str.GetLength();i++)
	{	
			a[i][0]=a[i-1][0]+20;
			a[i][1]=200;
	}
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTRY3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTRY3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GAME_1, &CTRY3Dlg::OnGameStart)
	ON_COMMAND(ID_GAME_2, &CTRY3Dlg::OnGamePause)
	ON_COMMAND(ID_GAME_3, &CTRY3Dlg::OnGameFind)
	ON_COMMAND(ID_GAME_4, &CTRY3Dlg::OnGameContinue)
	ON_UPDATE_COMMAND_UI(ID_GAME_1, &CTRY3Dlg::OnUpdateGame1)
	ON_COMMAND(ID_DIFFICULTY_SIMPLE, &CTRY3Dlg::OnDifficultySimple)
	ON_COMMAND(ID_DIFFICULTY_NORMAL, &CTRY3Dlg::OnDifficultyNormal)
	ON_COMMAND(ID_DIFFICULTY_HARD, &CTRY3Dlg::OnDifficultyHard)
END_MESSAGE_MAP()


// CTRY3Dlg message handlers

BOOL CTRY3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	this->GetClientRect(wallrect);
	wx=wallrect.left+20;
	wt=wallrect.top+20;
	wy=wallrect.right-20;
	wb=wallrect.bottom-20;
	wy=(wy/20)*20;
	wb=(wb/20)*20;
	wx=(wx/20)*20;
	wt=(wt/20)*20;

	midx=(wy-wx)/2;
	midy=(wb-wt)/2;
	//SetTimer(1,250,NULL);
	m_newFont.CreateFont(40,20,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,_T("船慕"));
	m_Font.CreateFont(40,13,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,_T("船慕"));
	srand((unsigned)time(NULL));
	CPaintDC dc(this);	

	/*foodX=(rand()%(wy/10))*10;foodY=(rand()%(wb/10))*10;
	if(foodX<=wx||foodX>=wy||foodY<=wt||foodY>=wb)
	{	foodX=(rand()%(wy/10))*10;foodY=(rand()%(wb/10))*10;}*/

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTRY3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTRY3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
	CPen newpen;
	CPen  *oldpen;
	CDC dcBmp;
	dcBmp.CreateCompatibleDC (&dc);
	CBitmap backaround;
	backaround.LoadBitmap (IDB_BITMAP2);
	BITMAP bitmap;
	backaround.GetBitmap (&bitmap);
	CBitmap *bmpOld=dcBmp.SelectObject (&backaround);
	dc.StretchBlt (0,0,wallrect.Width (),wallrect.Height (),&dcBmp,0,0,bitmap.bmWidth,bitmap.bmHeight ,SRCCOPY);
	newpen.CreatePen(PS_SOLID,5,RGB(0,255,0));
	oldpen=dc.SelectObject(&newpen);
	dc.MoveTo(wx,wt);
	dc.LineTo(wx,wb);
	dc.LineTo(wy,wb);
	dc.LineTo(wy,wt);
	dc.LineTo(wx,wt);
	dc.SelectObject(oldpen);
	newpen.DeleteObject();
	m_oldFont=(CFont*)dc.SelectObject(&m_newFont);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,0,0));
	LENGTH=str.GetLength ();
	if(left==up&&left==down&&left==right&&left==FALSE)
	{
		dc.TextOut(a[LENGTH-1][0],a[LENGTH-1][1],_T(">"));
		for(int i=0;i<LENGTH-1;i++)
			dc.TextOut(a[i][0],a[i][1],_T("*"));
	}
	else if(up==TRUE)
	{
		for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
			dc.SelectObject(m_Font);
			dc.TextOut(a[LENGTH-1][0],a[LENGTH-1][1]-=20,_T("…"));
			dc.SelectObject(m_newFont);
		for(int i=0;i<LENGTH-1;i++)
			dc.TextOut(a[i][0],a[i][1],_T("*"));
		a1=0;
	}
	else if(right==TRUE)
	{
		for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
	
			dc.TextOut(a[LENGTH-1][0]+=20,a[LENGTH-1][1],_T(">"));
		
		for(int i=0;i<LENGTH-1;i++)
			dc.TextOut(a[i][0],a[i][1],_T("*"));
		a3=0;
	}
	else  if(down==TRUE)
	{
		for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
		
			dc.TextOut(a[LENGTH-1][0],a[LENGTH-1][1]+=20,_T("V"));
	
		
		for(int i=0;i<LENGTH-1;i++)
			dc.TextOut(a[i][0],a[i][1],_T("*"));
		a2=0;
	}
	else   if(left==TRUE)
	{
		for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
		
			dc.TextOut(a[LENGTH-1][0]-=20,a[LENGTH-1][1],_T("<"));
		for(int i=0;i<LENGTH-1;i++)
			dc.TextOut(a[i][0],a[i][1],_T("*"));
		a4=0;
	}
	dc.TextOut(foodX,foodY,_T("，"));
	dc.SelectObject(m_oldFont);


		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTRY3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*void  CTRY3Dlg::Turnup()
{

	for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
			DC.SelectObject(m_Font);
			DC.TextOut(a[LENGTH-1][0],a[LENGTH-1][1]-=20,_T("…"));
			DC.SelectObject(m_newFont);
		for(int i=0;i<LENGTH-1;i++)
			DC.TextOut(a[i][0],a[i][1],_T("*"));
		a1=0;
}
void  CTRY3Dlg::Turndown()
{

	for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
		
			DC.TextOut(a[LENGTH-1][0],a[LENGTH-1][1]+=20,_T("V"));
	
		
		for(int i=0;i<LENGTH-1;i++)
			DC.TextOut(a[i][0],a[i][1],_T("*"));
		a2=0;
}
void  CTRY3Dlg::Turnleft()
{
	for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
		
			DC.TextOut(a[LENGTH-1][0]-=20,a[LENGTH-1][1],_T("<"));
		
		
		for(int i=0;i<LENGTH-1;i++)
			DC.TextOut(a[i][0],a[i][1],_T("*"));
		a4=0;
}
void CTRY3Dlg::Turnright()
{

		for(int i=0;i<LENGTH-1;i++)
		{
			a[i][0]=a[i+1][0];
			a[i][1]=a[i+1][1];
		}
	
			DC.TextOut(a[LENGTH-1][0]+=20,a[LENGTH-1][1],_T(">"));
		
		for(int i=0;i<LENGTH-1;i++)
			DC.TextOut(a[i][0],a[i][1],_T("*"));
		a3=0;
}*/
void CTRY3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
{
case 1:
	for(int i=0;i<LENGTH;i++)
			a[i][0]+=20;
	if(	(a[LENGTH-1][0])>=wy||hit()==TRUE)
	{	
		left=FALSE;
		right=FALSE;
		up=FALSE;
		down=FALSE;
		a[0][0]=100	;a[0][1]=200;
	str=_T("**>");
	for(int i=1;i<str.GetLength();i++)
	{	
			a[i][0]=a[i-1][0]+20;
			a[i][1]=200;
	}
		KillTimer(1);
		if(IDOK==MessageBox(_T("You Are Die!")));
			SetTimer(1,250,NULL);
	}
	if(eat()==TRUE)foodprovide();
	break;
case 2:
	up=TRUE;
	
	if(	a[LENGTH-1][1]<=wt||hit()==TRUE)
	{	
		left=FALSE;
		right=FALSE;
		up=FALSE;
		down=FALSE;
		a[0][0]=100	;a[0][1]=200;
	str=_T("**>");
	for(int i=1;i<str.GetLength();i++)
	{	
			a[i][0]=a[i-1][0]+20;
			a[i][1]=200;
	}
		KillTimer(2);
		if(IDOK==MessageBox(_T("You Are Die!")));
		{	SetTimer(1,250,NULL);up=FALSE;}
		
	}
	
	if(eat()==TRUE)foodprovide();

	break;
case 3:
	right=TRUE;

		if(a[LENGTH-1][0]>=wy||hit()==TRUE)
	{	
		left=FALSE;
		right=FALSE;
		up=FALSE;
		down=FALSE;
		a[0][0]=100	;a[0][1]=200;
	str=_T("**>");
	for(int i=1;i<str.GetLength();i++)
	{	
			a[i][0]=a[i-1][0]+20;
			a[i][1]=200;
	}
		KillTimer(3);
		if(IDOK==MessageBox(_T("You Are Die!")));
		{	SetTimer(1,250,NULL);up=FALSE;}
		
	}
	if(eat()==TRUE)foodprovide();
	break;
case 4:
	down=TRUE;
	if(a[LENGTH-1][1]>=wb-20||hit()==TRUE)
	{	
		left=FALSE;
		right=FALSE;
		up=FALSE;
		down=FALSE;
		a[0][0]=100	;a[0][1]=200;
	str=_T("**>");
	for(int i=1;i<str.GetLength();i++)
	{	
			a[i][0]=a[i-1][0]+20;
			a[i][1]=200;
	}
		KillTimer(4);
		if(IDOK==MessageBox(_T("You Are Die!")));
		{	SetTimer(1,250,NULL);up=FALSE;}
		
	}
	if(eat()==TRUE)foodprovide();
	break;
case 5:
	left=TRUE;

	if(a[LENGTH-1][0]<=wx||hit()==TRUE)
	{	
		left=FALSE;
		right=FALSE;
		up=FALSE;
		down=FALSE;
		a[0][0]=100	;a[0][1]=200;
	str=_T("**>");
	for(int i=1;i<str.GetLength();i++)
	{	
			a[i][0]=a[i-1][0]+20;
			a[i][1]=200;
	}
		KillTimer(5);
		if(IDOK==MessageBox(_T("You Are Die!")));
		{	SetTimer(1,250,NULL);up=FALSE;}
		
	}
	if(eat()==TRUE)foodprovide();
	break;

	case 6:
		if(move==FALSE)
		Move(startx,starty,b[J][0],b[J][1]);
		else
		if(J>0){	
		Move(b[J][0],b[J][1],b[J-1][0],b[J-1][1]);
		J--;
		}
		else if(J==0){
		Move(b[0][0],b[0][1],foodX,foodY);
		}
		move=TRUE;
		if(eat()==TRUE)foodprovide();
		break;
		}
	Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}
bool CTRY3Dlg::eat()
{
	if(a[LENGTH-1][0]==foodX&&a[LENGTH-1][1]==foodY)
		{
	str=_T("*")+str;
	LENGTH=str.GetLength();
	for(int i=LENGTH-1;i>0;i--)
	{
		a[i][0]=a[i-1][0];
		a[i][1]=a[i-1][1];
	}
	a[0][0]=a[1][0]-20;
	a[0][1]=a[1][1];
	return TRUE;}
	else return FALSE;
}
void CTRY3Dlg::foodprovide()
{
	int foodx,foody;
	foodx=foodX;foody=foodY;
	foodX=(rand()%(wy/20))*20;foodY=(rand()%(wb/20))*20;
	for(int i=0;i<LENGTH;i++)
		if(foodX==a[i][0]&&foodY==a[i][0])a5=1;
	while(foodX<=wx*2||foodX>=wy-wx||foodY<=wt*2||foodY>=wb-wt||a5==1||foodx==foodX&&foody==foodY)
	{a5=0;
		foodX=(rand()%(wy/20))*20;foodY=(rand()%(wb/20))*20;
	for(int i=0;i<LENGTH;i++)
		if(foodX==a[i][0]&&foodY==a[i][1])a5=1;
	}
	/*if(sss==0){
		foodX=400,foodY=400;sss++;}
	else	if(sss==1){foodX=300;foodY=360;sss++;}
	 else if(sss==2){
		foodX=400;foodY=300;sss++;}*/

	if(FIND==TRUE){KillTimer(6);find();}
}
BOOL CTRY3Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg	->message==WM_KEYDOWN)
	{
		pMsg->hwnd=m_hWnd;
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTRY3Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==0x26)
	{
		if(up1==FALSE){
			up1=TRUE;
		a1=1;
		if(a3!=0||a4!=0)return;
		if(left==up&&left==down&&left==right){
		KillTimer(1);
		turnup=TRUE;
		turn=TRUE;
		if(easy==TRUE)SetTimer(2,1000,NULL);
		else if(normal==TRUE)SetTimer(2,500,NULL);
		else 
		SetTimer(2,250,NULL);
		}
		else if(turndown==TRUE)return;
		else if(turnleft==TRUE){
			KillTimer(5);
			turnup=TRUE;
			left=FALSE;
			left1=FALSE;
			turnleft=FALSE;
			if(easy==TRUE)SetTimer(2,1000,NULL);
		else if(normal==TRUE)SetTimer(2,500,NULL);
		else 
			SetTimer(2,250,NULL);
		}
		else if(turnright==TRUE){
			KillTimer(3);
			turnup=TRUE;
			right=FALSE;
			right1=FALSE;
			turnright=FALSE;
			if(easy==TRUE)SetTimer(2,1000,NULL);
		else if(normal==TRUE)SetTimer(2,500,NULL);
		else 
			SetTimer(2,250,NULL);
		}
	}
	}
	if(nChar==VK_DOWN)
	{
		if(down1==FALSE){down1=TRUE;
		a2=1;
		if(a3!=0||a4!=0)return;
		if(left==up&&left==down&&left==right){
		KillTimer(1);
		turndown=TRUE;
		down=TRUE;
		if(easy==TRUE)SetTimer(4,1000,NULL);
		else if(normal==TRUE)SetTimer(4,500,NULL);
		else 
		SetTimer(4,250,NULL);
		}
		if(turnup==TRUE)return;
		else if(turnright==TRUE)
		{
			KillTimer(3);
			turndown=TRUE;
			if(easy==TRUE)SetTimer(4,1000,NULL);
		else if(normal==TRUE)SetTimer(4,500,NULL);
		else 
			SetTimer(4,250,NULL);
			right=FALSE;
			turnright=FALSE;
			right1=FALSE;
		}
		else if(turnleft==TRUE)
		{
			KillTimer(5);
			turndown=TRUE;
			if(easy==TRUE)SetTimer(4,1000,NULL);
		else if(normal==TRUE)SetTimer(4,500,NULL);
		else 
			SetTimer(4,250,NULL);
			left=FALSE;
			turnleft=FALSE;
			left1=FALSE;
		}
		else {
			KillTimer(1);
			turndown=TRUE;
			if(easy==TRUE)SetTimer(4,1000,NULL);
		else if(normal==TRUE)SetTimer(4,500,NULL);
		else 
			SetTimer(4,250,NULL);
			left=FALSE;
		}
		}
	}

	if(nChar==VK_RIGHT)
	{
		if(right1==FALSE){right1=TRUE;
		a3=1;
		if(a1!=0||a2!=0)return;
		if(turnleft==TRUE)return;
		
		if(turnup==TRUE)
		{
			KillTimer(2);
			turnright=TRUE;
			if(easy==TRUE)SetTimer(3,1000,NULL);
		else if(normal==TRUE)SetTimer(3,500,NULL);
		else 
			SetTimer(3,250,NULL);
			up=FALSE;
			turnup=FALSE;
			up1=FALSE;
		}
		 if(turndown==TRUE)
		{
			KillTimer(4);
			turnright=TRUE;
			if(easy==TRUE)SetTimer(3,1000,NULL);
		else if(normal==TRUE)SetTimer(3,500,NULL);
		else 
			SetTimer(3,250,NULL);
			turndown=FALSE;
			down=FALSE;
			down1=FALSE;
		}
	}
	}
	if(nChar==VK_LEFT)
	{
		if(left1==FALSE){left1=TRUE;
		if(a1!=0||a2!=0)return;
		a4=1;
		if(turnright==TRUE)return;
		if(turnup==TRUE)
		{
			KillTimer(2);
			turnleft=TRUE;
			if(easy==TRUE)SetTimer(5,1000,NULL);
		else if(normal==TRUE)SetTimer(5,500,NULL);
		else 
			SetTimer(5,250,NULL);
			turnup=FALSE;
			up=FALSE;
			up1=FALSE;
		}
		 if(turndown==TRUE)
		{
			KillTimer(4);
			turnleft=TRUE;
			if(easy==TRUE)SetTimer(5,1000,NULL);
		else if(normal==TRUE)SetTimer(5,500,NULL);
		else 
			SetTimer(5,250,NULL);
			turndown=FALSE;
			down=FALSE;
			down1=FALSE;
		}
	}
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
bool CTRY3Dlg::hit()
{
	for(int i=0;i<LENGTH-1;i++)
	{
		if(a[LENGTH-1][0]==a[i][0]&&a[LENGTH-1][1]==a[i][1])
			return TRUE;
	}
	return FALSE;
}
void CTRY3Dlg::find()
{

	move=FALSE;
	up=FALSE;
	down=FALSE;
	left=FALSE;
	right=FALSE;
	LENGTH=str.GetLength ();
	int endx=foodX;
	int endy=foodY;
	 startx=a[LENGTH-1][0];
	 starty=a[LENGTH-1][1];

	Node *OpenList=NULL;
	Node * CloseList=NULL;
	Node ** map=new_array2D(wx,wy,wt,wb,a,startx,starty,endx,endy);
	Node startPoint=map[startx/20-1][starty/20-1];
	Node endPoint=map[endx/20-1][endy/20-1];
	CloseList=&startPoint;
	int check;
	Node *LastPoint;
	Node *curNode;
	check=check_around(&startPoint,endPoint,OpenList,map,wx,wy,wt,wb);
	while(check==0)
	{	
		curNode=OpenList;
		check=check_around(curNode,endPoint,OpenList,map,wx,wy,wt,wb);
		if(check!=0)break;
		curNode->close_flag =1;
		curNode->Open_flag =0;
		//OpenList=OpenList->next;
	//		MessageBox(_T("123"));
	/*	Node *p1,*p2,*head;
	head=p1=OpenList;
	while(p1->next !=NULL&&p1!=curNode)
	{
		p2=p1;p1=p1->next;
	}
	if(p1==curNode)
	{
		if(head==p1)
		{
			head=p1->next;
		}
		else {
			p2->next=p1->next;
		}
	}
	OpenList=head;*/
	}

	/*if(check==1)
		LastPoint=map[(curNode->x -wx)/20-2][(curNode->y-wt)/20-1];
	else if(check==2)LastPoint=map[(curNode->x-wx)/20-1][(curNode->y-wt)/20-2];
	else if(check==3)LastPoint=map[(curNode->x-wx)/20][(curNode->y-wt)/20-1];
	else if(check==4)LastPoint=map[(curNode->x-wx)/20-1][(curNode->y-wt)/20];*/
	LastPoint=curNode;
	Node *node;
	node=LastPoint;
	Node *p3,*p4;
	p3=p4=node;
	int i=0;
	while(p3->final_next !=NULL)
	{
		b[i][0]=p3->x;
		b[i++][1]=p3->y;
		p3=p3->final_next ;
	}
	J=i-1;
	free_array2D(map);
	//delete []OpenList;
//	delete []CloseList;
	SetTimer(6,250,NULL);
	//Move(startx,starty,b[J][0],b[J][1]);
	
}
void CTRY3Dlg::Move(int x,int y,int a,int b)
{
	if(y<b)
		{
			down=TRUE;
			left=FALSE;
			up=FALSE;
			right=FALSE;
			//keybd_event(40,0,0,0);
		
	} 
	if(y>b)
	{
		up=TRUE;
		left=FALSE;
		down=FALSE;
		right=FALSE;
	//	keybd_event(38,0,0,0);
		
	}
	if(x<a)
	{
	right=TRUE;
	up=FALSE;
	down=FALSE;
	left=FALSE;
	//	keybd_event(39,0,0,0);
	
	}
	if(x>a)
	{
		left=TRUE;
		up=FALSE;
		down=FALSE;
		right=FALSE;
	//	keybd_event(37,0,0,0);
			
	}
}


void CTRY3Dlg::OnGameStart()
{
	start=FALSE;
		SetTimer(1,250,NULL);
	// TODO: Add your command handler code here
}


void CTRY3Dlg::OnGamePause()
{
	if(turnup==TRUE)KillTimer(2);
	else if(turndown==TRUE)KillTimer(4);
	else if(turnright==TRUE)KillTimer(3);
	else if(turnleft==TRUE)KillTimer(5);
	else if(FIND==TRUE)KillTimer(6);
	else KillTimer(1);

	//KillTimer(6);
	// TODO: Add your command handler code here
}


void CTRY3Dlg::OnGameFind()
{
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	KillTimer(5);
	FIND=TRUE;
	find();
	//SetTimer(1,2000,NULL);
	
	// TODO: Add your command handler code here
}


void CTRY3Dlg::OnGameContinue()
{
	if(turnup==TRUE){
		if(easy==TRUE)SetTimer(2,1000,NULL);
		else if(normal==TRUE)SetTimer(2,500,NULL);
		else 
			SetTimer(2,250,NULL);}
	else if(turndown==TRUE)
		{
			if(easy==TRUE)SetTimer(4,1000,NULL);
		else if(normal==TRUE)SetTimer(4,500,NULL);
		else 
			SetTimer(4,250,NULL);
	}
	else if(turnright==TRUE){
		if(easy==TRUE)SetTimer(3,1000,NULL);
		else if(normal==TRUE)SetTimer(3,500,NULL);
		else 
			SetTimer(3,250,NULL);}
	else if(turnleft==TRUE){
		if(easy==TRUE)SetTimer(5,1000,NULL);
		else if(normal==TRUE)SetTimer(5,500,NULL);
		else 
			SetTimer(5,250,NULL);}
	else if(FIND==TRUE)
		{
			if(easy==TRUE)SetTimer(6,1000,NULL);
		else if(normal==TRUE)SetTimer(6,500,NULL);
		else 
			SetTimer(6,250,NULL);}
	else {
		if(easy==TRUE)SetTimer(1,1000,NULL);
		else if(normal==TRUE)SetTimer(1,500,NULL);
		else 
		SetTimer(1,250,NULL);
	}
	// TODO: Add your command handler code here
}


void CTRY3Dlg::OnUpdateGame1(CCmdUI *pCmdUI)
{

	pCmdUI->Enable(start);
	
	// TODO: Add your command update UI handler code here
}


void CTRY3Dlg::OnDifficultySimple()
{
	easy=TRUE;
	normal=FALSE;
	// TODO: Add your command handler code here
	if(turnup==TRUE){KillTimer(2);SetTimer(2,1000,NULL);}
	else if(turndown==TRUE){KillTimer(4);SetTimer(4,1000,NULL);}
	else if(turnright==TRUE){KillTimer(3);SetTimer(3,1000,NULL);}
	else if(turnleft==TRUE){KillTimer(5);SetTimer(5,1000,NULL);}
	else if(FIND==TRUE){KillTimer(6);SetTimer(6,1000,NULL);}
	else {KillTimer(1);SetTimer(1,1000,NULL);}
}


void CTRY3Dlg::OnDifficultyNormal()
{
	easy=FALSE;normal=TRUE;
	// TODO: Add your command handler code here
	if(turnup==TRUE){KillTimer(2);SetTimer(2,500,NULL);}
	else if(turndown==TRUE){KillTimer(4);SetTimer(4,500,NULL);}
	else if(turnright==TRUE){KillTimer(3);SetTimer(3,500,NULL);}
	else if(turnleft==TRUE){KillTimer(5);SetTimer(5,500,NULL);}
	else if(FIND==TRUE){KillTimer(6);SetTimer(6,500,NULL);}
	else {KillTimer(1);SetTimer(1,500,NULL);}
}


void CTRY3Dlg::OnDifficultyHard()
{
	easy=FALSE;normal=FALSE;
	// TODO: Add your command handler code here
	if(turnup==TRUE){KillTimer(2);SetTimer(2,250,NULL);}
	else if(turndown==TRUE){KillTimer(4);SetTimer(4,250,NULL);}
	else if(turnright==TRUE){KillTimer(3);SetTimer(3,250,NULL);}
	else if(turnleft==TRUE){KillTimer(5);SetTimer(5,250,NULL);}
	else if(FIND==TRUE){KillTimer(6);SetTimer(6,250,NULL);}
	else {KillTimer(1);SetTimer(1,250,NULL);}
}
