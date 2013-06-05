#include "client.h"
#include "projectDialog.h"
#include "afxdialogex.h"


// projectDialog dialog

IMPLEMENT_DYNAMIC(projectDialog, CDialogEx)

projectDialog::projectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(projectDialog::IDD, pParent)
	, task(_T(""))
	, subject(_T(""))
	, completeness(0)
	, student(_T(""))
	, lecturer(_T(""))
	, dueTo(_T("2012-12-01"))
	, name(_T(""))
	, group(_T(""))
{
	
}

projectDialog::~projectDialog()
{
}

void projectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, taskEdit, task);
	DDX_Text(pDX, subjectEdit, subject);
	//DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, dueTo);
	DDX_Text(pDX, IDC_EDIT4, completeness);
	DDV_MinMaxInt(pDX, completeness, 0, 100);
	DDX_Text(pDX, IDC_EDIT5, student);
	DDX_Text(pDX, IDC_EDIT6, lecturer);
	DDX_Text(pDX, dateEdit, dueTo);
}


BEGIN_MESSAGE_MAP(projectDialog, CDialog)
	ON_BN_CLICKED(sendButton, &projectDialog::sendRequested)
END_MESSAGE_MAP()


// projectDialog message handlers

void projectDialog::sendRequested()
{
	UpdateData(TRUE);
	this->EndDialog(IDOK);
}
