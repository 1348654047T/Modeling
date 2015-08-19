#include "vcontrol.h"

void VControl::Move(VVector3& move) //�ƶ�����
{
	m_mat.MoveTM(-move);
}
void VControl::Rotate(VAxisAngle& AxisAng)//��ת����
{
	m_mat.RotateTM(AxisAng);
}
void VControl::Scale(VVector3& scale)//���ž���
{
	m_mat.ScaleTM(scale);
}
VMatrix3 VControl::GetTM()//���ؾ���
{
	return m_mat;
}

void VControl::SetTM(VMatrix3& tm)//���øþ���
{
	m_mat = tm;								
}

void VControl::SetTM(VMatrix3* p_mat)//���øþ���
{
	m_mat = *p_mat;								
}

//��������
void VControl::CopyMat(VMatrix3& newMat)
{
	m_mat = newMat;
}