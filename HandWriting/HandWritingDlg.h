
// HandWritingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include<string>
#include"cv.h"
#include"highgui.h"
#include "svm.h"
#include "BP.h"
#define Malloc(type,n) (type*)malloc((n)*sizeof(type))

// CHandWritingDlg �Ի���
class CHandWritingDlg : public CDialogEx
{
// ����
public:
	CHandWritingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HANDWRITING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	CString filename;
	int methodType;
	IplImage* img; 
	BpNet bp; 
	svm_model* model;
public:
	CStatic m_Picture;
	//����
	CComboBox m_Methods;
	//ѡ���
	afx_msg void OnCbnSelchangeCombo1();
	//��ȡ·��
	std::string CHandWritingDlg::getPath();
	//��ȡ����
	unsigned int* CHandWritingDlg::getFeature(CvMat* row);
	CFont * f;
};
