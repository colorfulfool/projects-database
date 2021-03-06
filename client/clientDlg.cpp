#include "client.h"
#include "clientDlg.h"
#include "afxdialogex.h"
#include "RequestGenerator.h"

#include "mgl2\mgl.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CclientDlg::CclientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CclientDlg::IDD, pParent)
	, connectionStateEdit(_T(""))
	, addressEdit(_T(""))
	, portEdit(_T(""))
	, productNameString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, duna, connectionStateEdit);
	DDX_Text(pDX, IDC_EDIT1, addressEdit);
	DDX_Text(pDX, productNameEdit, productNameString);
	DDX_Control(pDX, tableEdit, table);
}

BEGIN_MESSAGE_MAP(CclientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CclientDlg::lecturerProjectsRequested)
//	ON_BN_CLICKED(IDC_BUTTON3, &CclientDlg::allProjectsRequested)
	ON_BN_CLICKED(IDC_BUTTON4, &CclientDlg::projectAddRequested)
	ON_BN_CLICKED(IDC_BUTTON5, &CclientDlg::projectUpdateRequested)
	ON_BN_CLICKED(IDC_BUTTON6, &CclientDlg::projectRemoveRequested)
	ON_COMMAND(ID_32774, &CclientDlg::fullReportRequested)
	ON_BN_CLICKED(sendButton, &CclientDlg::projectAddCompleted)
	ON_BN_CLICKED(IDC_BUTTON7, &CclientDlg::serverConnectRequested)
	ON_BN_CLICKED(IDC_BUTTON8, &CclientDlg::productPurchasesRequested)
//	ON_BN_CLICKED(IDC_BUTTON9, &CclientDlg::allProfitabilityRequested)
	ON_BN_CLICKED(IDC_BUTTON10, &CclientDlg::allSalesRequested)
	ON_BN_CLICKED(IDC_BUTTON1, &CclientDlg::productSalesRequested)
	ON_BN_CLICKED(IDC_BUTTON9, &CclientDlg::productProfitabilityRequested)
	ON_BN_CLICKED(IDC_BUTTON3, &CclientDlg::allProfitabilityRequested)
	ON_BN_CLICKED(IDC_BUTTON10, &CclientDlg::allPurchasesRequested)
	ON_BN_CLICKED(IDC_BUTTON11, &CclientDlg::OnBnClickedButton11)
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
	table.InsertColumn(1, L"Наименование");
	table.SetColumnWidth(1, 150);
	table.InsertColumn(2, L"Количество");
	table.SetColumnWidth(2, 50);
	table.InsertColumn(3, L"Цена за единицу");
	table.SetColumnWidth(3, 50);

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


void CclientDlg::projectAddRequested()
{
	dialog = new projectDialog();

	currentID = 0;
	isSaleMode = 1;

	INT_PTR result = dialog->DoModal();
	if (result == IDOK) projectAddCompleted();
}


void CclientDlg::projectUpdateRequested()
{
	dialog = new projectDialog();

	currentID = _ttoi(table.GetItemText(table.GetSelectionMark(), 0)); //беру id выбранного курсового из таблицы

	dialog->name = table.GetItemText(table.GetSelectionMark(), 1);
	dialog->amount = _ttoi(table.GetItemText(table.GetSelectionMark(), 2));
	dialog->cost = _ttoi(table.GetItemText(table.GetSelectionMark(), 3));

	UpdateData(FALSE);
	
	INT_PTR result = dialog->DoModal();
	if (result == IDOK) projectAddCompleted();
}


void CclientDlg::projectRemoveRequested()
{
	UpdateData(TRUE);

	int id = _ttoi(table.GetItemText(table.GetSelectionMark(), 0));

	if (isSaleMode)
		RequestGenerator::instance()->removeSale(id);
	else
		RequestGenerator::instance()->removePurchase(id);
}


void CclientDlg::fullReportRequested()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->fullReport();
}


