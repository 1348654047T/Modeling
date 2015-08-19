/**********************************************************************

DESCRIPTION:  VPoint.h �����˶�ά ��ά��ĳ��ò���

CREATED BY: С��C���ǲ�  [7/28/2015 niewenchao]
**********************************************************************/
#ifndef _VPOINT_H_
#define _VPOINT_H_
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
class VPoint2{																// ��ά��Ķ���
public:
	VPoint2(){x = y = 0.0f;}																//Ĭ�Ϲ��캯��
	VPoint2(float px, float py){x = px; y = py;}											//���캯����Ϊ�����ά���ṩ�˷���
	VPoint2(int px, int py){x = (float)px; y = (float)py;}									//���캯����Ϊ�����ά���ṩ�˷���
	VPoint2(double px, double py){x = (float)px; y = (float)py;}							//���캯����Ϊ�����ά���ṩ�˷���
	VPoint2(const VPoint2& FromPoint){x = FromPoint.x; y = FromPoint.y;}					//���캯����Ϊ�����ά���ṩ�˷���
	VPoint2(float point_f[2]){x = point_f[0]; y = point_f[1];}								//���캯����Ϊ�����ά���ṩ�˷���
	VPoint2(int point_i[2]){x = (float)point_i[0]; y = (float)point_i[1];}					//���캯����Ϊ�����ά���ṩ�˷���
	VPoint2(double point_d[2]){x = (float)point_d[0]; y = (float)point_d[1];}				//���캯����Ϊ�����ά���ṩ�˷���
	~VPoint2(){}																			//��������

public:
	//attribution
	float x;																// x����
	float y;																// y����

public:
	//Member Function
	float operator[](int i)
	{
		if(i <= 0)	return x;
		else if(i >= 1)	return y;
	}
	VPoint2 operator-() const	{VPoint2 p; p.x = -x; p.y = -y; return p;}
	VPoint2 operator+() const	{VPoint2 p; p.x = x; p.y = y; return p;}
	VPoint2 operator*(float scl) const{VPoint2 p1; p1.x = x * scl; p1.y = y * scl; return p1;}
	VPoint2 operator/(float scl) const {VPoint2 p1; p1.x = x / scl; p1.y = y / scl; return p1;}
	inline VPoint2& operator-=(const VPoint2& p2){x -= p2.x; y -= p2.y; return (*this);}
	inline VPoint2& operator+=(const VPoint2& p2){x += p2.x; y += p2.y; return (*this);}
	inline VPoint2& operator*=(const VPoint2& p2){x *= p2.x; y *= p2.y; return (*this);}
	inline VPoint2& operator/=(const VPoint2& p2){x /= p2.x; y /= p2.y; return (*this);}							//���ã���֤������Ϊ0
	inline VPoint2& operator*=(float scl){x *= scl; y *= scl; return (*this);}
	inline VPoint2& operator/=(float scl){x /= scl; y /= scl; return (*this);}									//���ã���֤������Ϊ0
	inline bool operator==(VPoint2& p2){if((x == p2.x) && (y == p2.y)) return true;return false;}
	inline VPoint2 operator-(VPoint2& p2){VPoint2 p1; p1.x = x - p2.x; p1.y = y - p2.y; return p1;}
	inline VPoint2 operator+(VPoint2& p2){VPoint2 p1; p1.x = x + p2.x; p1.y = y + p2.y; return p1;}
	inline VPoint2 operator*(VPoint2& p2){VPoint2 p1; p1.x = x * p2.x; p1.y = y * p2.y; return p1;}
	inline VPoint2 operator/(VPoint2& p2){VPoint2 p1; p1.x = x / p2.x; p1.y = y / p2.y; return p1;}				//���ã���֤������Ϊ0
	VPoint2& operator =(const VPoint2& p2){ x = p2.x; y = p2.y; return (*this); }

	//��������X Y Z��Ϣ
	void SetXY(float px,float py){x = px; y = py;}
	void SetXY(int px, int py){x = (float)px; y = (float)py;}
	void SetXY(double px, double py){x = (float)px; y = (float)py;}
	void SetXY(const VPoint2& FromPoint){x = FromPoint.x; y = FromPoint.y;}
	void SetXY(float point_f[2]){x = point_f[0]; y = point_f[1];}
	void SetXY(int point_i[2]){x = (float)point_i[0]; y = (float)point_i[1];}
	void SetXY(double point_d[2]){x = (float)point_d[0]; y = (float)point_d[1];}

	//�жϷ��������
	bool EqualZero()
	{
		if((x == 0.0f) && (y == 0.0f))
			return true;
		return false;
	}
	bool Equal(float px,float py)
	{
		if((x == px) && (y == py))
			return true;
		return false;
	}
	bool Equal(int px, int py)
	{
		if((x == (float)px) && (y == (float)py))
			return true;
		return false;
	}
	bool Equal(double px, double py)
	{
		if((x == (float)px) && (y == (float)py))
			return true;
		return false;
	}																			
};

