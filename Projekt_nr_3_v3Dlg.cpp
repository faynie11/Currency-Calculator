
// Projekt_nr_3_v3Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Projekt_nr_3_v3.h"
#include "Projekt_nr_3_v3Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <curl/curl.h>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include "afxwin.h"
#include <atlconv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using std::cout;
using std::string;
//creating map that will contain our currency values
std::map<std::string, double> Currency_Pairs{};


size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

std::map<std::string, double> Get_Currency()
{
	CURL* curl;
	CURLcode res;



	curl_global_init(CURL_GLOBAL_DEFAULT);

	// creating curl initialisation

	curl = curl_easy_init();


	//code below is executed only if condition below returns true - it means that code will be executed if curl is created

	if (curl) {

		// creating get request using header with app id ( in '' braces)

		curl_easy_setopt(curl, CURLOPT_URL, "https://openexchangerates.org/api/latest.json?app_id='6ab5475424ac4f9eb09f28769c248698'");

		// probably not necesairy code below

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // when page has no verified certificate
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

		//----------------------------------

		//creating strings containing header and response 

		std::string response_string;
		std::string header_string;

		//------------------------------------------------

		// functions used for reading data from get request response

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

		//----------------------------------------------------------


		curl_easy_perform(curl);

		//cout << header_string;

	   // cout << response_string;

		// converting json into map vector containing pairs - Currency name : Currency value (base currency is american USD)
		std::string line;

		// string stream must be created for getline function
		std::istringstream string_stream(response_string);




		//reading json line by line from our string stream
		size_t delimiter{};
		size_t end{};

		short check_data{ 0 };


		while (std::getline(string_stream, line)) {

			// continue until currency data appear - until second { appears
			if (check_data < 2) {
				if (line.find('{') != string::npos) {
					check_data++;
				}
				continue;
			}

			// deleting all white symbols
			line.erase(remove(line.begin(), line.end(), ' '), line.end());

			//searching for delimiter and end symbol
			delimiter = line.find(":");
			end = line.find(",");

			if (delimiter != string::npos && end != string::npos) {
				//cout << line.substr(1, delimiter - 2) << " " << line.substr(delimiter + 1, end - delimiter - 1) << std::endl; //-1 and +1 is because we dont want delimiters in our data , end-delimiter is because substr gets number of symbols - not position in string
				Currency_Pairs[line.substr(1, delimiter - 2)] = std::stod(line.substr(delimiter + 1, end - delimiter - 1)); //delimiter to pozycja w linii znaku oddzielajacego klucz i wartosc, a end to pozycja przecinka ktory usuwamy
																															//cala linie tak przetwarzamy, aby wyciac z niej klucz i wartosc
			}	

		}


		// testing if 

		for (auto element : Currency_Pairs) {
			cout << element.first << " " << element.second << std::endl;
		}


		//string ComboBox = "PLN";

		//cout << "test-----\n" << Currency_Pairs[ComboBox] << std::endl;

		//------------------------------------------------------------------------------------------------------------------

		curl_easy_cleanup(curl);
		curl_global_cleanup();
		curl = NULL;
	}
	res = curl_easy_perform(curl);
	return Currency_Pairs;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjektnr3v3Dlg dialog



CProjektnr3v3Dlg::CProjektnr3v3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJEKT_NR_3_V3_DIALOG, pParent)
	
	, cstring_value_from(_T(""))
	, value_currency_to(_T(""))
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjektnr3v3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, code_currency_from);
	//  DDX_Text(pDX, IDC_EDIT1, value_currency_from);
	DDX_Text(pDX, IDC_EDIT2, cstring_value_from);
	DDX_Control(pDX, IDC_COMBO1, code_currency_to);
	//DDX_Text(pDX, IDC_EDIT1, value_currency_to);
	//  DDX_Text(pDX, IDC_EDIT1, value_currency_to);
	DDX_Text(pDX, IDC_EDIT1, value_currency_to);
}

BEGIN_MESSAGE_MAP(CProjektnr3v3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProjektnr3v3Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CProjektnr3v3Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CProjektnr3v3Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CProjektnr3v3Dlg message handlers

BOOL CProjektnr3v3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProjektnr3v3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProjektnr3v3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProjektnr3v3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProjektnr3v3Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	
	CString data;
	CString finalData;
	
	int nIndex = code_currency_from.GetCurSel(); //Pobieranie danych z comboboxa nr1
	code_currency_from.GetLBText(nIndex, data);

	int finalIndex = code_currency_to.GetCurSel(); //Pobieranie danych z comboboxa nr2
	code_currency_to.GetLBText(finalIndex, finalData);


	std::map<std::string, double> RETURN_VALUE{}; //tworzenie mapy z kursami walut
	RETURN_VALUE = Get_Currency();
	
		
	double dValue = _tstof(cstring_value_from); //pobieranie wartosci z editcontrola
	
	std::string sData = CT2A(data); //konwersja na stringa z CStringa z pierwszego comboxa
	std::string fData = CT2A(finalData);

	double result = 0;
	result = dValue / RETURN_VALUE[sData];
	
	double final_result = 0;

	final_result = result * RETURN_VALUE[fData];

	std::string finalresult = std::to_string(final_result);

	size_t delimiter{};
	delimiter = finalresult.find(".");
	if (delimiter != std::string::npos) //sprawdza czy nasza szukana wartosc jest w stringu
	finalresult = finalresult.substr(0, delimiter + 3);

	value_currency_to = finalresult.c_str();

	UpdateData(FALSE);

	//Ponizej sprawdzanie widnowpopout czy kod dzia³a³ poprawnie

	/*
	CString strValue;
	strValue.Format(_T("%f"), final_result);
	
	data.Append(L", " + strValue);

	AfxMessageBox(data);
	*/
	
}


void CProjektnr3v3Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CProjektnr3v3Dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
