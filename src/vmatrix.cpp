#include "vmatrix.h"

//////////////////////////////////////
//������	VMatrix3()				//
//���ܣ�	Ĭ�Ϲ��캯����Ϊ��λ��	//
//������	��						//
//����ֵ��	��						//
//			by xcc	2013.12.5	//
//////////////////////////////////////
VMatrix3::VMatrix3()
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = 0.0f;
	}
	m_fMat[0] = m_fMat[5] = m_fMat[10] = 1.0f;
}

//////////////////////////////////////////////////
//������	VMatrix3(const VMatrix3& mat2)	//
//���ܣ�	�������캯��						//
//������	mat2-ΪԴ����						//
//����ֵ��	��									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
VMatrix3::VMatrix3(const VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat2.m_fMat[i];
	}
}

//////////////////////////////////////////
//������	VMatrix3(float fVal)		//
//���ܣ�	����һ���Խ���ΪfVal�ľ���	//
//������	fVal-�Խ���ֵ				//
//����ֵ��	��							//
//				by xcc	2013.12.5	//
//////////////////////////////////////////
VMatrix3::VMatrix3(float fVal)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = 0.0f;
	}
	m_fMat[0] = m_fMat[5] = m_fMat[10] = fVal;
}

//////////////////////////////
//������	~VMatrix3()	//
//���ܣ�	��������		//
//������	��				//
//����ֵ��	��				//
//	by xcc	2013.12.5	//
//////////////////////////////
VMatrix3::~VMatrix3()
{
	//
}

//////////////////////////////////////////////
//������	SetValue(float* pMat)			//
//���ܣ�	���þ������е�Ԫ��ֵ			//
//������	pMat-�������þ�������Ԫ�ص�����	//
//			���ȱ���Ϊ12					//
//����ֵ��	��								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetValue(float* pMat)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = pMat[i];
	}
}

//////////////////////////////////////////////
//������	SetValue(VMatrix3& mat2)		//
//���ܣ�	����Դ�������õ�ǰ�����ֵ		//
//������	mat2-Դ����						//
//����ֵ��	��								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetValue(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat2.m_fMat[i];
	}
}

//////////////////////////////////////////////////
//������	GetRowValue(int iRow, float* pRow)	//
//���ܣ�	���þ���ָ���е�Ԫ��ֵ				//
//������	iRow-��������pRow-�������ø��е�	//
//			Ԫ��ֵ�����飬���ȱ���Ϊ4			//
//����ֵ��	��									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::SetRowValue(int iRow, float* pRow)
{
	for (int i = 0; i < 4; i++)
	{
		m_fMat[4 * iRow + i] = pRow[i];
	}
}

//////////////////////////////////////////////////
//������	SetColValue(int iCol, float* pCol)	//
//���ܣ�	���þ���ָ���е�Ԫ��ֵ				//
//������	iCol-��������pCol-�������ø��е�	//
//			Ԫ��ֵ�����飬���ȱ���Ϊ3			//
//����ֵ��	��									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::SetColValue(int iCol, float* pCol)
{
	for (int i = 0; i < 3; i++)
	{
		m_fMat[i * 4 + iCol] = pCol[i];
	}
}

//////////////////////////////////////////////////////
//������	SetValue(int i, int j, float fValue)	//
//���ܣ�	���þ���ָ��λ�õ�Ԫ��ֵ				//
//������	i,j-�ֱ��־���е�������fValue-����ֵ	//
//����ֵ��	��										//
//							by xcc	2013.12.5	//
//////////////////////////////////////////////////////
void VMatrix3::SetValue(int i, int j, float fValue)
{
	m_fMat[4 * i + j] = fValue;
}

//////////////////////////////////////////////
//������	GetAllValue(float* pMat)		//
//���ܣ�	���ؾ������е�Ԫ��ֵ			//
//������	pMat-���Դ洢��������Ԫ�ص�����	//
//			���ȱ���Ϊ12					//
//����ֵ��	��								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::GetAllValue(float* pMat)
{
	for (int i = 0; i < 12; i++)
	{
		pMat[i] = m_fMat[i];
	}
}

