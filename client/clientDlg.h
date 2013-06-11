#pragma once
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdisp.h>        // MFC Automation classes
#include <vector>

#include "resource.h"
#include "dataDialog.h"

#include "Sale.h"
#include "Purchase.h"
#include "ValueObject.h"
#include "RequestGenerator.h"
#include "projectDialog.h"
#include "ObjectsContainer.h"

#include "afxcmn.h"

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
	afx_msg void projectAddRequested();
	afx_msg void projectUpdateRequested();
	afx_msg void projectRemoveRequested();
	afx_msg void fullReportRequested();

	afx_msg void showError(WCHAR *message);
	afx_msg void displayObjects(ObjectsContainer *list);
	afx_msg void displayValue(ObjectsContainer *list);
	void displayDiagram(ObjectsContainer *list);
	void saveTextReport(ObjectsContainer *list);
private:
	CString productNameString;

	projectDialog *dialog;
	dataDialog *dataDialogPointer;
public:
	afx_msg void projectAddCompleted();
	afx_msg void lecturerAddCompleted();
	afx_msg void studentAddCompleted();
private:
	CString connectionStateEdit;
public:
	afx_msg void serverConnectRequested();
private:
	CString addressEdit;
	CString portEdit;
	CListCtrl table;

	char *bytes;
	int currentID;
	bool isSaleMode;
public:
	afx_msg void allPurchasesRequested();
	afx_msg void allSalesRequested();
	afx_msg void productPurchasesRequested();

	afx_msg void productSalesRequested();

	afx_msg void productProfitabilityRequested();
	afx_msg void allProfitabilityRequested();
};
