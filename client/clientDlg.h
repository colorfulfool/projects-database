#pragma once
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdisp.h>        // MFC Automation classes

#include "RequestGenerator.h"
#include "projectDialog.h"

// диалоговое окно CclientDlg
class CclientDlg : public CDialogEx
{
// Создание
public:
	CclientDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

	CMenu mainMenu;

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void lecturerProjectsRequested();
	afx_msg void groupProjectsRequested();
	afx_msg void allProjectsRequested();
	afx_msg void projectAddRequested();
	afx_msg void projectUpdateRequested();
	afx_msg void projectRemoveRequested();
	afx_msg void studentAddRequested();
	afx_msg void lecturerAddRequested();
	afx_msg void fullReportRequested();
	afx_msg void diagramRequested();
private:
	CString lecturerName;
	CString groupName;

	projectDialog *dialog;
public:
	afx_msg void projectAddCompleted();
};
