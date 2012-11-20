
// clientDlg.cpp : файл реализации
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
	, connectionStateEdit(_T(""))
	, addressEdit(_T(""))
	, portEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, lecturerEdit, lecturerName);
	DDX_Text(pDX, groupEdit, groupName);
	DDX_Text(pDX, duna, connectionStateEdit);
	DDX_Text(pDX, IDC_EDIT1, addressEdit);
	DDX_Control(pDX, tableEdit, table);
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
	ON_BN_CLICKED(IDC_BUTTON7, &CclientDlg::serverConnectRequested)
END_MESSAGE_MAP()


// обработчики сообщений CclientDlg

BOOL CclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//addressEdit.SetString(L"127.0.0.1");

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	//SetIcon(m_hIcon, TRUE);			// Крупный значок
	//SetIcon(m_hIcon, FALSE);		// Мелкий значок

	mainMenu.LoadMenuW(IDR_MENU1);
	SetMenu(&mainMenu);

	connectionStateEdit.SetString(L"На данный момент: нет подключения");
	addressEdit.SetString(L"127.0.0.1");

	table.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	table.InsertColumn(0, L"id");
	table.InsertColumn(1, L"Задание");
	table.SetColumnWidth(1, 150);
	table.InsertColumn(2, L"Предмет");
	table.SetColumnWidth(2, 100);
	table.InsertColumn(3, L"Готовность, %");
	table.SetColumnWidth(3, 30);
	table.InsertColumn(4, L"Срок сдачи");
	table.SetColumnWidth(4, 70);
	table.InsertColumn(5, L"Преподаватель");
	table.SetColumnWidth(5, 100);
	table.InsertColumn(6, L"Студент");
	table.SetColumnWidth(6, 100);

	UpdateData(FALSE);
	
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
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

	int id = _ttoi(table.GetItemText(table.GetSelectionMark(), 0));

	RequestGenerator::instance()->removeProject(id);
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
	RequestGenerator::instance()->fullReport();
}


void CclientDlg::diagramRequested()
{
	UpdateData(TRUE);

	if (groupName.IsEmpty()) this->MessageBox(L"Укажите группу, по данным которой нужно строить диаграмму, в соответствующем поле.");

	RequestGenerator::instance()->diagram(groupName.GetString());
}


void CclientDlg::projectAddCompleted()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->addProject(dialog->task.GetString(), dialog->subject.GetString(), dialog->dueTo.GetString(), dialog->completeness, dialog->lecturer.GetString(), dialog->student.GetString());

	dialog->EndDialog(0);
}

void CclientDlg::showError(WCHAR *message)
{
	this->MessageBox((LPCTSTR)message, L"Ошибка", MB_ICONERROR);
}

void CclientDlg::displayProjects(ObjectsContainer *list)
{
	int row=0;
	Project *object;
	WCHAR numbersTemp[5];

	table.DeleteAllItems();

	while (list->next())
	{
		object = (Project*)list->current();

		swprintf(numbersTemp, L"%d", object->id);
		int newRow = table.InsertItem(row, numbersTemp);
		table.SetItemText(newRow, 1, object->task);
		table.SetItemText(newRow, 2, object->subject);
		swprintf(numbersTemp, L"%d", object->completeness);
		table.SetItemText(newRow, 3, numbersTemp);
		table.SetItemText(newRow, 4, object->dueTo);
		table.SetItemText(newRow, 5, object->lecturer);
		table.SetItemText(newRow, 6, object->student);

		row++;
	}

	UpdateData(FALSE);
}


void CclientDlg::serverConnectRequested()
{
	char addressDecoded[50];

	UpdateData(TRUE);
	wcstombs(addressDecoded, addressEdit.GetString(), 50);
	//wcstombs(portDecoded, portEdit.GetString(), 6);
	
	if (RequestGenerator::instance()->connectToServer(addressDecoded, 1234) == 0)
	{
		connectionStateEdit.SetString(L"На данный момент: подключен");
		UpdateData(FALSE);
	}
}

void CclientDlg::displayDiagram(ObjectsContainer *list)
{

}

void CclientDlg::saveTextReport(ObjectsContainer *list)
{
	FILE *report = fopen("report.csv", "w, ccs=UTF-8");

	fwprintf(report, L"Задание\tПредмет\tСрок сдачи\tГотовность\tПреподаватель\tСтудент\n");

	Project *object;
	while (list->next())
	{
		object = (Project*)list->current();

		fwprintf(report, L"%s\t%s\t%s\t%d\t%s\t%s\n", object->task, object->subject, object->dueTo, object->completeness, object->lecturer, object->student);
	}

	fclose(report);

	MessageBox(L"Отчет был сохранен в файл report.csv");
}