import pandas as pd
import numpy as np

df = pd.read_csv('MainDG.csv')
df['roe_ave'] = 0
df['roe_vic'] = 0
df['roic_ttm_ave'] = 0
df['roic_ttm_vic'] = 0
df['NmC_ave'] = 0
df['NmC_vic'] = 0
df['opt_profit_growth_ratio_ave'] = 0
df['opt_profit_growth_ratio_vic'] = 0
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
    tdf['roic_ttm_ave'] = np.sum(tdf['roic_ttm']) / len(tdf)
    tdf['roic_ttm_vic'] = np.var(tdf['roic_ttm'])
    tdf['NmC_ave'] = np.sum(tdf['NmC']) / len(tdf)
    tdf['NmC_vic'] = np.var(tdf['NmC'])
    tdf['opt_profit_growth_ratio_ave'] = np.sum(tdf['opt_profit_growth_ratio']) / len(tdf)
    tdf['opt_profit_growth_ratio_vic'] = np.var(tdf['opt_profit_growth_ratio'])
    df[df['symbol'] == code] = tdf
    print('[ ' + str(i) + '/' + str(len_list) + ' ] ' + str(i / len_list * 100))
    i += 1
df.to_csv('MainDG_px.csv', index=False)