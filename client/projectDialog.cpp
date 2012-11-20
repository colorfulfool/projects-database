#include "client.h"
#include "projectDialog.h"
#include "afxdialogex.h"


// projectDialog dialog

IMPLEMENT_DYNAMIC(projectDialog, CDialogEx)

projectDialog::projectDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(projectDialog::IDD, pParent)
	, task(_T(""))
	, subject(_T(""))
	, dueTo(_T(""))
	, completeness(0)
	, student(_T(""))
	, lecturer(_T(""))
{

}

projectDialog::~projectDialog()
{
}

void projectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, taskEdit, task);
	DDX_Text(pDX, subjectEdit, subject);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, dueTo);
	DDX_Text(pDX, IDC_EDIT4, completeness);
	DDV_MinMaxInt(pDX, completeness, 0, 100);
	DDX_Text(pDX, IDC_EDIT5, student);
	DDX_Text(pDX, IDC_EDIT6, lecturer);
}


BEGIN_MESSAGE_MAP(projectDialog, CDialogEx)
END_MESSAGE_MAP()


// projectDialog message handlers