//////////////////////////////////////////////////
//������	GetRowValue(int iRow, float* pRow)	//
//���ܣ�	���ؾ���ָ���е�Ԫ��ֵ				//
//������	iRow-��������pRow-���Դ洢���е�	//
//			Ԫ��ֵ�����飬���ȱ���Ϊ4			//
//����ֵ��	��									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::GetRowValue(int iRow, float* pRow)
{
	for (int i = 0; i < 4; i++)
	{
		pRow[i] = m_fMat[4 * iRow + i];
	}
}

//////////////////////////////////////////////////
//������	GetColValue(int iCol, float* pCol)	//
//���ܣ�	���ؾ���ָ���е�Ԫ��ֵ				//
//������	iCol-��������pCol-���Դ洢���е�	//
//			Ԫ��ֵ�����飬���ȱ���Ϊ3			//
//����ֵ��	��									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::GetColValue(int iCol, float* pCol)
{
	for (int i = 0; i < 3; i++)
	{
		pCol[i] = m_fMat[i * 4 + iCol];
	}
}

//////////////////////////////////////////////
//������	GetValue(int i, int j)			//
//���ܣ�	���ؾ���ָ��λ�õ�Ԫ��ֵ		//
//������	i,j-�ֱ��־���е�����			//
//����ֵ��	ָ��λ�õ�Ԫ��ֵ				//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
float VMatrix3::GetValue(int i, int j)
{
	return m_fMat[4 * i + j];
}

//////////////////////////////////////////////
//������	GetMatDet()						//
//���ܣ�	���ظþ��������ʽֵ			//
//������	��								//
//����ֵ��	��								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
float VMatrix3::GetMatDet()
{
	return(m_fMat[0]*m_fMat[5]*m_fMat[10] + m_fMat[1]*m_fMat[6]*m_fMat[8] + m_fMat[2]*m_fMat[4]*m_fMat[9]
	- m_fMat[0]*m_fMat[6]*m_fMat[9] - m_fMat[1]*m_fMat[4]*m_fMat[10] - m_fMat[2]*m_fMat[5]*m_fMat[8]);
}

//////////////////////////////////////////////
//������	GetInverseMat(VMatrix3& mat)	//
//���ܣ�	��ȡ�ı任����������			//
//������	mat-���Դ洢�����ֵ			//
//����ֵ��	����������򷵻�true������false.//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
bool VMatrix3::GetInverseMat(VMatrix3& mat)
{
	float fDet = GetMatDet();
	if(fDet == 0.0)	return false;
	mat.m_fMat[0] = (m_fMat[5] * m_fMat[10] - m_fMat[9] * m_fMat[6]) / fDet;
	mat.m_fMat[1] = -(m_fMat[1] * m_fMat[10] - m_fMat[9] * m_fMat[2]) / fDet;
	mat.m_fMat[2] = (m_fMat[1] * m_fMat[6] - m_fMat[5] * m_fMat[2]) / fDet;
	mat.m_fMat[3] = -(m_fMat[1] * m_fMat[6] * m_fMat[11] - m_fMat[1] * m_fMat[7] * m_fMat[10]
		- m_fMat[5] * m_fMat[2] * m_fMat[11] + m_fMat[5] * m_fMat[3] * m_fMat[10]
		+ m_fMat[9] * m_fMat[2] * m_fMat[7] - m_fMat[9] * m_fMat[3] * m_fMat[6]) / fDet;
	mat.m_fMat[4] = -(m_fMat[4] * m_fMat[10] - m_fMat[8] * m_fMat[6]) / fDet;
	mat.m_fMat[5] = (m_fMat[0] * m_fMat[10] - m_fMat[8] * m_fMat[2]) / fDet;
	mat.m_fMat[6] = -(m_fMat[0] * m_fMat[6] - m_fMat[4] * m_fMat[2]) / fDet;
	mat.m_fMat[7] = (m_fMat[0] * m_fMat[6] * m_fMat[11] - m_fMat[0] * m_fMat[7] * m_fMat[10]
		- m_fMat[4] * m_fMat[2] * m_fMat[11] + m_fMat[4] * m_fMat[3] * m_fMat[10]
		+ m_fMat[8] * m_fMat[2] * m_fMat[7] - m_fMat[8] * m_fMat[3] * m_fMat[6]) / fDet;
	mat.m_fMat[8] = (m_fMat[4] * m_fMat[9] - m_fMat[8] * m_fMat[5]) / fDet;
	mat.m_fMat[9] = -(m_fMat[0] * m_fMat[9] - m_fMat[8] * m_fMat[1]) / fDet;
	mat.m_fMat[10] = (m_fMat[0] * m_fMat[5] - m_fMat[4] * m_fMat[1]) / fDet;
	mat.m_fMat[11] = (-m_fMat[0] * m_fMat[5] * m_fMat[11] + m_fMat[0] * m_fMat[7] * m_fMat[9]
		+ m_fMat[4] * m_fMat[1] * m_fMat[11] - m_fMat[4] * m_fMat[3] * m_fMat[9]
		- m_fMat[8] * m_fMat[1] * m_fMat[7] + m_fMat[8] * m_fMat[3] * m_fMat[5]) / fDet;
	return true;
}

