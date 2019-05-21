#include "stdafx.h"
#include "DataBaseMgr.h"


DataBaseMgr::DataBaseMgr(void)
{
	pConnection.CreateInstance("ADODB.Connection");
	pRecordset.CreateInstance("ADODB.Recordset");
	CoInitialize(NULL);	//初始化COM
}

INT DataBaseMgr::TestDB(void)
{
	try
	{
		pConnection->Open("Provider = Microsoft.ACE.OLEDB.12.0; Data Source = DB.accdb", "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		return ERR;
	}
	return OK;
}

DataBaseMgr::~DataBaseMgr(void)
{
	try
	{
		pConnection->Close();
	}
	catch (_com_error e)
	{
		;
	}
}

INT DataBaseMgr::CleanDB(void)
{
	TestDB();
	try
	{
		pRecordset->Open("Drop table CodeName",
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		pRecordset->Open("Drop table LotsofInfo",
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		pRecordset->Open("Drop table MainDG",
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		pRecordset->Open("Drop table cashflow",
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		pRecordset->Open("Drop table income",
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		pRecordset->Open("Drop table balance",
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error e)
	{
		return ERR;
	}

	return OK;
}

INT DataBaseMgr::CSV2DB(CString FolderPath)
{
	TestDB();
	CString str_CodeName = L"Select * INTO CodeName FROM [TEXT;FMT=CSV;DELIMITED;HDR=YES;DATABASE=" + FolderPath + L"].[CodeName.csv];";
	CString str_cashflow = L"Select * INTO cashflow FROM [TEXT;FMT=CSV;DELIMITED;IMEX=1;HDR=YES;DATABASE=" + FolderPath + L"].[cashflow.csv];";
	CString str_income = L"Select * INTO income FROM [TEXT;FMT=CSV;DELIMITED;IMEX=1;HDR=YES;DATABASE=" + FolderPath + L"].[income.csv];";
	CString str_balance = L"Select * INTO balance FROM [TEXT;FMT=CSV;DELIMITED;IMEX=1;HDR=YES;DATABASE=" + FolderPath + L"].[balance.csv];";
	CString str_MainDG = L"Select * INTO MainDG FROM [TEXT;FMT=CSV;DELIMITED;IMEX=1;HDR=YES;DATABASE=" + FolderPath + L"].[MainDG_px.csv];";
	CString str_LotsofInfo = L"Select * INTO LotsofInfo FROM [TEXT;FMT=CSV;DELIMITED;IMEX=1;HDR=YES;DATABASE=" + FolderPath + L"].[LotsofInfo-PX.csv];";
	char str_CodeName_ANSI[1024] = { 0 };
	char str_cashflow_ANSI[1024] = { 0 };
	char str_income_ANSI[1024] = { 0 };
	char str_balance_ANSI[1024] = { 0 };
	char str_MainDG_ANSI[1024] = { 0 };
	char str_LotsofInfo_ANSI[1024] = { 0 };
	try
	{
		WideCharToMultiByte(CP_ACP, 0, str_CodeName, str_CodeName.GetLength(), str_CodeName_ANSI, 1024, NULL, NULL);
		pRecordset->Open(str_CodeName_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		WideCharToMultiByte(CP_ACP, 0, str_cashflow, str_cashflow.GetLength(), str_cashflow_ANSI, 1024, NULL, NULL);
		pRecordset->Open(str_cashflow_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		WideCharToMultiByte(CP_ACP, 0, str_income, str_income.GetLength(), str_income_ANSI, 1024, NULL, NULL);
		pRecordset->Open(str_income_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		WideCharToMultiByte(CP_ACP, 0, str_balance, str_balance.GetLength(), str_income_ANSI, 1024, NULL, NULL);
		pRecordset->Open(str_income_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		WideCharToMultiByte(CP_ACP, 0, str_MainDG, str_MainDG.GetLength(), str_MainDG_ANSI, 1024, NULL, NULL);
		pRecordset->Open(str_MainDG_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		WideCharToMultiByte(CP_ACP, 0, str_LotsofInfo, str_LotsofInfo.GetLength(), str_LotsofInfo_ANSI, 1024, NULL, NULL);
		pRecordset->Open(str_LotsofInfo_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error e)
	{
		return ERR;
	}

	return OK;
}

std::vector<std::array<CString, 2>> DataBaseMgr::SearchMainDG(INT SearchIndex, INT Combo_index, CString edit[1][2])
{
	TestDB();
	std::vector<std::array<CString, 2>> result;
	std::array<CString, 2> resultnode;
	_variant_t vtnode[2];
	char SQL_ANSI[10001] = { 0 };
	CString SQL = L"Select distinct CodeName.symbol,display_name from MainDG, CodeName where MainDG.symbol = CodeName.symbol";
	
	//构造SQL语句
	if (SearchIndex == 6)
	{
		SQL += L" and MainDG.symbol like \'%" + edit[0][0] + L"%\'";
	}
	else
	{
		switch (Combo_index)
		{
		case 0:
			SQL += L" and date > 2018-01-01";
			break;
		case 1:
			SQL += L" and date > 2014-01-01";
			break;
		case 2:
			SQL += L" and date > 2008-01-01";
			break;
		default:
			break;
		}
		switch (SearchIndex)
		{
		case 0:
			SQL += L" and profit_from_operations <> null and CDbl(profit_from_operations) between " + edit[0][0] + L" and " + edit[0][1];
			break;
		case 1:
			SQL += L" and net_cash_flows_from_opt_act <> null and CDbl(net_cash_flows_from_opt_act) between " + edit[0][0] + L" and " + edit[0][1];
			break;
		case 2:
			if (Combo_index == 3)
				SQL += L" and roe_ave <> null and CDbl(roe_ave) between " + edit[0][0] + L" and " + edit[0][1];
			else if (Combo_index == 4)
				SQL += L" and roe_vic <> null and CDbl(roe_vic) between " + edit[0][0] + L" and " + edit[0][1];
			else
				SQL += L" and roe <> null and CDbl(roe) between " + edit[0][0] + L" and " + edit[0][1];
			break;
		case 3:
			if (Combo_index == 3)
				SQL += L" and opt_profit_growth_ratio_ave <> null and CDbl(opt_profit_growth_ratio_ave) between " + edit[0][0] + L" and " + edit[0][1];
			else if (Combo_index == 4)
				SQL += L" and opt_profit_growth_ratio_vic <> null and CDbl(opt_profit_growth_ratio_vic) between " + edit[0][0] + L" and " + edit[0][1];
			else
				SQL += L" and opt_profit_growth_ratio <> null and CDbl(opt_profit_growth_ratio) between " + edit[0][0] + L" and " + edit[0][1];
			break;
		case 4:
			if (Combo_index == 3)
				SQL += L" and roic_ttm_ave <> null and CDbl(roic_ttm_ave) between " + edit[0][0] + L" and " + edit[0][1];
			else if (Combo_index == 4)
				SQL += L" and roic_ttm_vic <> null and CDbl(roic_ttm_vic) between " + edit[0][0] + L" and " + edit[0][1];
			else
				SQL += L" and roic_ttm <> null and CDbl(roic_ttm) between " + edit[0][0] + L" and " + edit[0][1];
			break;
		case 5:
			SQL += L" and CDbl(basic_eps) between " + edit[0][0] + L" and " + edit[0][1];
			break;
		default:
			break;
		}
	}
	try
	{
		WideCharToMultiByte(CP_ACP, 0, SQL, SQL.GetLength(), SQL_ANSI, 10001, NULL, NULL);
		pRecordset->Open(SQL_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		while (!pRecordset->adoEOF)
		{
			vtnode[0] = pRecordset->GetCollect("symbol");
			vtnode[1] = pRecordset->GetCollect("display_name");
			for (INT i = 0; i < 2; i++)
			{
				if (vtnode[i].vt == VT_NULL)
				{
					resultnode[i] = L"";
				}
				else
				{
					resultnode[i] = (LPCTSTR)_bstr_t(vtnode[i]);
				}
			}
			result.push_back(resultnode);
			pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		return result;
	}

	//关闭记录集及库
	pRecordset->Close();

	return result;
}

std::vector<std::vector<CString>> DataBaseMgr::GetDetail(INT index_tbl, INT flag_time, CString symbol)
{
	TestDB();
	std::vector<std::vector<CString>> result;
	std::vector<CString> resultnode;
	std::vector<_variant_t> vtnode;
	char SQL_ANSI[10001] = { 0 };
	CString SQL = L"Select * from ";

	switch (index_tbl)
	{
	//主要指标
	case 0:
		SQL += L"MainDG where symbol = \"" + symbol + L"\"";
		break;
	//综合分析
	case 1:
		SQL += L"LotsofInfo where symbol = \"" + symbol + L"\"";
		break;
	//资产负债
	case 2:
		SQL += L"balance where symbol = \"" + symbol + L"\"";
		break;
	//现金流量
	case 3:
		SQL += L"cashflow where symbol = \"" + symbol + L"\"";
		break;
	//利润
	case 4:
		SQL += L"income where symbol = \"" + symbol + L"\"";
		break;
	default:
		break;
	}
	switch (flag_time)
	{
	//年报（第四季度）
	case 0:
		SQL += L" and Format(date,\"q\")=4 order by date";
		break;
	//季报
	case 1:
		SQL += L" order by date";
		break;
	//报告期
	case 2:
		SQL += L" order by date_repo";
		break;
	default:
		break;
	}
	try
	{
		WideCharToMultiByte(CP_ACP, 0, SQL, SQL.GetLength(), SQL_ANSI, 10001, NULL, NULL);
		pRecordset->Open(SQL_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		while (!pRecordset->adoEOF)
		{
			for (LONG index = 0; index < pRecordset->Fields->Count; index++)
			{
				vtnode.push_back(pRecordset->GetCollect(_variant_t(index)));
				if (vtnode.back().vt == VT_NULL)
				{
					resultnode.push_back(L"");
				}
				else
				{
					resultnode.push_back((LPCTSTR)_bstr_t(vtnode.back()));
					if (resultnode[index][0] == '.')
					{
						resultnode[index] = '0' + resultnode[index];
					}
					else if (resultnode[index][0] == '-' && resultnode[index][1] == '.')
					{
						resultnode[index].Insert(1, L"0");
					}
				}
			}
			result.push_back(resultnode);
			resultnode.clear();
			vtnode.clear();
			pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		return result;
	}

	//关闭记录集及库
	pRecordset->Close();

	return result;
}

DOUBLE DataBaseMgr::GetLastCashflow(CString symbol)
{
	TestDB();
	_variant_t vtnode;
	DOUBLE result = 0;
	char SQL_ANSI[10001] = { 0 };
	CString SQL = L"Select NmC from MainDG where symbol = \"" + symbol + "\" order by date desc";

	try
	{
		WideCharToMultiByte(CP_ACP, 0, SQL, SQL.GetLength(), SQL_ANSI, 10001, NULL, NULL);
		pRecordset->Open(SQL_ANSI,
			pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		//只取最近一次
		if (!pRecordset->adoEOF)
		{
			vtnode = pRecordset->GetCollect("NmC");
			if (vtnode.vt != VT_NULL)
			{
				result = vtnode.dblVal;
			}
		}
	}
	catch (_com_error e)
	{
		return result;
	}

	pRecordset->Close();
	
	return result;
}