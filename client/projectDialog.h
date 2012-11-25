#pragma once
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdisp.h>        // MFC Automation classes
#include <afxcmn.h>
#include <afxdialogex.h>

class projectDialog : public CDialog
{
	DECLARE_DYNAMIC(projectDialog)

public:
	projectDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~projectDialog();

// Dialog Data
	enum { IDD = projectForm };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString task;
	CString subject;
	int completeness;
	CString student;
	CString lecturer;
	CString dueTo;
	CString name;
	CString group;


	afx_msg void sendRequested();
};
