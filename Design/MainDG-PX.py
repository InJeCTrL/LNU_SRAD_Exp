'''
operating_profit			营业利润
net_operate_cash_flow			自由现金流
roe					净资产收益率
inc_operation_profit_year_on_year	营业增长率
eps					每股收益
NmC					(自由现金流-固定资产等)
fix_intan_other_asset_acqui_cash	购建固定资产、无形资产和其他长期资产支付的现金(不出现)
'''
import pandas as pd
import numpy as np

df = pd.read_csv('JQData.csv')
#删除多余列
df.drop(['inc_return'],axis=1,inplace=True)
df.drop(['operating_revenue'],axis=1,inplace=True)
df.drop(['total_operating_revenue'],axis=1,inplace=True)
df.drop(['inc_total_revenue_year_on_year'],axis=1,inplace=True)
df.drop(['inc_net_profit_to_shareholders_year_on_year'],axis=1,inplace=True)
#生成空的均值方差列
df['roe_ave'] = 0
df['roe_vic'] = 0
df['inc_operation_profit_year_on_year_ave'] = 0
df['inc_operation_profit_year_on_year_vic'] = 0
df['NmC_ave'] = 0
df['NmC_vic'] = 0
df['NmC'] = 0
#列名统一
df.rename(columns={'code': 'symbol', 'statDate': 'date', 'pubDate': 'date_repo'}, inplace=True)

#第一次处理
print("开始第一次处理...")
for ele in range(len(df)):
    #修改股票代码后缀
    df.loc[ele,'symbol'] = df.iloc[ele]['symbol'].replace('XSHE','SZ')
    df.loc[ele,'symbol'] = df.iloc[ele]['symbol'].replace('XSHG','SH')
    #计算NmC
    df.loc[ele,'NmC'] = df.iloc[ele]['net_operate_cash_flow'] - df.iloc[ele]['fix_intan_other_asset_acqui_cash']
    print("[ " + str(ele + 1) + "/" + str(len(df)) + " ]")
print("第一次处理完成")

#第二次处理
print("开始第二次处理")
list_stock = []
for ele in df['symbol']:
    if(ele not in list_stock):
        list_stock.append(ele)
len_list = len(list_stock)
i = 1
for code in list_stock:
    tdf = df[df['symbol'] == code]
    tdf['roe_ave'] = np.sum(tdf['roe']) / len(tdf)
    tdf['roe_vic'] = np.var(tdf['roe'])
    tdf['NmC_ave'] = np.sum(tdf['NmC']) / len(tdf)
    tdf['NmC_vic'] = np.var(tdf['NmC'])
    tdf['inc_operation_profit_year_on_year_ave'] = np.sum(tdf['inc_operation_profit_year_on_year']) / len(tdf)
    tdf['inc_operation_profit_year_on_year_vic'] = np.var(tdf['inc_operation_profit_year_on_year'])
    df[df['symbol'] == code] = tdf
    print('[ ' + str(i) + '/' + str(len_list) + ' ] ' + str(i / len_list * 100))
    i += 1
print("第二次处理完成")
df.to_csv('MainDG_px.csv', index=False)