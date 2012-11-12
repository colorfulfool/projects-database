
// clientDlg.cpp : ���� ����������
//

#include "client.h"
#include "clientDlg.h"
#include "afxdialogex.h"
#include "RequestGenerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CclientDlg::CclientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CclientDlg::IDD, pParent)
	, lecturerName(_T(""))
	, groupName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, lecturerEdit, lecturerName);
	DDX_Text(pDX, groupEdit, groupName);
}

BEGIN_MESSAGE_MAP(CclientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CclientDlg::lecturerProjectsRequested)
	ON_BN_CLICKED(IDC_BUTTON2, &CclientDlg::groupProjectsRequested)
	ON_BN_CLICKED(IDC_BUTTON3, &CclientDlg::allProjectsRequested)
	ON_BN_CLICKED(IDC_BUTTON4, &CclientDlg::projectAddRequested)
	ON_BN_CLICKED(IDC_BUTTON5, &CclientDlg::projectUpdateRequested)
	ON_BN_CLICKED(IDC_BUTTON6, &CclientDlg::projectRemoveRequested)
	ON_COMMAND(ID_32772, &CclientDlg::studentAddRequested)
	ON_COMMAND(ID_32773, &CclientDlg::lecturerAddRequested)
	ON_COMMAND(ID_32774, &CclientDlg::fullReportRequested)
	ON_COMMAND(ID_32775, &CclientDlg::diagramRequested)
	ON_BN_CLICKED(sendButton, &CclientDlg::projectAddCompleted)
END_MESSAGE_MAP()


// ����������� ��������� CclientDlg

BOOL CclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	mainMenu.LoadMenuW(IDR_MENU1);
	SetMenu(&mainMenu);

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void CclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CclientDlg::lecturerProjectsRequested()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->lecturerProjects(lecturerName.GetString());
}


void CclientDlg::groupProjectsRequested()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->groupProjects(groupName.GetString());
}


void CclientDlg::allProjectsRequested()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->allProjects();
}


void CclientDlg::projectAddRequested()
{
	LPCWSTR test = L"��������";
	char result[20];
	wcstombs(result, test, 20);
	WideCharToMultiByte(CP_UTF8, NULL, test, 8, result, 20, NULL, NULL); 

	dialog = new projectDialog();
	dialog->DoModal();
}


void CclientDlg::projectUpdateRequested()
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
}


void CclientDlg::projectRemoveRequested()
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
}


void CclientDlg::studentAddRequested()
{
	UpdateData(TRUE);
	// TODO: Add your command handler code here
}


void CclientDlg::lecturerAddRequested()
{
	UpdateData(TRUE);
	// TODO: Add your command handler code here
}


void CclientDlg::fullReportRequested()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->allProjects();
}


void CclientDlg::diagramRequested()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->groupProjects(groupName.GetString());
}


void CclientDlg::projectAddCompleted()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->addProject(dialog->task.GetString(), dialog->subject.GetString(), dialog->dueTo.GetString(), dialog->completeness, dialog->lecturer.GetString(), dialog->student.GetString());

	dialog->EndDialog(0);
}
