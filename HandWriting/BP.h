#include "stdafx.h"

#include<iostream>  
#include<cmath>  
using namespace std;  

#define  innode 128  //��������  
#define  hidenode 80//10//���������  
#define  outnode 1 //��������  
#define  trainsample 2//BPѵ��������  
class BpNet  
{  
public:  
	void train(double p[trainsample][innode ],double t[trainsample][outnode]);//Bpѵ��  
	double p[trainsample][innode];     //���������  
	double t[trainsample][outnode];    //����Ҫ�����  

	double *recognize(double *p);//Bpʶ��  

	void writetrain(); //дѵ�����Ȩֵ  
	void readtrain(); //��ѵ���õ�Ȩֵ����ʹ�Ĳ���ÿ��ȥѵ���ˣ�ֻҪ��ѵ����õ�Ȩֵ��������OK  

	BpNet();  
	virtual ~BpNet();  

public:  
	void init();  
	double w[innode][hidenode];//�������Ȩֵ  
	double w1[hidenode][outnode];//������Ȩֵ  
	double b1[hidenode];//������㷧ֵ  
	double b2[outnode];//�����㷧ֵ  

	double rate_w; //Ȩֵѧϰ�ʣ������-������)  
	double rate_w1;//Ȩֵѧϰ�� (������-�����)  
	double rate_b1;//�����㷧ֵѧϰ��  
	double rate_b2;//����㷧ֵѧϰ��  

	double e;//������  
	double error;//�����������  
	double result[outnode];// Bp���  
};  