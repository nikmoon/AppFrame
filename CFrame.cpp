/*
 * CFrame.cpp
 *
 *  Created on: 02 окт. 2013 г.
 *      Author: karpachevnk
 */

#include "CFrame.h"


namespace AppFrameNameSpace {


CFrame::CFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
		LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,CBaseFrame *pparent,int x,int y,int cx,int cy)
	: CBaseFrame(hinst,cstyle,hicon,hiconsm,hcursor,hbr,clname,fstyle,fstyleex,fname,pparent,x,y,cx,cy)
{

}



CFrame::CFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,CBaseFrame *pparent,
		int x,int y,int cx,int cy)
	: CBaseFrame(hinst,clname,fstyle,fstyleex,fname,pparent,x,y,cx,cy)
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





CButton::CButton(HINSTANCE hinst,CFrame *pparent,LPCTSTR btext)
	: CFrame(hinst,"BUTTON",BS_PUSHBUTTON|WS_CHILD,0,btext,pparent,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT)
{
	// для элемента управления должен быть задан родительский фрейм
	if (pparent == NULL)
	{
		// обработка ошибки
		MessageBox(NULL,"Give me a parent! (button)","Warning",MB_OK);
		PostQuitMessage(0);
	}
}


LRESULT
CButton::OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	return ::CallWindowProc(m_WndProc,m_hWnd,msg,wp,lp);
}






CMainFrame::CMainFrame(HINSTANCE hinst,LPCTSTR title,int x,int y,int cx,int cy)
	: CFrame(hinst,CS_HREDRAW|CS_VREDRAW,0,0,0,0,"CMainFrame",WS_OVERLAPPEDWINDOW,0,title,NULL,x,y,cx,cy)
{
	pButtonExit = new CButton(m_hInst,this,"Выход");
	pButtonExit->MoveFrame(0,0, 100, 30, FALSE);
	pButtonExit->ShowFrame();

	pButtonHello = new CButton(m_hInst,this,"Привет");
	pButtonHello->MoveFrame(110,0, 100, 30, TRUE);
	pButtonHello->ShowFrame();

	pButtonQwer = new CButton(m_hInst,this,"Qwer");
	pButtonQwer->MoveFrame(220,0, 100, 30, TRUE);
	pButtonQwer->ShowFrame();

}


CMainFrame::~CMainFrame()
{
	delete pButtonExit;
	delete pButtonHello;
}


LRESULT
CMainFrame::OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return CFrame::OnFrameEvent(msg,wp,lp);
	}

	return 0;
}


} /* namespace AppFrameNameSpace */