void CclientDlg::projectAddCompleted()
{
	if (currentID == 0) //создание проекта
	{
		if (isSaleMode)
			RequestGenerator::instance()->addSale(dialog->name.GetString(), dialog->amount, dialog->cost);
		else
			RequestGenerator::instance()->addPurchase(dialog->name.GetString(), dialog->amount, dialog->cost);
	} else { //либо изменение существующего
		if (isSaleMode)
			RequestGenerator::instance()->editSale(currentID, dialog->name.GetString(), dialog->amount, dialog->cost);
		else
			RequestGenerator::instance()->editPurchase(currentID, dialog->name.GetString(), dialog->amount, dialog->cost);
	}
}

void CclientDlg::studentAddCompleted()
{
	// RequestGenerator::instance()->addStudent(dataDialogPointer->name.GetString(), dataDialogPointer->group.GetString());
}

void CclientDlg::lecturerAddCompleted()
{
	// RequestGenerator::instance()->addLecturer(dataDialogPointer->name.GetString());
}

void CclientDlg::showError(WCHAR *message)
{
	this->MessageBox((LPCTSTR)message, L"Ошибка", MB_ICONERROR);
}

void CclientDlg::displayObjects(ObjectsContainer *list)
{
	int row=0;
	Sale *object; //те же члены у Purchase
	WCHAR numbersTemp[5];

	table.DeleteAllItems();

	while (list->next())
	{
		object = (Sale*)list->current();

		swprintf(numbersTemp, L"%d", object->id);
		int newRow = table.InsertItem(row, numbersTemp);
		if (isSaleMode)
			table.SetItemText(newRow, 1, object->related_name());
		else
			table.SetItemText(newRow, 1, object->related_name());
		swprintf(numbersTemp, L"%d", object->amount);
		table.SetItemText(newRow, 2, numbersTemp);
		swprintf(numbersTemp, L"%d", object->cost);
		table.SetItemText(newRow, 3, numbersTemp);

		row++;
	}

	UpdateData(FALSE);
}

void CclientDlg::displayValue(ObjectsContainer *list)
{
	list->next();
	ValueObject *value = (ValueObject*)list->current(); //беру единственный объект

	WCHAR messageBoxText[200];
	swprintf(messageBoxText, L"%s: %s", value->name, value->value);
	this->MessageBox(messageBoxText, value->name, MB_ICONINFORMATION);
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

void CclientDlg::saveTextReport(ObjectsContainer *list)
{
	FILE *report = fopen("report.csv", "w, ccs=UTF-8");

	fwprintf(report, L"Наименование;Количество;Цена за единицу\n");

	Sale *object;
	while (list->next())
	{
		object = (Sale*)list->current();

		fwprintf(report, L"%s;%d;%d\n", object->product_name, object->cost, object->amount);
	}

	fclose(report);

	MessageBox(L"Отчет был сохранен в файл report.csv");
}

void CclientDlg::productPurchasesRequested()
{
	isSaleMode = 0;

	UpdateData(TRUE);
	RequestGenerator::instance()->productPurchases(productNameString.GetString());
}


void CclientDlg::allSalesRequested()
{
	isSaleMode = 1;

	RequestGenerator::instance()->allSales();
}


void CclientDlg::productSalesRequested()
{
	isSaleMode = 1;

	UpdateData(TRUE);
	RequestGenerator::instance()->productSales(productNameString.GetString());
}


void CclientDlg::productProfitabilityRequested()
{
	UpdateData(TRUE);
	RequestGenerator::instance()->productProfitability(productNameString.GetString());
}

void CclientDlg::allProfitabilityRequested()
{
	RequestGenerator::instance()->allProfitability();
}


void CclientDlg::allPurchasesRequested()
{
	isSaleMode = 0;

	UpdateData(TRUE);
	RequestGenerator::instance()->allPurchases();
}


void CclientDlg::OnBnClickedButton11()
{
	allPurchasesRequested();
}
