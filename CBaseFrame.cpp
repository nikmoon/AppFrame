/*
 * CBaseFrame.cpp
 *
 *  Created on: 09 ���. 2013 �.
 *      Author: karpachevnk
 */

#include "CBaseFrame.h"

namespace AppFrameNameSpace
{



ATOM
CBaseFrame::RegisterFrameClass(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,
		HBRUSH hbr,LPCTSTR clname)
{
	WNDCLASSEX wc;

	// �������������� ����������� ������ ��� ����������� �������� ������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = cstyle;
	wc.lpfnWndProc = &BindWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinst;
	wc.hIcon = (hicon != NULL) ? hicon : ::LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = (hcursor != NULL) ? hcursor : ::LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (hbr != NULL) ? hbr : (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = clname;
	wc.hIconSm = (hiconsm != NULL) ? hiconsm : ::LoadIcon(NULL,IDI_APPLICATION);

	return ::RegisterClassEx(&wc);
}



BOOL
CBaseFrame::UnregisterFrameClass(LPCTSTR clname, HINSTANCE hinst)
{
	return ::UnregisterClass(clname, hinst);
}


//--------------------------------------------------------------------------
//
//	�������� ������ ���� � �������
//
//--------------------------------------------------------------------------
HWND
CBaseFrame::CreateFrame(HINSTANCE hinst, DWORD style, DWORD exstyle, LPCTSTR clname, LPCTSTR fname,
		CBaseFrame *pparent, int x,int y,int cx,int cy)
{
	HWND
	hparent = (pparent == NULL) ? NULL : pparent->m_hWnd;

	return ::CreateWindowEx(exstyle,clname,fname,style,x,y,cx,cy,hparent,NULL,hinst,NULL);
}


//--------------------------------------------------------------------------
//
//	�������� ����������� CBaseFrame (� ������������ �������� ������)
//
//--------------------------------------------------------------------------
CBaseFrame::CBaseFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
		LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,CBaseFrame *pparent,int x,int y,int cx,int cy)
{
	ATOM
	// ����������� �������� ������
	regResult = RegisterFrameClass(hinst, cstyle, hicon, hiconsm, hcursor, hbr, clname);
	if (regResult == 0)
	{
		// ��������� ������
	}

	// �������� ���� � �������
	m_hWnd = CreateFrame(hinst, fstyle, fstyleex, clname, fname, pparent, x, y, cx, cy);
	if (m_hWnd == NULL)
	{
		// ��������� ������
	}

	// ������������ ����� ������ ������� � ��������� ����� ��� ��������� ���������
	m_WndProc = BindFrame(m_hWnd);

	m_Parent = pparent;
	m_hInst = hinst;
	m_ClassName = clname;
}


//--------------------------------------------------------------------------
//
//	�������� ����������� CBaseFrame (��� ����������� �������� ������)
//
//--------------------------------------------------------------------------
CBaseFrame::CBaseFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,
		CBaseFrame *pparent,int x,int y,int cx,int cy)
{
	// �������� ���� � �������
	m_hWnd = CreateFrame(hinst, fstyle, fstyleex, clname, fname, pparent, x, y, cx, cy);
	if (m_hWnd == NULL)
	{
		// ��������� ������
	}

	// ������������ ����� ������ ������� � ��������� ����� ��� ��������� ���������
	m_WndProc = BindFrame(m_hWnd);

	m_Parent = pparent;
	m_hInst = hinst;
	m_ClassName = clname;
}




CBaseFrame::CBaseFrame(const CBaseFrame &src)
{
	m_hWnd = CreateFrame(src.m_hInst,src.GetStyle(),src.GetExStyle(),src.m_ClassName.c_str(), "copy",
			src.m_Parent, CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT);
	if (m_hWnd == NULL)
	{
		// ��������� ������
	}

	m_WndProc = BindFrame(m_hWnd);
	m_Parent = src.m_Parent;
	m_hInst = src.m_hInst;
	m_ClassName = src.m_ClassName;
}


//--------------------------------------------------------------------------
//
//	���������� CBaseFrame
//
//--------------------------------------------------------------------------
CBaseFrame::~CBaseFrame()
{
	// ���� ��� �������� ���������� ���� ��������������� ����� �����
	if (m_WndProc == NULL)
	{
		// �������� ����������� ������
		// ������ ����� ����� ��������, ������ ����� ����� ���������� ��� ����������
		// ���������� ����, ������� ������ ��������� � ������ ��� ������� ���������� ���
		UnregisterFrameClass(m_ClassName.c_str(), m_hInst);
	}
}



