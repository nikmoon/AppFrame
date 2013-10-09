/*
 * CFrame.cpp
 *
 *  Created on: 02 окт. 2013 г.
 *      Author: karpachevnk
 */

#include "CFrame.h"


namespace AppFrameNameSpace {



//--------------------------------------------------------------------------
//
//	Регистрация оконного класса в системе
//
//--------------------------------------------------------------------------
ATOM
RegisterFrameClass(HINSTANCE hinst, UINT cstyle, HICON hicon, HICON hiconsm, HCURSOR hcursor, HBRUSH hbr,
		LPCTSTR clname)
{
	WNDCLASSEX wc;

	// подготавливаем необходимые данные для регистрации оконного класса
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
//	Отмена регистрации оконного класса в системе
//
//--------------------------------------------------------------------------
BOOL
UnregisterFrameClass(LPCTSTR clname, HINSTANCE hinst)
{
	return ::UnregisterClass(clname, hinst);
}



//--------------------------------------------------------------------------
//
//	Создание нового окна в системе
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
//	Связывание окна системы с нашим экземпляром для перехвата
//	всех сообщений системы окну
//
//--------------------------------------------------------------------------
WNDPROC
CFrame::BindFrame(HWND hwnd)
{
	// добавляем в системную структуру окна адрес нашего экземпляра
	::SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)this);

	// проверим, нужно ли заменять оконную процедуру
	WNDPROC wproc = (WNDPROC)::GetWindowLongPtr(hwnd,GWLP_WNDPROC);
	if (wproc != BindWndProc)
	{
		// заменяем оконную процедуру
		return (WNDPROC)::SetWindowLongPtr(hwnd,GWLP_WNDPROC,(LONG_PTR)BindWndProc);
	}

	return NULL;
}


//--------------------------------------------------------------------------
//
//	Разрывание связи окна системы с нашим экземпляром
//
//--------------------------------------------------------------------------
void
CFrame::UnbindFrame()
{
	// удаляем из системной структуры окна адрес нашего экземпляра
	// ЭТО НЕОБЯЗАТЕЛЬНО
	//::SetWindowLongPtr(m_hWnd,GWLP_USERDATA,(LONG_PTR)this);

	// восстанавливаем адрес оконной процедуры
	if (m_WndProc != NULL)
	{
		::SetWindowLongPtr(m_hWnd,GWLP_WNDPROC,(LONG_PTR)m_WndProc);
	}
}



//--------------------------------------------------------------------------
//
//	Основной конструктор CFrame (с регистрацией оконного класса)
//
//--------------------------------------------------------------------------
CFrame::CFrame(HINSTANCE hinst, UINT cstyle, HICON hicon, HICON hiconsm, HCURSOR hcursor, HBRUSH hbr, LPCTSTR clname,
		DWORD fstyle, DWORD fstyleex, LPCTSTR fname, CFrame *pparent, int x, int y, int cx,int cy)
{
	ATOM
	// регистрация оконного класса
	regResult = RegisterFrameClass(hinst, cstyle, hicon, hiconsm, hcursor, hbr, clname);
	if (regResult == 0)
	{
		// обработка ошибок
	}

	// создание окна в системе
	m_hWnd = CreateFrame(hinst, fstyle, fstyleex, clname, fname, pparent, x, y, cx, cy);
	if (m_hWnd == NULL)
	{
		// обработка ошибок
	}

	// обеспечиваем связь нашего объекта с системным окном при обработке сообщений
	m_WndProc = BindFrame(m_hWnd);

	m_hInst = hinst;
	m_ClassName = clname;
}


//--------------------------------------------------------------------------
//
//	Основной конструктор CFrame (без регистрации оконного класса)
//
//--------------------------------------------------------------------------
CFrame::CFrame(HINSTANCE hinst, LPCTSTR clname, DWORD fstyle, DWORD fstyleex, LPCTSTR fname, CFrame *pparent,
		int x, int y, int cx, int cy)
{
	// создание окна в системе
	m_hWnd = CreateFrame(hinst, fstyle, fstyleex, clname, fname, pparent, x, y, cx, cy);
	if (m_hWnd == NULL)
	{
		// обработка ошибок
	}

	// обеспечиваем связь нашего объекта с системным окном при обработке сообщений
	m_WndProc = BindFrame(m_hWnd);

	m_hInst = hinst;
	m_ClassName = clname;
}



//--------------------------------------------------------------------------
//
//	Деструктор CFrame
//
//--------------------------------------------------------------------------
CFrame::~CFrame()
{
	// если для создания системного окна регистрировался новый класс
	if (m_WndProc == NULL)
	{
		// отменяем регистрацию класса
		// данный вызов будет успешным, только когда будет произведен для последнего
		// удаляемого окна, поэтому ничего страшного в вызове для каждого экземпляра нет
		UnregisterFrameClass(m_ClassName.c_str(), m_hInst);
	}
}


