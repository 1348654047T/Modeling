#include "vimport.h"
#include "vmatrix.h"
VImport* VImport::m_pImport = NULL;
/*********************************************************************************
  *Function:DoImport(string fileName)  
  *Description������VCCģ���ļ���Ŀǰ֧�ֽ������������ݵ�VCCģ�ͣ����ʡ����ա������������ݴ����� 
  *Input:  fileName-ģ���ļ�·��
  *Return: ����ɹ�����true ����false 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
bool VImport::DoImport(string fileName)
{
	string ext = fileName.substr(fileName.rfind('.')+1);
	if (ext.compare("VCC") || ext.compare("vcc"))
	{
		FILE* fp = fopen(fileName.c_str(), "r+");
		if (NULL == fp) return false;
		char buf[512];
		//	#Head------------->#HeadEnd
		bool bone_exist = false;
		bool skin_exist = false;
		bool mesh_exist = false;
		bool mtl_exist =false;
		while(fscanf(fp,"%[^\n]\n",buf))
		{
			if(0 == strcmp(buf, "#HeadEnd"))
			{
				break;
			}
			switch(buf[0])
			{
			case 'b':bone_exist = true;break;
			case 's':skin_exist = true;break;
			case 'm':mesh_exist = true;break;
			case 't':mtl_exist = true;break;
			}
			
	    }
		// #Mesh----------------->#MeshEnd
		if(mesh_exist) 
			return  OnImportMesh(fp);
	}
	else
	{
		return true;
	}
}
/*********************************************************************************
  *Function:OnImportMesh(FILE* fp)  
  *Description������VCCģ�����񲿷֣�һ��ģ�����񲿷�����ܴ��ڶ������part 
  *Input:  fp-�򿪵��ļ�ָ��
  *Return: ����ɹ�����true ����false  
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
bool VImport::OnImportMesh(FILE* fp)
{
	char buf[512];

	// �ж��ļ�ָ���Ƿ���ȷ
	fscanf(fp,"%[^\n]\n",buf);
	if(0 != strcmp(buf, "#Mesh"))
	{
		return false;
	}


	while(fscanf(fp,"%s",buf) != EOF && strcmp(buf,"#MeshEnd") != 0 )
	{	
		if (strcmp(buf,"#Part") == 0)
		{
			fseek(fp,-5L,SEEK_CUR);
			OnReadOnePart(fp);
		}
		else
		{
			fscanf(fp,"%[^\n]\n",buf);
		}
	}
	fscanf(fp,"\n");
	if(0 != strcmp(buf, "#MeshEnd"))
	{
		return false;
	}
	else
	{
		return true;
	}
}
/*********************************************************************************
  *Function: OnReadOnePart(FILE* fp) 
  *Description�� ��������ģ���е�һ��part�������ص������ṹ��
  *Input:  fp-�ļ�ָ��
  *Return: �ɹ�true ����false 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
bool VImport::OnReadOnePart(FILE* fp)
{
	char buf[512];
	fscanf(fp,"#Part\n");

	fscanf(fp,"n %s\n",buf);									//	mesh������
	VMesh* m_mesh = new VMesh();
	VNode* node = m_pScence->CreateNode(m_mesh);
	node->SetNodeName(buf);
	float mat[12];
	fscanf(fp,"m %f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",			//��ȡ�������
		&mat[0],&mat[1],&mat[2],&mat[3],&mat[4],&mat[5],&mat[6],
		&mat[7],&mat[8],&mat[9],&mat[10],&mat[11]);
	VMatrix3* pmat = new VMatrix3;
	pmat->SetValue(mat);
	node->GetTMController()->SetTM(pmat);
	// ���⣬�������һ���ַ���
	fscanf(fp,"t %s\n",buf);
	

	bool nExist=false;
	bool tExist=false;
	while(fscanf(fp,"%s",buf) != EOF && strcmp(buf,"#PartEnd") != 0) {
		switch(buf[0]){
		case 'v':
			fseek(fp,-1L,SEEK_CUR);
			OnImportVertex(fp,m_mesh);	//���붥������	
			break;
		case 'n':
			nExist = true;
			fseek(fp,-1L,SEEK_CUR);
			OnImportNormal(fp,m_mesh);	//���뷨������
			break;
		case 't':
			tExist = true;
			fseek(fp,-1L,SEEK_CUR);
			OnImportTVert(fp,m_mesh);		//��������������
			break;
		case 'f':
			fseek(fp,-1L,SEEK_CUR);
			OnImportFace(fp,m_mesh,nExist,tExist);		//������Ƭ����
			break;
		}
	}
	fscanf(fp,"\n");
	m_mesh->ComputeBoundBox();
	return true;
}
/*********************************************************************************
  *Function: OnImportVertex(FILE* fp,VMesh* m_mesh) 
  *Description�� �������񶥵㵽VMesh��
  *Input:  fp-�ļ�ָ�룬m_mesh VMesh����ָ��
  *Return: �� 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
void VImport::OnImportVertex(FILE* fp,VMesh* m_mesh){			//���붥������
	int vNum = 0;
	fscanf(fp,"v %d\n",&vNum);									//��ȡ���񶥵���Ŀ
	m_mesh->SetNumVerts(vNum);										//�������񶥵���Ŀ
	float x = 0.0f,y=0.0f,z=0.0f;
	for (int i=0;i<vNum;i++)
	{
		fscanf(fp,"%f,%f,%f\n",&x,&y,&z);						//���ζ�ȡ��������
		m_mesh->SetVert(i,x,y,z);									//���ö�������
	}
}
//������Ƭ
void VImport::OnImportFace(FILE* fp,VMesh* m_mesh,bool nExist /* = true */,bool tExist /* = true */){
	int fNum = 0;
	fscanf(fp,"f %d\n",&fNum);									//��ȡ������Ƭ��Ŀ
	m_mesh->SetNumFaces(fNum);										//����������Ƭ��Ŀ

	if (nExist&&tExist)
	{
		int x = 0, y = 0, z = 0;
		int nx = 0, ny = 0, nz = 0;
		int tx = 0, ty = 0, tz = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &x, &nx, &tx, &y, &ny, &ty, &z, &nz, &tz);
			//mesh.SetFace_Normal_Verts(i, x, y, z, nx, ny, nz);
			//mesh.SetTVFace(i, tx, ty, tz);
			m_mesh->SetFace(i, x, y, z);
		}
	}
	else if (nExist&&!tExist)
	{
		int x = 0, y = 0, z = 0;
		int nx = 0, ny = 0, nz = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d/%d %d/%d %d/%d\n", &x, &nx, &y, &ny, &z, &nz);
			m_mesh->SetFace(i, x, y, z);
			//mesh.SetFace_Normal_Verts(i, x, y, z, nx, ny, nz);
		}
	}
	else if (!nExist&&tExist)
	{
		int x = 0, y = 0, z = 0;
		int tx = 0, ty = 0, tz = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d/%d %d/%d %d/%d\n", &x, &tx, &y,&ty, &z, &tz);
			m_mesh->SetFace(i, x, y, z);
			//mesh.SetTVFace(i, tx, ty, tz);
		}
	}
	else
	{
		int x = 0, y = 0, z = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d %d %d\n", &x,&y,&z);
			m_mesh->SetFace(i, x, y, z);
		}
	}

}
//���뷨��
void VImport::OnImportNormal(FILE* fp,VMesh* m_mesh){			//���붥������
	int vNum = 0;
	fscanf(fp,"n %d\n",&vNum);									//��ȡ��������Ŀ
	//mesh.SetNumNormals(vNum);
	float x = 0.0f,y=0.0f,z=0.0f;
	for (int i=0;i<vNum;i++)
	{
		fscanf(fp,"%f,%f,%f\n",&x,&y,&z);						//���ζ�ȡ���㷨������
		//mesh.SetNormal(i,x,y,z);									//���ö��㷨������
	}
}
//����������
void VImport::OnImportTVert(FILE* fp,VMesh* m_mesh){			//���붥������
	int tvNum = 0;
	fscanf(fp,"t %d\n",&tvNum);								//��ȡ������������Ŀ
	//mesh.SetNumTVerts(tvNum);									//����������������Ŀ
	float x = 0.0f,y=0.0f,z=0.0f;
	for (int i=0;i<tvNum;i++)
	{
		fscanf(fp,"%f,%f,%f\n",&x,&y,&z);						//���ζ�ȡ����������
		//mesh.SetTVert(i,x,y,z);									//��������������
	}
}