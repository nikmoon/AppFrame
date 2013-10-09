/*
 * CFrame.cpp
 *
 *  Created on: 02 ���. 2013 �.
 *      Author: karpachevnk
 */

#include "CFrame.h"


namespace AppFrameNameSpace {



//--------------------------------------------------------------------------
//
//	����������� �������� ������ � �������
//
//--------------------------------------------------------------------------
ATOM
RegisterFrameClass(HINSTANCE hinst, UINT cstyle, HICON hicon, HICON hiconsm, HCURSOR hcursor, HBRUSH hbr,
		LPCTSTR clname)
{
	WNDCLASSEX wc;

	// �������������� ����������� ������ ��� ����������� �������� ������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = cstyle;
	wc.lpfnWndProc = &CFrame::BindWndProc;
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


//--------------------------------------------------------------------------
//
//	������ ����������� �������� ������ � �������
//
//--------------------------------------------------------------------------
BOOL
UnregisterFrameClass(LPCTSTR clname, HINSTANCE hinst)
{
	return ::UnregisterClass(clname, hinst);
}



//--------------------------------------------------------------------------
//
//	�������� ������ ���� � �������
//
//--------------------------------------------------------------------------
HWND CreateFrame(HINSTANCE hinst, DWORD style, DWORD exstyle, LPCTSTR clname, LPCTSTR fname,
		CFrame *pparent, int x,int y,int cx,int cy)
{
	HWND
	hparent = (pparent == NULL) ? NULL : pparent->m_hWnd;

	return ::CreateWindowEx(exstyle,clname,fname,style,x,y,cx,cy,hparent,NULL,hinst,NULL);
}



//--------------------------------------------------------------------------
//
//	���������� ���� ������� � ����� ����������� ��� ���������
//	���� ��������� ������� ����
//
//--------------------------------------------------------------------------
WNDPROC
CFrame::BindFrame(HWND hwnd)
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
CFrame::UnbindFrame()
{
	// ������� �� ��������� ��������� ���� ����� ������ ����������
	// ��� �������������
	//::SetWindowLongPtr(m_hWnd,GWLP_USERDATA,(LONG_PTR)this);

	// ��������������� ����� ������� ���������
	if (m_WndProc != NULL)
	{
		::SetWindowLongPtr(m_hWnd,GWLP_WNDPROC,(LONG_PTR)m_WndProc);
	}
}



//--------------------------------------------------------------------------
//
//	�������� ����������� CFrame (� ������������ �������� ������)
//
//--------------------------------------------------------------------------
CFrame::CFrame(HINSTANCE hinst, UINT cstyle, HICON hicon, HICON hiconsm, HCURSOR hcursor, HBRUSH hbr, LPCTSTR clname,
		DWORD fstyle, DWORD fstyleex, LPCTSTR fname, CFrame *pparent, int x, int y, int cx,int cy)
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

	m_hInst = hinst;
	m_ClassName = clname;
}


//--------------------------------------------------------------------------
//
//	�������� ����������� CFrame (��� ����������� �������� ������)
//
//--------------------------------------------------------------------------
CFrame::CFrame(HINSTANCE hinst, LPCTSTR clname, DWORD fstyle, DWORD fstyleex, LPCTSTR fname, CFrame *pparent,
		int x, int y, int cx, int cy)
{
	// �������� ���� � �������
	m_hWnd = CreateFrame(hinst, fstyle, fstyleex, clname, fname, pparent, x, y, cx, cy);
	if (m_hWnd == NULL)
	{
		// ��������� ������
	}

	// ������������ ����� ������ ������� � ��������� ����� ��� ��������� ���������
	m_WndProc = BindFrame(m_hWnd);

	m_hInst = hinst;
	m_ClassName = clname;
}



//--------------------------------------------------------------------------
//
//	���������� CFrame
//
//--------------------------------------------------------------------------
CFrame::~CFrame()
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
CFrame::GetStyle() const
{
	return ::GetWindowLongPtr(m_hWnd,GWL_STYLE);
}


//--------------------------------------------------------------------------
//
//		��������� ������������ ����� ����
//
//--------------------------------------------------------------------------
DWORD
CFrame::GetExStyle() const
{
	return ::GetWindowLongPtr(m_hWnd,GWL_EXSTYLE);
}



//--------------------------------------------------------------------------
//
//		��������� ��������� ����� ����
//
//--------------------------------------------------------------------------
DWORD
CFrame::SetStyle(DWORD style)
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
CFrame::SetExStyle(DWORD styleex)
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
CFrame::ShowFrame()
{
	::ShowWindow(m_hWnd, SW_SHOW);
	::UpdateWindow(m_hWnd);
}



//--------------------------------------------------------------------------
//
//	������ �������� (��������) ������
//
//--------------------------------------------------------------------------
void
CFrame::HideFrame()
{
	::ShowWindow(m_hWnd,SW_HIDE);
}


//--------------------------------------------------------------------------
//
//	�����������/��������� ������� ������
//
//--------------------------------------------------------------------------
BOOL
CFrame::MoveFrame(int x,int y,int cx,int cy, BOOL repaint)
{
	return ::MoveWindow(m_hWnd,x,y,cx,cy,repaint);
}




//--------------------------------------------------------------------------
//
//	���������� �������
//
//--------------------------------------------------------------------------
BOOL
CFrame::OnFrameDestroy()
{
	return FALSE;
}


//--------------------------------------------------------------------------
//
//	���������� �������
//
//--------------------------------------------------------------------------
BOOL
CFrame::OnFrameClose()
{
	int mbres = ::MessageBox(m_hWnd,"Frame is closing", "Warning", MB_OKCANCEL);
	if (mbres == IDOK)
	{
		DestroyFrame();
	}
	return FALSE;
}



//--------------------------------------------------------------------------
//
//	���������� �������
//
//--------------------------------------------------------------------------
BOOL
CFrame::OnFrameRepaint()
{
	return TRUE;
}


//--------------------------------------------------------------------------
//
//	���������� �������
//
//--------------------------------------------------------------------------
BOOL
CFrame::OnControlEvent(CFrame * ct, DWORD evcode)
{
	return FALSE;
}



//--------------------------------------------------------------------------
//
//	��������������� ���������� ���� ��������� �������
//
//--------------------------------------------------------------------------
LRESULT CALLBACK
CFrame::BindWndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	// �������� ��������� � ����� ��������� ������
	CFrame * pframe = (CFrame*)::GetWindowLongPtr(hwnd,GWLP_USERDATA);

