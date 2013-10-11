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

#include "CBaseFrame.h"

using namespace std;

namespace AppFrameNameSpace
{



class CFrame : public CBaseFrame
{
public:
	CFrame(HINSTANCE hinst,UINT cstyle,HICON hicon,HICON hiconsm,HCURSOR hcursor,HBRUSH hbr,
			LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,CBaseFrame *pparent,int,int,int,int);
	CFrame(HINSTANCE hinst,LPCTSTR clname,DWORD fstyle,DWORD fstyleex,LPCTSTR fname,CBaseFrame *pparent,
			int,int,int,int);
	CFrame(const CBaseFrame &src);

protected:
	virtual LRESULT OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp);
private:

};





class CButton : public CFrame
{
public:
	CButton(HINSTANCE hinst,CFrame *pparent,LPCTSTR btext);
	virtual LRESULT OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp);
protected:
private:
};




class CMainFrame : public CFrame
{
public:
	CMainFrame(HINSTANCE hinst,LPCTSTR title,int,int,int,int);
	virtual ~CMainFrame();
protected:
	virtual LRESULT OnFrameEvent(UINT msg, WPARAM wp, LPARAM lp);
private:
	CButton * pButtonExit, *pButtonHello, *pButtonQwer;

};



} /* namespace AppFrameNameSpace */
#endif /* CFRAME_H_ */