//--------------------------------------------------------------------------
//
//		Получение основного стиля окна
//
//--------------------------------------------------------------------------
DWORD
CFrame::GetStyle() const
{
	return ::GetWindowLongPtr(m_hWnd,GWL_STYLE);
}


//--------------------------------------------------------------------------
//
//		Получение расширенного стиля окна
//
//--------------------------------------------------------------------------
DWORD
CFrame::GetExStyle() const
{
	return ::GetWindowLongPtr(m_hWnd,GWL_EXSTYLE);
}



//--------------------------------------------------------------------------
//
//		Изменение основного стиля окна
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
//		Изменение расширенного стиля окна
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
//	Отображение фрейма на рабочем столе
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
//	Полное сокрытие (закрытие) фрейма
//
//--------------------------------------------------------------------------
void
CFrame::HideFrame()
{
	::ShowWindow(m_hWnd,SW_HIDE);
}


//--------------------------------------------------------------------------
//
//	Перемещение/изменение размера фрейма
//
//--------------------------------------------------------------------------
BOOL
CFrame::MoveFrame(int x,int y,int cx,int cy, BOOL repaint)
{
	return ::MoveWindow(m_hWnd,x,y,cx,cy,repaint);
}




//--------------------------------------------------------------------------
//
//	Обработчик события
//
//--------------------------------------------------------------------------
BOOL
CFrame::OnFrameDestroy()
{
	return FALSE;
}


//--------------------------------------------------------------------------
//
//	Обработчик события
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
//	Обработчик события
//
//--------------------------------------------------------------------------
BOOL
CFrame::OnFrameRepaint()
{
	return TRUE;
}


//--------------------------------------------------------------------------
//
//	Обработчик события
//
//--------------------------------------------------------------------------
BOOL
CFrame::OnControlEvent(CFrame * ct, DWORD evcode)
{
	return FALSE;
}



//--------------------------------------------------------------------------
//
//	Перехватывающий обработчик всех сообщений системы
//
//--------------------------------------------------------------------------
LRESULT CALLBACK
CFrame::BindWndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	// получаем связанный с окном экземпляр класса
	CFrame * pframe = (CFrame*)::GetWindowLongPtr(hwnd,GWLP_USERDATA);

	// если связывание отсутствует (WM_CREATE, WM_NCCREATE и т.д.)
	if (pframe == NULL)
	{
		return ::DefWindowProc(hwnd,msg,wp,lp);
	}

	// флаг отвечает за необходимость вызова дефолтной оконной процедуры
	// обработчик пользователя должен установить флаг в 0, чтобы дефолтная процедура не вызывалась
	BOOL fCallDefault = TRUE;


	switch (msg)
	{
		// системное окно уничтожается
		case WM_DESTROY:
			pframe->UnbindFrame();			// отвязываем наш экземпляр класса от системного окна
			fCallDefault = pframe->OnFrameDestroy();	// обработчик события
			break;

		case WM_CLOSE:
			fCallDefault = pframe->OnFrameClose();
			break;

		case WM_PAINT:
			fCallDefault = pframe->OnFrameRepaint();
			break;

		// получено сообщение от контрола или т.п.
		case WM_COMMAND:
			if (lp != 0)	// если сообщение получено от дочернего элемента управления
			{
				// вызываем обработчик сообщений
				fCallDefault = pframe->OnControlEvent((CFrame*)::GetWindowLongPtr((HWND)lp,GWLP_USERDATA),HIWORD(wp));
			}
			break;
	}

	// если оконная процедура была нашим экземпляром переопределена, вызываем оригинальную процедуру
	if (pframe->m_WndProc != NULL)
	{
		fCallDefault = ::CallWindowProc(pframe->m_WndProc,hwnd,msg,wp,lp);
	}
	else
	{
		// если необходимо вызвать дефолтную оконную процедуру
		if (fCallDefault)
		{
			// делаем это
			fCallDefault = ::DefWindowProc(hwnd,msg,wp,lp);
		}
	}
	return fCallDefault;
}



//--------------------------------------------------------------------------
//
//	Обработчик события
//
//--------------------------------------------------------------------------
CButtonFrame::CButtonFrame(HINSTANCE hinst, LPCTSTR btext, CFrame * pparent)
	: CFrame(hinst, "BUTTON", BS_PUSHBUTTON|WS_CHILD, 0, btext, pparent,
			CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT)
{
	// экземпляры данного класса должны иметь предка
	if (pparent == NULL)
	{
		// тут бросаем исключение
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
	if ((ct == m_pButton1) || (ct == m_pButton2))	// нажата кнопка m_pButton
	{
		DWORD style_curr = ct->GetStyle() ^ (WS_SIZEBOX | WS_CAPTION);
		ct->SetStyle(style_curr);

//		::MessageBox(m_hWnd, "Button WS_SIZEBOX changed", "Event", MB_OK);
	}
	return FALSE;
}


} /* namespace AppFrameNameSpace */
