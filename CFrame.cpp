/*
 * CFrame.cpp
 *
 *  Created on: 02 окт. 2013 г.
 *      Author: karpachevnk
 */

#include "CFrame.h"


namespace AppFrameNameSpace {


CFrame::CFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
		LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,int x,int y,int cx,int cy)
	: CBaseFrame(hinst,cstyle,hicon,hiconsm,hcursor,hbr,clname,fstyle,fstyleex,ftext,pparent,x,y,cx,cy)
{

}



CFrame::CFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,
		int x,int y,int cx,int cy)
	: CBaseFrame(hinst,clname,fstyle,fstyleex,ftext,pparent,x,y,cx,cy)
{

}


CFrame::CFrame(const CBaseFrame &src) : CBaseFrame(src)
{

}


LRESULT
CFrame::OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	return ::DefWindowProc(m_hWnd,msg,wp,lp);
}




CControlFrame::CControlFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,
		CBaseFrame *pparent,int x,int y,int cx,int cy)
	: CBaseFrame(hinst,clname,fstyle|WS_CHILD,fstyleex,ftext,pparent,x,y,cx,cy)
{
	// для элемента управления должен быть задан родительский фрейм
	if (pparent == NULL)
	{
		// обработка ошибки
		MessageBox(NULL,"Give me a parent! (I am a control element!!!)","Warning",MB_OK);
		PostQuitMessage(0);
	}
}




LRESULT
CControlFrame::OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	return ::CallWindowProc(m_WndProc,m_hWnd,msg,wp,lp);
}



CButton::CButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext)
	: CControlFrame(hinst,"BUTTON",BS_PUSHBUTTON,0,btext,pparent,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT)
{

}


CButton::CButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext,int x,int y,int cx,int cy)
	: CControlFrame(hinst,"BUTTON",BS_PUSHBUTTON,0,btext,pparent,x,y,cx,cy)
{

}


CStateButton::CStateButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext)
	: CControlFrame(hinst,"BUTTON",BS_AUTOCHECKBOX|BS_PUSHLIKE,0,btext,pparent,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT)
{

}


CStateButton::CStateButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext,int x,int y,int cx,int cy)
	: CControlFrame(hinst,"BUTTON",BS_AUTOCHECKBOX|BS_PUSHLIKE,0,btext,pparent,x,y,cx,cy)
{

}


CGroupBox::CGroupBox(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR gbtext)
	: CControlFrame(hinst,"BUTTON",BS_GROUPBOX,0,gbtext,pparent,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT)
{

}


CGroupBox::CGroupBox(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR gbtext,int x,int y,int cx,int cy)
	: CControlFrame(hinst,"BUTTON",BS_GROUPBOX,0,gbtext,pparent,x,y,cx,cy)
{

}




CTreeView::CTreeView(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext,int x,int y,int cx,int cy)
	: CControlFrame(hinst,WC_TREEVIEW,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS,0,btext,pparent,x,y,cx,cy)
{
	TVINSERTSTRUCT tvi;

	tvi.hParent = TVI_ROOT;
	tvi.hInsertAfter = TVI_FIRST;
	tvi.item.mask = TVIF_TEXT;
	tvi.item.pszText = (LPSTR)"My Tree Item";

	tvi.hParent = TreeView_InsertItem(m_hWnd,&tvi);
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.pszText = (LPSTR)"First Item";

	tvi.hParent = TreeView_InsertItem(m_hWnd,&tvi);
	tvi.hParent = TreeView_InsertItem(m_hWnd,&tvi);
}



CDialogFrame::CDialogFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
		LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,int x,int y,int cx,int cy)
	: CBaseFrame(hinst,cstyle,hicon,hiconsm,hcursor,hbr,clname,fstyle,fstyleex,ftext,pparent,x,y,cx,cy)
{
	InitCommonControls();
}



CDialogFrame::~CDialogFrame()
{
	// очищаем список элементов управления
	while (!m_ChildList.empty())
	{
		delete m_ChildList.back();
		m_ChildList.pop_back();
	}
}


BOOL
CDialogFrame::AddButton(LPCTSTR btext,int x,int y,int cx,int cy)
{
	CButton * butt = new CButton(m_hInst,this,btext,x,y,cx,cy);
	butt->ShowFrame();
	AddControlFrame(butt);
	return TRUE;
}

BOOL
CDialogFrame::AddStateButton(LPCTSTR btext,int x,int y,int cx,int cy)
{
	CStateButton * butt = new CStateButton(m_hInst,this,btext,x,y,cx,cy);
	butt->ShowFrame();
	AddControlFrame(butt);
	return TRUE;
}


BOOL
CDialogFrame::AddGroupBox(LPCTSTR gbtext,int x,int y,int cx,int cy)
{
	CStateButton * butt = new CStateButton(m_hInst,this,gbtext,x,y,cx,cy);
	butt->ShowFrame();
	AddControlFrame(butt);
	return TRUE;
}



BOOL
CDialogFrame::AddTreeView(LPCTSTR ttext, int x,int y,int cx,int cy)
{
	CTreeView * tree = new CTreeView(m_hInst,this,ttext,x,y,cx,cy);
	tree->ShowFrame();
	AddControlFrame(tree);
	return TRUE;
}




LRESULT
CDialogFrame::OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_NOTIFY:
			switch (((LPNMHDR)lp)->code)
			{
				case TVN_SELCHANGED:	// выбран элемент дерева
					LPNMTREEVIEW pNMTreeView = (LPNMTREEVIEW)lp;

					::MessageBox(m_hWnd,"Изменился выбранный элемент","Внимание",MB_OK);
					break;
			}
			break;

		case WM_COMMAND:
			if (lp != 0)	// значит сообщение от элемента управления
			{
				OnButtonPush((CControlFrame*)GetFramePtr((HWND)lp));
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return ::DefWindowProc(m_hWnd,msg,wp,lp);
	}

	return 0;
}


void
CDialogFrame::OnButtonPush(CControlFrame * pbutton)
{
//	::MessageBox(m_hWnd,"Button action","wnimanie",MB_OK);
	//DeleteControlFrame(pbutton);
}


BOOL
CDialogFrame::AddControlFrame(CControlFrame * pframe)
{
	if (pframe != NULL)
	{
		m_ChildList.push_back(pframe);
		return TRUE;
	}
	return FALSE;
}


void
CDialogFrame::DeleteControlFrame(CControlFrame * pframe)
{
	if (pframe != NULL)
	{
		m_ChildList.remove(pframe);
		pframe->DestroyFrame();
		delete pframe;
	}
}


} /* namespace AppFrameNameSpace */
