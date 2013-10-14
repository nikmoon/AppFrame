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




CDialogFrame::CDialogFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
		LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,int x,int y,int cx,int cy)
	: CBaseFrame(hinst,cstyle,hicon,hiconsm,hcursor,hbr,clname,fstyle,fstyleex,ftext,pparent,x,y,cx,cy)
{
	m_ChildCount = 0;
	m_pChildArray = new CControlFrame* [MAX_CHILD_COUNT+1];	// +1 для завершающего NULL
	m_pChildArray[0] = NULL;
}



CDialogFrame::~CDialogFrame()
{

	// удаляем все созданные элементы в массиве
	UINT i = 0;
	while(m_pChildArray[i] != NULL)
	{
		delete m_pChildArray[i];
		i++;
	}

	// удаляем сам массив
	delete [] m_pChildArray;
}


CControlFrame *
CDialogFrame::AddButton(LPCTSTR btext,int x,int y,int cx,int cy)
{
	// проверяем свободное место в массиве
	if (m_ChildCount < MAX_CHILD_COUNT)
	{
		CControlFrame * ptemp = new CStateButton(m_hInst,this,btext,x,y,cx,cy);
		ptemp->ShowFrame();
		m_pChildArray[m_ChildCount] = ptemp;
		m_ChildCount++;
		m_pChildArray[m_ChildCount] = NULL;
		return ptemp;
	}

	return NULL;
}




LRESULT
CDialogFrame::OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
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
//	pbutton->DestroyFrame();
}




} /* namespace AppFrameNameSpace */