//////////////////////////////////////////////////
//������	GetTransPoseMat(float* pMat)		//
//���ܣ�	��ȡ�����ת�þ���Ԫ��ֵ			//
//������	pMat-���Դ洢�þ���ת�þ���Ԫ��ֵ��	//
//			���飬���ȱ���Ϊ16					//
//����ֵ��	��									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::GetTransPoseMat(float* pMat) const
{
	pMat[0] = m_fMat[0];
	pMat[1] = m_fMat[4];
	pMat[2] = m_fMat[8];
	pMat[3] = 0.0f;
	pMat[4] = m_fMat[1];
	pMat[5] = m_fMat[5];
	pMat[6] = m_fMat[9];
	pMat[7] = 0.0f;
	pMat[8] = m_fMat[2];
	pMat[9] = m_fMat[6];
	pMat[10] = m_fMat[10];
	pMat[11] = 0.0f;
	pMat[12] = m_fMat[3];
	pMat[13] = m_fMat[7];
	pMat[14] = m_fMat[11];
	pMat[15] = 1.0f;
}
void VMatrix3::GetTransMat(VMatrix3& tMat)								//�õ��þ����ƽ�ƾ���
{
	tMat.IdentifyTM();
	tMat.m_fMat[3]=m_fMat[3]; //Ϊƽ�ƾ���ֵ
	tMat.m_fMat[7]=m_fMat[7];
	tMat.m_fMat[11]=m_fMat[11];
}

void VMatrix3::GetRotateMat(VMatrix3& rMat)								//�õ��þ������ת����
{
	rMat.IdentifyTM();
	VMatrix3 sMat;
	GetScaleMat(sMat);
	for(int j=0;j<11;j++)
	{
		if(j==0 || j==4 || j==8)
			rMat.m_fMat[j]=m_fMat[j]/sMat.m_fMat[0];
		else if(j==1 || j==5 ||j==9)
			rMat.m_fMat[j]=m_fMat[j]/sMat.m_fMat[5];
		else if(j==2 || j==6 ||j==10)
			rMat.m_fMat[j]=m_fMat[j]/sMat.m_fMat[10];
	}
}

