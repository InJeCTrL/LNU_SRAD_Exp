#pragma once
#include <vector>
#include <array>
#define OK 0
#define ERR 10001
class DataBaseMgr
{
protected:
	//指向数据库连接对象
	_ConnectionPtr pConnection;
	//指向读取记录对象
	_RecordsetPtr pRecordset;
public:
	//初始化数据库管理类
	DataBaseMgr(void);
	//析构
	~DataBaseMgr(void);
	//测试数据库连接
	INT TestDB(void);
	//清空数据库
	INT CleanDB(void);
	//导入CSV文件到数据库
	INT CSV2DB(CString FolderPath);
	//条件搜索主要指标
	std::vector<std::array<CString, 2>> SearchMainDG(INT SearchIndex, INT Combo_index, CString edit[1][2]);
	//获取详细指标
	std::vector<std::vector<CString>> GetDetail(INT index_tbl, INT flag_time, CString symbol);
	//获取某股对应最近一个自由现金流
	DOUBLE GetLastCashflow(CString symbol);
};