// dataDialog.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "dataDialog.h"
#include "afxdialogex.h"


// dataDialog dialog

IMPLEMENT_DYNAMIC(dataDialog, CDialog)

dataDialog::dataDialog(bool lecturerMode, CWnd* pParent /*=NULL*/)
	: CDialog(dataDialog::IDD, pParent)
	, name(_T(""))
	, group(_T(""))
{
	if (lecturerMode) //диалог вызван дл€ добавлени€ преподавател€ - поле √руппа не нужно, пр€чу его
	{
		groupDataEditControl.ShowWindow(SW_HIDE);
		groupLabelControl.ShowWindow(SW_HIDE);
	}
}

dataDialog::~dataDialog()
{
}

void dataDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, groupDataEdit, groupDataEditControl);
	DDX_Text(pDX, nameEdit, name);
	DDX_Text(pDX, groupDataEdit, group);
	DDX_Control(pDX, groupLabel, groupLabelControl);
}


BEGIN_MESSAGE_MAP(dataDialog, CDialog)
	ON_BN_CLICKED(sendButton, &dataDialog::sendRequested)
END_MESSAGE_MAP()


// dataDialog message handlers


void dataDialog::sendRequested()
{
	UpdateData(TRUE);
	this->EndDialog(IDOK);
}
