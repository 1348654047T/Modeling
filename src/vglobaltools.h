/**********************************************************************
DESCRIPTION: ����һЩ���ʺϷ���������ĳ��õĹ��� 

CREATED BY:  [8/2/2015 niewenchao]
**********************************************************************/
#ifndef _VGLOBALTOOLS_H_
#define _VGLOBALTOOLS_H_

#include "vpoint.h"
#include <math.h>
#include <string>
using namespace std;

//VPoint2�����,�ɲο�class VPoint2,�����ļ�VPoint.h
inline float GetFLength(const VPoint2& p1);				//��һ����ά�㵽ԭ��ľ���
float GetFLength(VPoint3& p1, VPoint3& p2);				//��������ά��֮��ľ���
inline float GetFLenSquared(const VPoint2& p1);			//��һ����ά�㵽ԭ������ƽ��
float GetFLenSquared(VPoint3& p1, VPoint3& p2);
VPoint2 FNormalize(const VPoint2& p1);
inline float FDotProd(const VPoint2& p1,const VPoint2& p2);//���
float GetFCosA(VVector2& vec1, VVector2& vec2);//���

//VPoint3�����,�ɲο�class VPoint3,�����ļ�VPoint.h
inline float GetFLength(const VPoint3& p1);
float GetFLength(VPoint3& p1, VPoint3& p2);
inline float GetFLenSquared(const VPoint3& p1);
float GetFLenSquared(VPoint3& p1, VPoint3& p2);
VPoint3 FNormalize(const VPoint3& p1);
inline float FDotProd(const VPoint3& p1,const VPoint3& p2);
VPoint3 FCrossProd(const VPoint3& p1,const VPoint3& p2);
float GetFCosA(VVector3& vec1,VVector3& vec2);
float GetFArea(VPoint3& p1,VPoint3& p2,VPoint3& p3);	//����������ɵ������ε����
VPoint3 GetFGravityCenter(VPoint3& p1,VPoint3& p2,VPoint3& p3);	//����������ɵ������ε�����

void string_replace(string & strBig, const string & strsrc, const string &strdst);
#endif