typedef VPoint2 VVector2;													//����һ����ά��������

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class VPoint3{																// ��ά��Ķ���
public:
	// constructor
	VPoint3(){ x = y = z = 0.0f;}											// Ĭ�Ϲ��캯��
	VPoint3(float px,float py,float pz){x = px;y = py;z = pz;}				// ���ع��캯�������㹹��
	VPoint3(double px,double py,double pz){x = (float)px; y = (float)py; z = (float)pz;}
	VPoint3(int px,int py,int pz){x = (float)px; y = (float)py; z = (float)pz;}
	VPoint3(const VPoint3& SourcePoint){x = SourcePoint.x;y = SourcePoint.y;z = SourcePoint.z;}
	VPoint3(float af[3]){x = af[0];y = af[1];z = af[2];}
	VPoint3(double af[3]){x = (float)af[0];y = (float)af[1];z = (float)af[2];}
	VPoint3(int af[3]){x = (float)af[0];y = (float)af[1];z = (float)af[2];}
	~VPoint3(){}

public:
	//attribution
	float x;																// x����
	float y;																// y����
	float z;																// z����
public:
	
	float operator[](int i)
	{
		if(i <= 0)	return x;
		else if(i = 1)	return y;
		else if(i >= 2)	return z;
	}
	VPoint3 operator-() const	{VPoint3 p; p.x = -x; p.y = -y; p.z = -z; return p;}
	VPoint3 operator+() const	{VPoint3 p; p.x = x; p.y = y; p.z = z; return p;}
	VPoint3 operator*(float scl) const {VPoint3 p1; p1.x = x * scl; p1.y = y * scl; p1.z = z * scl; return p1;}
	VPoint3 operator/(float scl) const {VPoint3 p1; p1.x = x / scl; p1.y = y / scl; p1.z = z / scl; return p1;}
	inline VPoint3& operator-=(const VPoint3& p2){x -= p2.x; y -= p2.y; z -= p2.z; return (*this);}
	inline VPoint3& operator+=(const VPoint3& p2){x += p2.x; y += p2.y; z += p2.z; return (*this);}
	inline VPoint3& operator*=(const VPoint3& p2){x *= p2.x; y *= p2.y; z *= p2.z; return (*this);}
	inline VPoint3& operator/=(const VPoint3& p2){x /= p2.x; y /= p2.y; z /= p2.z; return (*this);}							//���ã���֤������Ϊ0
	inline VPoint3& operator*=(float scl){x *= scl; y *= scl; z *= scl; return (*this);}
	inline VPoint3& operator/=(float scl){x /= scl; y /= scl; z /= scl; return (*this);}									//���ã���֤������Ϊ0
	inline bool operator==(VPoint3& p2){if((x == p2.x) && (y == p2.y) && (z == p2.z)) return true;return false;}
	inline VPoint3 operator-(VPoint3& p2){VPoint3 p1; p1.x = x - p2.x; p1.y = y - p2.y; p1.z = z - p2.z; return p1;}
	inline VPoint3 operator+(VPoint3& p2){VPoint3 p1; p1.x = x + p2.x; p1.y = y + p2.y; p1.z = z + p2.z; return p1;}
	inline VPoint3 operator*(VPoint3& p2){VPoint3 p1; p1.x = x * p2.x; p1.y = y * p2.y; p1.z = z * p2.z; return p1;}
	inline VPoint3 operator/(VPoint3& p2){VPoint3 p1; p1.x = x / p2.x; p1.y = y / p2.y; p1.z = z / p2.z; return p1;}		//���ã���֤������Ϊ0
	
	VPoint3 operator^(VPoint3& p2)																							//���
	{
		VPoint3 p1; 
		p1.x = y * p2.z - z * p2.y; 
		p1.y = z * p2.x - x * p2.z; 
		p1.z = x * p2.y - y * p2.x; 
		return p1;
	}
	//���
	float DianChen(const VPoint3& p2) {
		return x*p2.x + y*p2.y + z*p2.z;
	}
	VPoint3& operator =(const VPoint3& p2){ x = p2.x; y = p2.y; z = p2.z; return (*this); }
	//��������X Y Z��Ϣ
	void SetXYZ(float px,float py,float pz){x = px; y = py; z = pz;}
	void SetXYZ(int px, int py, int pz){x = (float)px; y = (float)py; z = (float)pz;}
	void SetXYZ(double px, double py, double pz){x = (float)px; y = (float)py; z = (float)pz;}
	void SetXYZ(const VPoint3& FromPoint){x = FromPoint.x; y = FromPoint.y; z = FromPoint.z;}
	void SetXYZ(float point_f[3]){x = point_f[0]; y = point_f[1]; z = point_f[2];}
	void SetXYZ(int point_i[3]){x = (float)point_i[0]; y = (float)point_i[1]; z = (float)point_i[2];}
	void SetXYZ(double point_d[3]){x = (float)point_d[0]; y = (float)point_d[1]; z = (float)point_d[2];}

	//�жϷ��������
	bool EqualZero()
	{
		if((x == 0.0f) && (y == 0.0f) && (z == 0.0f))
			return true;
		return false;
	}
	bool Equal(float px,float py,float pz)
	{
		if((x == px) && (y == py) && (z == pz))
			return true;
		return false;
	}
	bool Equal(int px, int py, int pz)
	{
		if((x == (float)px) && (y == (float)py) && (z == (float)pz))
			return true;
		return false;
	}
	bool Equal(double px, double py, double pz)
	{
		if((x == (float)px) && (y == (float)py) && (z == (float)pz))
			return true;
		return false;
	}
	float* Getfloat3(){ float v[3]; v[0] = x; v[1] = y; v[2] = z; return v;}
};


typedef VPoint3 VVector3;																										//����һ����ά�������ݽṹ
//////////////////////////////////////////////////////////////////////////
#endif