void VMatrix3::GetScaleMat(VMatrix3& sMat)								//�õ��þ�������ž���
{
	sMat.IdentifyTM();
	sMat.m_fMat[0]=sqrt(m_fMat[0]*m_fMat[0]+m_fMat[4]*m_fMat[4]+m_fMat[8]*m_fMat[8]);
	sMat.m_fMat[5]=sqrt(m_fMat[1]*m_fMat[1]+m_fMat[5]*m_fMat[5]+m_fMat[9]*m_fMat[9]);
	sMat.m_fMat[10]=sqrt(m_fMat[2]*m_fMat[2]+m_fMat[6]*m_fMat[6]+m_fMat[10]*m_fMat[10]);
}

void VMatrix3::GetTRSMat(VMatrix3& tMat,VMatrix3& rMat,VMatrix3& sMat)								//�õ��þ������ת����ƽ�ƾ���
{
	tMat.IdentifyTM();
	tMat.m_fMat[3]=m_fMat[3]; //Ϊƽ�ƾ���ֵ
	tMat.m_fMat[7]=m_fMat[7];
	tMat.m_fMat[11]=m_fMat[11];

	sMat.IdentifyTM();
	sMat.m_fMat[0]=sqrt(m_fMat[0]*m_fMat[0]+m_fMat[4]*m_fMat[4]+m_fMat[8]*m_fMat[8]);
	sMat.m_fMat[5]=sqrt(m_fMat[1]*m_fMat[1]+m_fMat[5]*m_fMat[5]+m_fMat[9]*m_fMat[9]);
	sMat.m_fMat[10]=sqrt(m_fMat[2]*m_fMat[2]+m_fMat[6]*m_fMat[6]+m_fMat[10]*m_fMat[10]);

	rMat.IdentifyTM();
	for(int j=0;j<11;j++)
	{
		if(j==0 || j==4 || j==8)
			rMat.m_fMat[j]=m_fMat[j]/rMat.m_fMat[0];
		else if(j==1 || j==5 ||j==9)
			rMat.m_fMat[j]=m_fMat[j]/rMat.m_fMat[5];
		else if(j==2 || j==6 ||j==10)
			rMat.m_fMat[j]=m_fMat[j]/rMat.m_fMat[10];
	}
}
//////////////////////////////////////
//������	IdentifyTM()			//
//���ܣ�	���þ�������Ϊ��λ��	//
//������	��						//
//����ֵ��	��						//
//			by xcc	2013.12.5	//
//////////////////////////////////////
void VMatrix3::IdentifyTM()
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = 0.0f;
	}
	m_fMat[0] = m_fMat[5] = m_fMat[10] = 1.0f;
}

//////////////////////////////////////
//������	InverseTM()				//
//���ܣ�	���þ�������Ϊ�������	//
//������	��						//
//����ֵ��	��						//
//			by xcc	2013.12.5	//
//////////////////////////////////////
void VMatrix3::InverseTM()
{
	VMatrix3 tm1;
	GetInverseMat(tm1);
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = tm1.m_fMat[i];
	}
}

//////////////////////////////////////
//������	TransPoint(VPoint3& p1)	//
//���ܣ�	�Ե���пռ�任		//
//������	p1-ԭ�ռ������			//
//����ֵ��	�任��Ŀռ������		//
//			by xcc	2013.12.5	//
//////////////////////////////////////
VPoint3 VMatrix3::TransPoint(VPoint3& p1)
{
	VPoint3 p2;
	p2.x = m_fMat[0]*p1.x + m_fMat[1]*p1.y + m_fMat[2]*p1.z + m_fMat[3];
	p2.y = m_fMat[4]*p1.x + m_fMat[5]*p1.y + m_fMat[6]*p1.z + m_fMat[7];
	p2.z = m_fMat[8]*p1.x + m_fMat[9]*p1.y + m_fMat[10]*p1.z + m_fMat[11];
	return p2;
}

//////////////////////////////////////////////
//������	SetTMForMove(VVector3& vMove)	//
//���ܣ�	���øþ���Ϊָ��ƽ�ƾ���		//
//������	vMove-ƽ������					//
//����ֵ��	��								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetTMForMove(VVector3& vMove)
{
	IdentifyTM();
	m_fMat[3] = vMove.x;
	m_fMat[7] = vMove.y;
	m_fMat[11] = vMove.z;
}