	// ���� ���������� ����������� (WM_CREATE, WM_NCCREATE � �.�.)
	if (pframe == NULL)
	{
		return ::DefWindowProc(hwnd,msg,wp,lp);
	}

	// ���� �������� �� ������������� ������ ��������� ������� ���������
	// ���������� ������������ ������ ���������� ���� � 0, ����� ��������� ��������� �� ����������
	BOOL fCallDefault = TRUE;


	switch (msg)
	{
		// ��������� ���� ������������
		case WM_DESTROY:
			pframe->UnbindFrame();			// ���������� ��� ��������� ������ �� ���������� ����
			fCallDefault = pframe->OnFrameDestroy();	// ���������� �������
			break;

		case WM_CLOSE:
			fCallDefault = pframe->OnFrameClose();
			break;

		case WM_PAINT:
			fCallDefault = pframe->OnFrameRepaint();
			break;

		// �������� ��������� �� �������� ��� �.�.
		case WM_COMMAND:
			if (lp != 0)	// ���� ��������� �������� �� ��������� �������� ����������
			{
				// �������� ���������� ���������
				fCallDefault = pframe->OnControlEvent((CFrame*)::GetWindowLongPtr((HWND)lp,GWLP_USERDATA),HIWORD(wp));
			}
			break;
	}

	// ���� ������� ��������� ���� ����� ����������� ��������������, �������� ������������ ���������
	if (pframe->m_WndProc != NULL)
	{
		fCallDefault = ::CallWindowProc(pframe->m_WndProc,hwnd,msg,wp,lp);
	}
	else
	{
		// ���� ���������� ������� ��������� ������� ���������
		if (fCallDefault)
		{
			// ������ ���
			fCallDefault = ::DefWindowProc(hwnd,msg,wp,lp);
		}
	}
	return fCallDefault;
}



//--------------------------------------------------------------------------
//
//	���������� �������
//
//--------------------------------------------------------------------------
CButtonFrame::CButtonFrame(HINSTANCE hinst, LPCTSTR btext, CFrame * pparent)
	: CFrame(hinst, "BUTTON", BS_PUSHBUTTON|WS_CHILD, 0, btext, pparent,
			CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT)
{
	// ���������� ������� ������ ������ ����� ������
	if (pparent == NULL)
	{
		// ��� ������� ����������
	}
}



CTestFrame::CTestFrame(HINSTANCE hinst,LPCTSTR fname)
	: CFrame(hinst, CS_HREDRAW|CS_VREDRAW, NULL, NULL, NULL, NULL, "AppFrameClass", WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			0, fname, NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT)
{
	m_pButton1 = new CButtonFrame(hinst,"Buton1",this);
	m_pButton1->MoveFrame(0,0,100,50,FALSE);
	m_pButton1->ShowFrame();

	m_pButton2 = new CButtonFrame(hinst,"Button2",this);
	m_pButton2->MoveFrame(150,0,100,50,FALSE);
	m_pButton2->ShowFrame();
}


CTestFrame::~CTestFrame()
{
	delete m_pButton1;
	delete m_pButton2;
}



BOOL
CTestFrame::OnFrameDestroy()
{
	PostQuitMessage(0);
	return FALSE;
}


BOOL
CTestFrame::OnControlEvent(CFrame * ct, DWORD evcode)
{
	if ((ct == m_pButton1) || (ct == m_pButton2))	// ������ ������ m_pButton
	{
		DWORD style_curr = ct->GetStyle() ^ (WS_SIZEBOX | WS_CAPTION);
		ct->SetStyle(style_curr);

//		::MessageBox(m_hWnd, "Button WS_SIZEBOX changed", "Event", MB_OK);
	}
	return FALSE;
}


} /* namespace AppFrameNameSpace */
