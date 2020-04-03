
// TRY 3Dlg.h : header file
//

#pragma once
#include<iostream>
using namespace std;

typedef   struct Node
{
	int data;//0啥都没，1蛇身，2蛇头，3食物
	int x;
	int y;
	int F;
	int G;
	int H;
	int  Open_flag;
	int close_flag;
	struct Node *next;
	struct Node *final_next;
}Node;
int check_around( Node* curNode,Node endNode,Node* &openlist,Node **map,int wx,int wy,int wt,int wb);
void free_array2D(Node **arr);
Node *List();

//int FindInList(Node *curNode,LinkList openlist);
//Node *minNode(LinkList openlist);
Node* insert(Node* list,Node *node);
//Node* sort(LinkList List);
//bool GotoClose(Node *minNode,LinkList closelist);

int count_G(Node *ParentNode);
int count_H(Node *curNode,Node *endNode);
int count_F(Node *curNode);

bool InTheOpenList(Node *node);
bool InTheCloseList(Node *node);
int check_around( Node* curNode,Node endNode,Node* &openlist,Node **map);
// CTRY3Dlg dialog
class CTRY3Dlg : public CDialogEx
{
// Construction
public:
	CTRY3Dlg(CWnd* pParent = NULL);	// standard constructor
	CFont m_newFont;
	CFont m_Font;
	CFont *m_oldFont;
	CString str;
	int a1,a2,a3,a4,a5;
	int J;
	int wx;
	int wy;
	int wt;
	int wb;
	int midx;
	int midy;
	int foodX;
	int foodY;
	int LENGTH;
	bool left;
	bool right;
	bool up;
	bool down;
	bool turnup;
	bool turndown;
	bool turn;
	bool turnleft;
	bool turnright;
	bool start;
	bool FIND;
	bool up1;
	bool down1;
	bool left1;
	bool right1;
	bool move;
	int startx,starty;
	int sss;
	int a[500][2];
	int b[500][2];
	bool easy,normal;
	CRect wallrect;
	LOGFONT logfont;
	bool eat();
	void  foodprovide();
	bool hit();
	void find();
	void Turnup();
	void Turndown();
	void Turnleft();
	void Turnright();
	void Move(int x,int y,int a,int b);
	

// Dialog Data
	enum { IDD = IDD_TRY3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGameStart();
	afx_msg void OnGamePause();
	afx_msg void OnGameFind();
	afx_msg void OnGameContinue();
	afx_msg void OnUpdateGame1(CCmdUI *pCmdUI);
	afx_msg void OnDifficultySimple();
	afx_msg void OnDifficultyNormal();
	afx_msg void OnDifficultyHard();
};
