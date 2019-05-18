import pandas as pd
import numpy as np

dfA = pd.read_csv('LotsofInfoA.csv')
dfA = dfA.loc[list(range(0,len(dfA),2))]
dfB = pd.read_csv('LotsofInfoB.csv')
dfB = dfB.loc[list(range(0,len(dfB),2))]
dfD = pd.read_csv('LotsofInfoD.csv')
dfD = dfD.loc[list(range(0,len(dfD),2))]
dfC = pd.merge(dfB,dfA,on=['symbol','date','date_repo'],how='left')
dfE = pd.merge(dfC,dfD,on=['symbol','date'],how='left')
dfE['rateA'] = 0
dfE['rateB'] = 0
dfE['rateC'] = 0
dfE['rate1'] = 0
dfE['rate2'] = 0
dfE['other_receivableC'] = 0
dfE['advance_paymentC'] = 0
dfE['total_assetsC'] = 0
dfE['recv_NplusA'] = 0
dfE['payable_'] = 0
dfE['FplusC'] = 0
dfE['CALC'] = 0
len_dfE = len(dfE)
for ele in range(len_dfE):
    #修改股票代码后缀
    dfE.loc[ele,'symbol'] = dfE.iloc[ele]['symbol'].replace('XSHE','SZ')
    dfE.loc[ele,'symbol'] = dfE.iloc[ele]['symbol'].replace('XSHG','SH')
    #计算各项指标
    dfE.loc[ele,'rateA'] = dfE.iloc[ele]['other_receivableA'] / (dfE.iloc[ele]['other_receivableA'] + dfE.iloc[ele]['advance_paymentA'])
    dfE.loc[ele,'rateB'] = dfE.iloc[ele]['other_receivableB'] / (dfE.iloc[ele]['other_receivableB'] + dfE.iloc[ele]['advance_paymentB'])
    dfE.loc[ele,'other_receivableC'] = dfE.iloc[ele]['other_receivableB'] - dfE.iloc[ele]['other_receivableA']
    dfE.loc[ele,'advance_paymentC'] = dfE.iloc[ele]['advance_paymentB'] - dfE.iloc[ele]['advance_paymentA']
    dfE.loc[ele,'total_assetsC'] = dfE.iloc[ele]['total_assetsB'] - dfE.iloc[ele]['total_assetsA']
    dfE.loc[ele,'rateC'] = dfE.iloc[ele]['other_receivableC'] / (dfE.iloc[ele]['other_receivableC'] + dfE.iloc[ele]['advance_paymentC'])
    dfE.loc[ele,'rate1'] = dfE.iloc[ele]['notes_receivable'] / (dfE.iloc[ele]['notes_receivable'] + dfE.iloc[ele]['accounts_receivable'])
    dfE.loc[ele,'rate2'] = dfE.iloc[ele]['notes_payable'] / (dfE.iloc[ele]['account_payable'] + dfE.iloc[ele]['notes_payable'])
    dfE.loc[ele,'recv_NplusA'] = dfE.iloc[ele]['notes_receivable'] + dfE.iloc[ele]['accounts_receivable']
    dfE.loc[ele,'payable_'] = dfE.iloc[ele]['notes_payable'] + dfE.iloc[ele]['account_payable']
    dfE.loc[ele,'FplusC'] = dfE.iloc[ele]['fixed_assets'] + dfE.iloc[ele]['constru_in_process']
    dfE.loc[ele,'CALC'] = dfE.iloc[ele]['payable_'] + dfE.iloc[ele]['deposit_received'] - dfE.iloc[ele]['recv_NplusA']
    print('[ ' + str(ele+1) + ' / ' + str(len_dfE) + ' ] ' + str((ele+1) / len_dfE))
#删除多余列
del(dfE['fixed_assets'])
del(dfE['constru_in_process'])
dfE.to_csv('LotsofInfo-PX.csv', index=False)