#include "client.h"
#include "projectDialog.h"
#include "afxdialogex.h"


// projectDialog dialog

IMPLEMENT_DYNAMIC(projectDialog, CDialogEx)

projectDialog::projectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(projectDialog::IDD, pParent)
	, name(_T(""))
	, cost(0)
	, amount(0)
{
	
}

projectDialog::~projectDialog()
{
}

void projectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, nameEdit, name);
	DDX_Text(pDX, amountEdit, amount);
	DDX_Text(pDX, costEdit, cost);
	//DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, dueTo);
	// DDX_Text(pDX, IDC_EDIT4, completeness);
	// DDV_MinMaxInt(pDX, amount, 0, 100);
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
