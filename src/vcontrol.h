#ifndef _VCONTROL_H_
#define _VCONTROL_H_
/**********************************************************************
DESCRIPTION: ����������� ����VNode����ͼ�任 

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
#include "vmatrix.h"
#include "vpoint.h"
#include <vector>

using namespace std;

class VControl
{
public:
	VControl(){}
	~VControl(){}
private:
	VMatrix3 m_mat;		//�洢��̬����
public:
	void Move(VVector3& move);//�ƶ�
	void Rotate(VAxisAngle& AxisAng);//��ת
	void Scale(VVector3& scale);//����
	void SetTM(VMatrix3& tm);  //���þ���
	void SetTM(VMatrix3* tm);  //���þ���
	VMatrix3 GetTM();//��ȡ����
	void CopyMat(VMatrix3& newMat);	//��������
};
#endif