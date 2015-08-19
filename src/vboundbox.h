/**********************************************************************
DESCRIPTION: ��Χ�ж��� 

CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************/
#ifndef _VBOUNDBOX_H_
#define _VBOUNDBOX_H_
//////////////////////////////////////////////////////////////////////////
#include "vpoint.h"
//////////////////////////////////////////////////////////////////////////
class VBoundBox	{													// ��Χ�еĶ���
public:
	// constructor
	VBoundBox(){}
	VBoundBox(const VPoint3& minpoint,const VPoint3& maxpoint, const VPoint3 color){
		m_Pmin = minpoint;
		m_Pmax = maxpoint;
		m_Color = color;
	}
	~VBoundBox(){}

public:
	VPoint3 m_Pmin;													// �͵�
	VPoint3 m_Pmax;													// �ߵ�
	VPoint3 m_Color;
public:	
	
	VPoint3& GetColor() {return m_Color;}
	void SetColor(VPoint3& newColor) {m_Color = newColor;}							//����Ĭ����ʾ��ɫ
	void SetColor(float x, float y, float z)	{m_Color.SetXYZ(x, y, z);}				//����Ĭ����ʾ��ɫ

	const VPoint3& Min() { return m_Pmin; }							// ���ص͵�
	const VPoint3& Max() { return m_Pmax; }							// ���ظߵ�

	void InitBoundBox(){ m_Pmin.SetXYZ(0.0,0.0,0.0); m_Pmax.SetXYZ(0.0,0.0,0.0);}	// ��ʼ����Χ��
											
	void SetBoundBox(VPoint3& p1,VPoint3& p2){	m_Pmin.SetXYZ(p1);	m_Pmax.SetXYZ(p2);}// ���ð�Χ��

	inline const VPoint3 Center(){ return (m_Pmax+m_Pmin)/(float)2.0;}	// �������ĵ�
	inline const VPoint3 Width() { return (m_Pmax - m_Pmin);}			// ���ر�ʾ����ߵĵ�
	VPoint3 operator[](int i)const{										// ���ذ�Χ�е�8���˵�
		switch (i)
		{
		case 0:return VPoint3(m_Pmin.x,m_Pmin.y,m_Pmin.z);
		case 1:return VPoint3(m_Pmax.x,m_Pmin.y,m_Pmin.z);
		case 2:return VPoint3(m_Pmin.x,m_Pmax.y,m_Pmin.z);
		case 3:return VPoint3(m_Pmax.x,m_Pmax.y,m_Pmin.z);
		case 4:return VPoint3(m_Pmin.x,m_Pmin.y,m_Pmax.z);
		case 5:return VPoint3(m_Pmax.x,m_Pmin.y,m_Pmax.z);
		case 6:return VPoint3(m_Pmin.x,m_Pmax.y,m_Pmax.z);
		case 7:return VPoint3(m_Pmax.x,m_Pmax.y,m_Pmax.z);
		}
	}
	VBoundBox& operator+=(const VPoint3& p){					//��Χ�м���һ����
		m_Pmin += p;
		m_Pmax += p;
		return (*this);
	}
	

};
//////////////////////////////////////////////////////////////////////////
#endif