#pragma once

#include <afxwin.h>

class dataDialog : public CDialog
{
	DECLARE_DYNAMIC(dataDialog)

public:
	dataDialog(bool lecturerMode=FALSE, CWnd* pParent = NULL);   // standard constructor
	virtual ~dataDialog();

// Dialog Data
	enum { IDD = dataDialogForm };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit groupDataEditControl;
	CString name;
	CString group;
	CStatic groupLabelControl;
	afx_msg void sendRequested();
};
