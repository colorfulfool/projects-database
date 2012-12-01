#pragma once
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdisp.h>        // MFC Automation classes
#include <vector>

#include "resource.h"
#include "dataDialog.h"

#include "Project.h"
#include "Student.h"
#include "RequestGenerator.h"
#include "projectDialog.h"
#include "ObjectsContainer.h"

#include "afxcmn.h"

// ���������� ���� CclientDlg
class CclientDlg : public CDialogEx
{
// ��������
public:
	CclientDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV

	CMenu mainMenu;

// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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

	afx_msg void showError(WCHAR *message);
	afx_msg void displayProjects(ObjectsContainer *list);
	void displayDiagram(ObjectsContainer *list);
	void saveTextReport(ObjectsContainer *list);
private:
	CString lecturerName;
	CString groupName;

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
};
