/**********************************************************************
DESCRIPTION: vcamera.h
����� lookat�ķ�װ��ʹ��VMatrix3���װlookat��������

CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************/
#ifndef _H_VCAMERA_H_
#define _H_VCAMERA_H_
///////////////////////////////////////////////
#include "vpoint.h"
#include "vglobaltools.h"
#include "vmatrix.h"

class VCamera{
protected:
	VMatrix3 m_Mat;//ʹ�þ��󱣳������λ�á����򡢳���
public:
	//���캯��
	VCamera()
	{
	}
	
	//�������λ��
	void Identify()
	{
		m_Mat.IdentifyTM();
	}
	//��������λ��
	VVector3 GetCameraPos()
	{
		return m_Mat.TransPoint(VVector3(0.0f,0.0f,0.0f));
	}
	//������������
	VVector3 GetCameraView()
	{
		return m_Mat.TransPoint(VVector3(0.0f,0.0f,-300.0f));
	}
	//������������
	VVector3 GetCameraDir()
	{
		VVector3 camPos = m_Mat.TransPoint(VVector3(0.0f,0.0f,0.0f));
		VVector3 camDir = m_Mat.TransPoint(VVector3(0.0f,1.0f,0.0f));
		camDir = camDir - camPos;
		return camDir;
	}
	//�ƶ��������v-�ƶ�����
	void TransferCamera(VVector3& v)					//ƽ����ͼ
	{
		m_Mat.MoveTM(v);
	}
	//��ת����� v-��ת�� angle-��ת�Ƕ�
	void RotateCamera(VVector3& v,float angle)				//��ת��ͼ
	{
		VPoint3 oldPos = GetCameraPos();						//
		VPoint3 view = GetCameraView();						//
		VVector3 oldDir = GetCameraDir();						//
		VVector3 axis = v - oldPos;
		m_Mat.MoveTM(view - oldPos);						//ƽ��
		m_Mat.RotateTM(VAxisAngle(axis,angle));		//��ת
		m_Mat.MoveTM(GetCameraPos() - GetCameraView());						//��ƽ�ƻ���
	}
	//��������� factor-��������
	void ZoomCamera(float factor)						//������ͼ
	{
		m_Mat.ScaleTM(VVector3(factor,factor,factor));
	}
	/*********************************************************************************
	  *Function:GetCamPara(VPoint3 p_start,VPoint3 p_end)  
	  *Description�����������������������ƶ����� 
	  *Input: p_start-��������㣬p_end-����ƶ��� 
	  *Return: �������������ռ���ƶ����� 
	              *CREATED BY:  [8/10/2015 niewenchao]
	**********************************************************************************/
	VVector3 GetCamMovePara(VPoint3 p_start,VPoint3 p_end)
	{
		VVector3 v;
		v = VVector3(int(p_start.x-p_end.x),int(p_end.y-p_start.y),0);
		//ת����������ռ�  
		v = m_Mat.TransPoint(v);
		v -= m_Mat.TransPoint(VVector3(0.0f,0.0f,0.0f));
		//v /= 250;
		return v;
		
	}
	VVector3 GetCamRotatePara(VPoint3 p_start,VPoint3 p_end)
	{
		float x = p_end.x-p_start.x;
		float y = p_end.y-p_start.y;
		int xSbl = 1,ySbl = 1;
		VVector3 v;
		if (y<0) ySbl = -1;
		if (x<0) xSbl = -1;
		if (x == 0)
			v.SetXYZ(-10.0*ySbl,0.0,0.0);
		else if (y == 0)
			v.SetXYZ(0.0,-10.0*xSbl,0.0);
		else
			v.SetXYZ(-10.0*ySbl,-10.0*(float)y/(float)x*ySbl,0.0);
		v = m_Mat.TransPoint(v);
		return v;

	}
	//Ӧ�������
	inline void ApplyCameraTransform(bool bRotOnly = false)    
			{
			VVector3 vPos = GetCameraPos();
			VVector3 vView = GetCameraView();
			VVector3 vUp = GetCameraDir();

			gluLookAt(vPos.x, vPos.y, vPos.z,
						vView.x, 
						vView.y, 
						vView.z , 
						vUp.x, vUp.y, vUp.z);
			
			}

};
///////////////////////////////////////////////
#endif