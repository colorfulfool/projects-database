#include "client.h"
#include "clientDlg.h"
#include <afxshellmanager.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CclientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CclientApp::CclientApp()
{
	
}

CclientApp theApp;

BOOL CclientApp::InitInstance()
{
	CWinApp::InitInstance();

	CShellManager *pShellManager = new CShellManager;

	SetRegistryKey(_T("��������� ����������, ��������� � ������� ������� ����������"));

	CclientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "��"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "������"
	}

	// ������� ��������� ��������, ��������� ����.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��������� ���������� ���� �������, ���������� �������� FALSE, ����� ����� ���� ����� ��
	//  ���������� ������ ������� ���������� ��������� ����������.
	return FALSE;
}

