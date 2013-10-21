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
#include <commctrl.h>
#include <string>
#include <list>

#include "CBaseFrame.h"

using namespace std;

namespace AppFrameNameSpace
{



class CFrame : public CBaseFrame
{
public:
	CFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
			LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,int,int,int,int);
	CFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,
			int,int,int,int);
	CFrame(const CBaseFrame &src);

protected:
	virtual LRESULT OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp);
private:

};




class CControlFrame : public CBaseFrame
{
public:
	CControlFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,
			int x,int y,int cx,int cy);
protected:
	virtual LRESULT OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp);
};



class CButton : public CControlFrame
{
public:
	CButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext);
	CButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext,int x,int y,int cx,int cy);
protected:

private:
};


class CStateButton : public CControlFrame
{
public:
	CStateButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext);
	CStateButton(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR btext,int x,int y,int cx,int cy);
};


class CGroupBox : public CControlFrame
{
public:
	CGroupBox(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR gbtext);
	CGroupBox(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR gbtext,int x,int y,int cx,int cy);
};


class CTreeView : public CControlFrame
{
public:
	CTreeView(HINSTANCE hinst,CBaseFrame *pparent,LPCTSTR gbtext,int x,int y,int cx,int cy);
};




class CDialogFrame : public CBaseFrame
{
public:
	CDialogFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
			LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR ftext,CBaseFrame *pparent,int,int,int,int);
	~CDialogFrame();

	BOOL AddButton(LPCTSTR btext,int x,int y,int cx,int cy);
	BOOL AddStateButton(LPCTSTR btext,int x,int y,int cx,int cy);
	BOOL AddGroupBox(LPCTSTR gbtext,int x,int y,int cx,int cy);
	BOOL AddTreeView(LPCTSTR ttext, int x,int y,int cx,int cy);


protected:
	virtual LRESULT OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp);
	virtual void OnButtonPush(CControlFrame * pbutton);

	BOOL AddControlFrame(CControlFrame * pframe);
	void DeleteControlFrame(CControlFrame * pframe);

private:
	list< CControlFrame* > m_ChildList;
};




} /* namespace AppFrameNameSpace */
#endif /* CFRAME_H_ */
