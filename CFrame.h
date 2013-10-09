/*
 * CFrame.h
 *
 *  Created on: 02 окт. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CFRAME_H_
#define CFRAME_H_

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

namespace AppFrameNameSpace
{

class CFrame;



class CFrame
{
private:
	friend ATOM RegisterFrameClass(HINSTANCE hinst, UINT cstyle, HICON hicon, HICON hsmicon,
			HCURSOR hcurs, HBRUSH hbr, LPCTSTR clname);
	friend BOOL UnregisterFrameClass(LPCTSTR clname, HINSTANCE hinst);

	friend HWND CreateFrame(HINSTANCE hinst, DWORD style, DWORD exstyle, LPCTSTR clname, LPCTSTR fname,
			CFrame *pparent, int x,int y,int cx,int cy);

	WNDPROC BindFrame(HWND hwnd);
	void UnbindFrame();

	static LRESULT CALLBACK BindWndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);

protected:
	HWND m_hWnd;
	WNDPROC m_WndProc;

	HINSTANCE m_hInst;
	string m_ClassName;

	virtual BOOL OnFrameDestroy();
	virtual BOOL OnFrameClose();
	virtual BOOL OnFrameRepaint();
	virtual BOOL OnControlEvent(CFrame * ct, DWORD evcode);


public:
	CFrame(HINSTANCE hinst, UINT cstyle, HICON hicon, HICON hiconsm, HCURSOR hcursor, HBRUSH hbr, LPCTSTR clname,
			DWORD fstyle, DWORD fstyleex, LPCTSTR fname, CFrame *pparent, int, int, int,int);
	CFrame(HINSTANCE hinst, LPCTSTR clname, DWORD fstyle, DWORD fstyleex, LPCTSTR fname, CFrame *pparent,
			int, int, int, int);
	virtual ~CFrame();

	DWORD GetStyle() const;
	DWORD GetExStyle() const;

	DWORD SetStyle(DWORD);
	DWORD SetExStyle(DWORD);

	void ShowFrame();
	void HideFrame();
	BOOL MoveFrame(int x,int y,int cx,int cy, BOOL repaint);
	void DestroyFrame() { ::DestroyWindow(m_hWnd); };
};





class CButtonFrame : public CFrame
{
private:

public:
	CButtonFrame(HINSTANCE hinst, LPCTSTR btext, CFrame * pparent);

};




class CTestFrame : public CFrame
{
private:
	CFrame *m_pButton1, *m_pButton2;

protected:
	virtual BOOL OnFrameDestroy();
	virtual BOOL OnControlEvent(CFrame * ct, DWORD evcode);

public:
	CTestFrame(HINSTANCE hinst,LPCTSTR fname);
	virtual ~CTestFrame();
};



} /* namespace AppFrameNameSpace */
#endif /* CFRAME_H_ */
