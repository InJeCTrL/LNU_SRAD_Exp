#pragma once
#include <vector>
#include <array>
#define OK 0
#define ERR 10001
class DataBaseMgr
{
protected:
	//ָ�����ݿ����Ӷ���
	_ConnectionPtr pConnection;
	//ָ���ȡ��¼����
	_RecordsetPtr pRecordset;
public:
	//��ʼ�����ݿ������
	DataBaseMgr(void);
	//����
	~DataBaseMgr(void);
	//�������ݿ�����
	INT TestDB(void);
	//������ݿ�
	INT CleanDB(void);
	//����CSV�ļ������ݿ�
	INT CSV2DB(CString FolderPath);
	//����������Ҫָ��
	std::vector<std::array<CString, 2>> SearchMainDG(INT SearchIndex, INT Combo_index, CString edit[1][2]);
	//��ȡ��ϸָ��
	std::vector<std::vector<CString>> GetDetail(INT index_tbl, INT flag_time, CString symbol);
	//��ȡĳ�ɶ�Ӧ���һ�������ֽ���
	DOUBLE GetLastCashflow(CString symbol);
};