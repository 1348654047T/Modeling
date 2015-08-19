/**********************************************************************
DESCRIPTION: ������ز�����ע��4ά�����������õ�ֻ��12��Ԫ�أ�
��˿�����12Ԫ������洢4ά����
����Ϊ3*4���󣬽��о��������ʱ�����4ά���� M*X^T

CREATED BY:  [8/9/2015 niewenchao]
**********************************************************************/
#ifndef _VMATRIX_H_
#define _VMATRIX_H_
//////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <cmath>
#include "vaxisangle.h"
//////////////////////////////////////////////////////////////////////////
class VMatrix3														//VMatrix3Ϊ3��4�ľ���
{
public:
	VMatrix3();														//���캯��
	VMatrix3(float fVal);											//����һ���Խ���Ϊval�ľ���
	VMatrix3(const VMatrix3& mat2);									//�������캯��
	~VMatrix3();													//��������
public:
	float m_fMat[12];												//��һά����洢����Ԫ��{(0,1,2,3);(3,4,5,6);(7,8,9,10)}

public:

	void SetValue(float* pMat);										//���þ����Ԫ��ֵ
	void SetValue(VMatrix3& mat2);									//����Դ�������øþ����Ԫ��ֵ
	void SetRowValue(int iRow, float* pRow);						//���þ���һ�е�ֵ
	void SetColValue(int iCol, float* pCol);						//���þ���һ�е�ֵ
	void SetValue(int i, int j, float fValue);						//���þ���Ԫ�ص�ֵ
	void GetAllValue(float* pMat);									//���ؾ�������Ԫ��
	void GetRowValue(int iRow, float* pRow);						//���ؾ���һ�е�Ԫ��ֵ
	void GetColValue(int iCol, float* pCol);						//���ؾ���һ�е�Ԫ��ֵ
	float GetValue(int i, int j);									//���ؾ���ĳһԪ��ֵ
	float* operator[](int iRow);									//����[]������
	float GetMatDet();												//���ظþ��������ʽֵ
	bool GetInverseMat(VMatrix3& mat);								//���ظþ���������
	void GetTransPoseMat(float* pMat) const;						//���ظþ����ת�þ���
	void GetTransMat(VMatrix3& tMat);								//�õ��þ����ƽ�ƾ���			
	void GetRotateMat(VMatrix3& rMat);								//�õ��þ������ת����������R*S
	void GetScaleMat(VMatrix3& sMat);								//�õ��þ�������ž���������R*S
	void GetTRSMat(VMatrix3& tMat,VMatrix3& rMat,VMatrix3& sMat);	//�ֽ����Ϊƽ�ơ���ת�����ž���

	void IdentifyTM();												//����Ϊ��λ��
	void InverseTM();												//���øþ���Ϊ�������
	VPoint3 TransPoint(VPoint3& p1);								//�Ե���пռ�任
	void SetTMForMove(VVector3& vMove);								//���øþ���Ϊָ��ƽ�ƾ���
	void SetTMForRotate(VAxisAngle& AxisAng);						//���øþ���Ϊָ����ת����
	void SetTMForScale(VVector3& vScale);							//���øþ���Ϊָ�����ž���
	void MoveTM(VVector3& vec1);									//����ƽ�ƾ���
	void RotateTM(VAxisAngle& AxisAng);			//�ڸ�������ϵ����ת�任����
	void ScaleTM(VVector3& vScale);									//�������ž���

	VMatrix3 operator +() const;									//��������+������
	VMatrix3 operator -() const;									//���ظ���-������
	VMatrix3 operator *(float scl) const;							//���س˺Ų�����*
	VMatrix3 operator /(float scl) const;							//���س��Ų�����/
	VMatrix3 operator + (VMatrix3& mat2);							//���ؼӺ�+������
	VMatrix3 operator - (VMatrix3& mat2);							//���ؼ���-������
	VMatrix3 operator * (VMatrix3& mat2);							//���س˺�*������
	VMatrix3 operator / (VMatrix3& mat2);							//���س��Ų�����
	VMatrix3& operator += (VMatrix3& mat2);						//����+=
	VMatrix3& operator -= (VMatrix3& mat2);						//����-=
	VMatrix3& operator *= (VMatrix3& mat2);						//����*=
	VMatrix3& operator /= (VMatrix3& mat2);						//����/=
	VMatrix3& operator *= (float scl);								//����*=
	VMatrix3& operator /= (float scl);								//����/=
	bool operator == (VMatrix3& mat2);								//���صȺ�==������
	VMatrix3& operator = (const VMatrix3& mat2);					//���ظ�ֵ=������

};


#endif