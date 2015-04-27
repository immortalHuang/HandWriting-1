
// HandWritingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HandWriting.h"
#include "HandWritingDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHandWritingDlg �Ի���



CHandWritingDlg::CHandWritingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHandWritingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHandWritingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Loadimage, m_Picture);
	DDX_Control(pDX, IDC_COMBO1, m_Methods);
}

BEGIN_MESSAGE_MAP(CHandWritingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHandWritingDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CHandWritingDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHandWritingDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CHandWritingDlg ��Ϣ�������

BOOL CHandWritingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	f = new CFont;
	f->CreateFont(150,            // nHeight 
		64,           // nWidth 
		0,           // nEscapement 
		0,           // nOrientation 
		FW_NORMAL,     // nWeight 
		FALSE,        // bItalic 
		FALSE,       // bUnderline 
		0,           // cStrikeOut 
		ANSI_CHARSET,              // nCharSet 
		OUT_DEFAULT_PRECIS,        // nOutPrecision 
		CLIP_DEFAULT_PRECIS,       // nClipPrecision 
		DEFAULT_QUALITY,           // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("����"));              // lpszFac

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	model = svm_load_model("model.txt");//��һ����/����ʾת���ַ���������������/��
	m_Methods.AddString(L"SVM");//���һ��ѡ��
	m_Methods.AddString(L"BP");//2
	m_Methods.SetCurSel(1);
	methodType = 1;
	bp.readtrain();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHandWritingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHandWritingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHandWritingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHandWritingDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog opendlg(TRUE, _T("*"), _T("*.bmp"), OFN_OVERWRITEPROMPT, _T("�����ļ�(*.*;)|*.*||"), NULL);
	if (opendlg.DoModal() == IDOK)
	{
		filename = opendlg.GetPathName();
	}
	HANDLE hHandle = ::LoadImageW(NULL, filename, IMAGE_BITMAP, 128, 128, LR_LOADFROMFILE);
	m_Picture.SetBitmap((HBITMAP)MAKEINTRESOURCE(hHandle));
}




void CHandWritingDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	if (index == 0)
		methodType = 2;

	if (index == 1)
		methodType = 1;
}
//��ȡ·��
std::string CHandWritingDlg::getPath()
{

	std::string tmp = CT2A(filename.GetBuffer());
	std::string path;
	std::string::size_type idx;
	while (1)
	{
		idx = tmp.find("\\");
		if (idx == std::string::npos)
		{
			path += tmp;
			break;
		}
		path += tmp.substr(0, idx) + "\\" + "\\";
		tmp = tmp.substr(idx + 1);
	}
	return path;
}
//��ȡͼ������
unsigned int* CHandWritingDlg::getFeature(CvMat* row)
{
	unsigned int fea[128] = { 0 };
	int i, j;
	float* ptr = (float*)row->data.ptr;
	for (i = 0; i<128; i++)
	{
		for (j = 0; j<32; j++)
		{
			if (*(ptr++))
				fea[i]|=(1<<j);
		}              
	}
	return fea;
}

void CHandWritingDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char ch[4];
	memset(ch, 0, 4);

	//BPʶ����
	double Y[trainsample][outnode] = {
		{ 0.0000 }, { 1.0000 }
	};

	////SVM
	if (methodType == 1)
	{
		img = cvLoadImage(getPath().data(), 0);
		CvMat* imgMat = cvCreateMat(img->height, img->width, CV_32FC1);//����һ��ָ��CvMat�����ָ��
		cvConvert(img, imgMat);

		//����������һ��
		CvMat row_header, *row;
		row = cvReshape(imgMat, &row_header, 0, 1);
		struct svm_node *node = Malloc(svm_node, 129);
		unsigned int* fea = getFeature(row);
		for (int i = 0; i<128; i++)
		{
			node[i].index = i + 1;
			node[i].value = fea[i];
		}
		node[128].index = -1;//-1��ʾ����
		double result = svm_predict(model, node);
		free(node);
		if (result == 1)
			ch[0] = 'A';
		if (result == 2)
			ch[0] = 'B';

	}

	////BP
	if (methodType == 2)
	{
		img = cvLoadImage(getPath().data(), 0);
		CvMat* imgMat = cvCreateMat(img->height, img->width, CV_32FC1);//����һ��ָ��CvMat�����ָ��
		cvConvert(img, imgMat);

		//����������һ��
		CvMat row_header, *row;
		row = cvReshape(imgMat, &row_header, 0, 1);
		unsigned int* fea = getFeature(row);

		double m[innode] = { 0 };
		for (int i = 0; i<128; i++)
			m[i] = fea[i] * 1.0 / 4294967296;

		double *r = bp.recognize(m);
		double cha[trainsample][outnode];
		double mi = 100;
		double index;
		for (int i = 0; i<trainsample; i++)
		{
			for (int j = 0; j<outnode; j++)
			{
				//�Ҳ�ֵ��С���Ǹ�����  
				cha[i][j] = (double)(abs(Y[i][j] - bp.result[j]));
				if (cha[i][j]<mi)
				{
					mi = cha[i][j];
					index = i;
				}
			}
		}
		if (index == 0)
			ch[0] = 'A';
		if (index == 1)
			ch[0] = 'B';

	}
	GetDlgItem(IDC_EDIT1)->SetFont(f);
	SetDlgItemText(IDC_EDIT1, LPCTSTR(ch));
}