/*********************************************************************************
  *Function:  SetTMForRotate(VAxisAngle& AxisAng)
  *Description�� ͨ����ת������ת�ǵõ�����ת����
  *Input:  VAxisAngleָ����ת�ᡢ��ת��
  *Output: ��
  *Return: �� 
  *CREATED BY:  [7/29/2015 niewenchao]
**********************************************************************************/
void VMatrix3::SetTMForRotate(VAxisAngle& AxisAng)
{
	/*
	IdentifyTM();
	DPoint3 axis;
	float fAngle, fSA, fCA, fX, fY, fZ;
	AxisAng.GetAxisAngle(axis, fAngle);
	fSA = sin(fAngle);
	fCA = cos(fAngle);
	fX = axis.x;
	fY = axis.y;
	fZ = axis.z;
	m_fMat[0] = fCA + (1 - fCA) * fX * fX;
	m_fMat[1] = (1 - fCA) * fX * fY - fSA * fZ;
	m_fMat[2] = (1 - fCA) * fX * fZ + fSA * fY;
	m_fMat[4] = (1 - fCA) * fX * fY + fSA * fZ;
	m_fMat[5] = fCA + (1 - fCA) * fY * fY;
	m_fMat[6] = (1 - fCA) * fY * fZ - fSA * fX;
	m_fMat[8] = (1 - fCA) * fX * fZ - fSA * fY;
	m_fMat[9] = (1 - fCA) * fY * fZ + fSA * fX;
	m_fMat[10] = fCA + (1 - fCA) * fZ * fZ;
	}


*/
	IdentifyTM();
	VPoint3 axis;
	float fAngle, fSA, fCA, fX, fY, fZ;
	AxisAng.GetAxisAngle(axis, fAngle);
	fSA = sin(fAngle);//����ֵΪ����
	fCA = cos(fAngle);
	fX = axis.x;
	fY = axis.y;
	fZ = axis.z;
	m_fMat[0] = fCA + (1 - fCA) * fX * fX;
	m_fMat[1] = (1 - fCA) * fX * fY - fSA * fZ;
	m_fMat[2] = (1 - fCA) * fX * fZ + fSA * fY;
	m_fMat[4] = (1 - fCA) * fX * fY + fSA * fZ;
	m_fMat[5] = fCA + (1 - fCA) * fY * fY;
	m_fMat[6] = (1 - fCA) * fY * fZ - fSA * fX;
	m_fMat[8] = (1 - fCA) * fX * fZ - fSA * fY;
	m_fMat[9] = (1 - fCA) * fY * fZ + fSA * fX;
	m_fMat[10] = fCA + (1 - fCA) * fZ * fZ;
	/*m_fMat[0] = fX * fX + (1 - fX * fX) * fCA;
	m_fMat[1] = (1 - fCA) * fX * fY + fSA * fZ;
	m_fMat[2] = (1 - fCA) * fX * fZ - fSA * fY;
	m_fMat[4] = (1 - fCA) * fX * fY - fSA * fZ;
	m_fMat[5] = fY * fY + (1 - fY * fY) * fCA;
	m_fMat[6] = (1 - fCA) * fY * fZ + fSA * fX;
	m_fMat[8] = (1 - fCA) * fX * fZ + fSA * fY;
	m_fMat[9] = (1 - fCA) * fY * fZ - fSA * fX;
	m_fMat[10] = fZ * fZ + (1 - fZ * fZ) * fCA;*/

}

//////////////////////////////////////////////
//������	SetTMForScale(VVector3& vScale)	//
//���ܣ�	���øþ���Ϊָ�����ž���		//
//������	vScale-������					//
//����ֵ��	��								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetTMForScale(VVector3& vScale)
{
	IdentifyTM();
	m_fMat[0] = vScale.x;
	m_fMat[5] = vScale.y;
	m_fMat[10] = vScale.z;
}

