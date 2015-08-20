#ifndef _VIMPORT_H_
#define _VIMPORT_H_
/**********************************************************************
DESCRIPTION:������ȡVCC�����������е�������һ��VNode�󶨲�������VScene����  

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
///////////////////////////////////////////////
#include <cstdio>
#include <string>
#include <iostream>
#include "vmesh.h"
#include "vscene.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
using std::string;
class VImport
{
public:
	VImport(void) {};
	~VImport(void) {};
	//����ģʽ
	static VImport* GetInstance()
	{ 
		if (m_pImport == NULL) 
			m_pImport = new VImport();
		return m_pImport;
	}
	 bool DoImport(string fileName);//����
	 bool OnImportMesh(FILE* fp);												//����Mesh
	 bool OnReadOnePart(FILE* fp);
	 void OnImportVertex(FILE* fp,VMesh* mesh);									//���붥������
	 void OnImportFace(FILE* fp,VMesh* mesh,bool nExist = true,bool tExist = true);									//������Ƭ����
	 void OnImportNormal(FILE* fp,VMesh* mesh);									//���붥�㷨������
	 void OnImportTVert(FILE* fp,VMesh* mesh);									//��������������
protected:
	
private:
	VScene* m_pScence;
	static VImport* m_pImport;
};







///////////////////////////////////////////////
#endif