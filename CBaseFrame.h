/*
 * CBaseFrame.h
 *
 *  Created on: 09 окт. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CBASEFRAME_H_
#define CBASEFRAME_H_

#include <windows.h>
#include <string>

using namespace std;

namespace AppFrameNameSpace
{



class CBaseFrame
{
public:
	static ATOM RegisterFrameClass(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,
			HBRUSH hbr,LPCTSTR clname);
	static BOOL UnregisterFrameClass(LPCTSTR clname, HINSTANCE hinst);
	static HWND CreateFrame(HINSTANCE hinst, DWORD style, DWORD exstyle, LPCTSTR clname, LPCTSTR fname,
				CBaseFrame *pparent,int x,int y,int cx,int cy);

	CBaseFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
			LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,CBaseFrame *pparent,int,int,int,int);
	CBaseFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,CBaseFrame *pparent,
			int,int,int,int);
	CBaseFrame(const CBaseFrame &src);

	virtual ~CBaseFrame();

	DWORD GetStyle() const;
	DWORD GetExStyle() const;

	DWORD SetStyle(DWORD);
	DWORD SetExStyle(DWORD);

	void ShowFrame();
	void UpdateFrame();
	void HideFrame();
	BOOL MoveFrame(int x,int y,int cx,int cy, BOOL repaint);
	void DestroyFrame();


protected:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	WNDPROC		m_WndProc;
	CBaseFrame	*m_Parent;
	string		m_ClassName;

	virtual LRESULT OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp) = 0;

private:
	static LRESULT CALLBACK BindWndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);


	WNDPROC BindFrame(HWND hwnd);
	void UnbindFrame();
};

} /* namespace AppFrameNameSpace */
#endif /* CBASEFRAME_H_ */