//////////////////////////////////////////////
//������	MoveTM(VVector3& vec)			//
//���ܣ�	�ڱ任����Ļ����ϵ���ƽ��		//
//������	vec-����ƽ�Ƶ���				//
//����ֵ��	��								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::MoveTM(VVector3& vec)
{
	m_fMat[3] += vec.x;
	m_fMat[7] += vec.y;
	m_fMat[11] += vec.z;
}

//////////////////////////////////////////////////////////////////
//������	Rotate(VMatrix3& tmAxis, VAxisAngle& vAxisAng)		//
//���ܣ�	�ڸñ任�����ϵ�����ת�任							//
//������	tmAxis-ָ����ת����ϵ��vAxisAng-��ת����ת��		//
//����ֵ��	��													//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////////////////////////
void VMatrix3::RotateTM(VAxisAngle& vAxisAng)
{
	VMatrix3 tmR;
	tmR.SetTMForRotate(vAxisAng);
	(*this) = (*this) * tmR;
}

//////////////////////////////////////////////
//������	ScaleTM(VVector3& vScale)		//
//���ܣ�	�ڱ任����Ļ����ϵ�������		//
//������	vScale-�������ŵ���				//
//����ֵ��	��								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::ScaleTM(VVector3& vScale)
{
	/*for (int i = 0; i < 4; i++)
	{
		m_fMat[i] *= vScale.x;
		m_fMat[4 + i] *= vScale.y;
		m_fMat[8 + i] *= vScale.z;
	}*/
	m_fMat[0] *= vScale.x;
	m_fMat[5] *= vScale.y;
	m_fMat[11] *= vScale.z;
}

////////////////////////////////////���¾�Ϊ����������///////////////////////////////////////////

VMatrix3 VMatrix3::operator +() const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator -() const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = - m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator *(float scl) const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = scl * m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator /(float scl) const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i] / scl;
	}
	return mat;
}

VMatrix3 VMatrix3::operator +(VMatrix3& mat2)
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i] + mat2.m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator -(VMatrix3& mat2)
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i] - mat2.m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator *(VMatrix3& mat2)
{
	VMatrix3 mat;
	int i, j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			mat.m_fMat[4 * i + j] = m_fMat[4 * i] * mat2.m_fMat[j] 
			+ m_fMat[4 * i + 1] * mat2.m_fMat[4 + j]
			+ m_fMat[4 * i + 2]*mat2.m_fMat[8 + j];
		}
	}
	mat.m_fMat[3] += m_fMat[3];
	mat.m_fMat[7] += m_fMat[7];
	mat.m_fMat[11] += m_fMat[11];
	return mat;
}

VMatrix3 VMatrix3::operator /(VMatrix3& mat2)
{
	VMatrix3 mat, mat1;
	if(mat2.GetInverseMat(mat1))
	{
		mat = (*this) * mat1;
	}
	return mat;
}

VMatrix3& VMatrix3::operator +=(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] += mat2.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator -=(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] -= mat2.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator *=(VMatrix3& mat2)
{
	VMatrix3 mat1;
	mat1 = (*this) * mat2;
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat1.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator /=(VMatrix3& mat2)
{
	VMatrix3 mat,mat1;
	if(mat2.GetInverseMat(mat1))
	{
		mat = (*this) * mat1;
	}
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator *=(float scl)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] *= scl;
	}
	return (*this);
}

VMatrix3& VMatrix3::operator /=(float scl)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] /= scl;
	}
	return (*this);
}

bool VMatrix3::operator ==(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		if(m_fMat[i] != mat2.m_fMat[i])
			return false;
	}
	return true;
}

VMatrix3& VMatrix3::operator =(const VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat2.m_fMat[i];
	}
	return (*this);
}