//--------------------------------------------------------------------------
//
//		��������� ��������� ����� ����
//
//--------------------------------------------------------------------------
DWORD
CBaseFrame::GetStyle() const
{
	return ::GetWindowLongPtr(m_hWnd,GWL_STYLE);
}


//--------------------------------------------------------------------------
//
//		��������� ������������ ����� ����
//
//--------------------------------------------------------------------------
DWORD
CBaseFrame::GetExStyle() const
{
	return ::GetWindowLongPtr(m_hWnd,GWL_EXSTYLE);
}



//--------------------------------------------------------------------------
//
//		��������� ��������� ����� ����
//
//--------------------------------------------------------------------------
DWORD
CBaseFrame::SetStyle(DWORD style)
{
	DWORD oldStyle = ::SetWindowLongPtr(m_hWnd, GWL_STYLE, style);
	::SetWindowPos(m_hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER);
	return oldStyle;
}


//--------------------------------------------------------------------------
//
//		��������� ������������ ����� ����
//
//--------------------------------------------------------------------------
DWORD
CBaseFrame::SetExStyle(DWORD styleex)
{
	DWORD oldStyleEx = ::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, styleex);
	::SetWindowPos(m_hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER);
	return oldStyleEx;
}


//--------------------------------------------------------------------------
//
//	����������� ������ �� ������� �����
//
//--------------------------------------------------------------------------
void
CBaseFrame::ShowFrame()
{
	::ShowWindow(m_hWnd, SW_SHOW);
}



//--------------------------------------------------------------------------
//
//	���������� ������
//
//--------------------------------------------------------------------------
void
CBaseFrame::UpdateFrame()
{
	::UpdateWindow(m_hWnd);
}


//--------------------------------------------------------------------------
//
//	������ �������� (��������) ������
//
//--------------------------------------------------------------------------
void
CBaseFrame::HideFrame()
{
	::ShowWindow(m_hWnd,SW_HIDE);
}


//--------------------------------------------------------------------------
//
//	�����������/��������� ������� ������
//
//--------------------------------------------------------------------------
BOOL
CBaseFrame::MoveFrame(int x,int y,int cx,int cy, BOOL repaint)
{
	return ::MoveWindow(m_hWnd,x,y,cx,cy,repaint);
}


//--------------------------------------------------------------------------
//
//	�������� ���������� ����
//
//--------------------------------------------------------------------------
void
CBaseFrame::DestroyFrame()
{
	::DestroyWindow(m_hWnd);
}



//--------------------------------------------------------------------------
//
//	����������� ���������� ��������� �������
//
//--------------------------------------------------------------------------
LRESULT CALLBACK
CBaseFrame::BindWndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	LRESULT ResVal;

	// �������� ��������� � ����� ��������� ������
	CBaseFrame * pframe = (CBaseFrame*)::GetWindowLongPtr(hwnd,GWLP_USERDATA);

	if (pframe != NULL)
	{
		ResVal = pframe->OnFrameEvent(msg,wp,lp);
		if (msg == WM_DESTROY)
		{
			pframe->UnbindFrame();
		}
	}
	else // ���������� �����������, �������� ������
	{
		ResVal = ::DefWindowProc(hwnd,msg,wp,lp);
	}

	return ResVal;
}


//--------------------------------------------------------------------------
//
//	���������� ���� ������� � ����� ����������� ��� ���������
//	���� ��������� ������� ����
//
//--------------------------------------------------------------------------
WNDPROC
CBaseFrame::BindFrame(HWND hwnd)
{
	// ��������� � ��������� ��������� ���� ����� ������ ����������
	::SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)this);

	// ��������, ����� �� �������� ������� ���������
	WNDPROC wproc = (WNDPROC)::GetWindowLongPtr(hwnd,GWLP_WNDPROC);
	if (wproc != BindWndProc)
	{
		// �������� ������� ���������
		return (WNDPROC)::SetWindowLongPtr(hwnd,GWLP_WNDPROC,(LONG_PTR)BindWndProc);
	}

	return NULL;
}


//--------------------------------------------------------------------------
//
//	���������� ����� ���� ������� � ����� �����������
//
//--------------------------------------------------------------------------
void
CBaseFrame::UnbindFrame()
{
	// ������� �� ��������� ��������� ���� ����� ������ ����������
	::SetWindowLongPtr(m_hWnd,GWLP_USERDATA,(LONG_PTR)NULL);

	// ��������������� ����� ������� ���������
	if (m_WndProc != NULL)
	{
		//::SetWindowLongPtr(m_hWnd,GWLP_WNDPROC,(LONG_PTR)m_WndProc);
	}
}



} /* namespace AppFrameNameSpace */
