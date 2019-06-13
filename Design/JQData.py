from jqdata import finance
import pandas
print("BG")
list_stock = list(get_all_securities().index)
for year in list(range(2005,2020)):
    q = query(cash_flow.code,
            cash_flow.statDate,
            cash_flow.pubDate,
            cash_flow.fix_intan_other_asset_acqui_cash,
            cash_flow.net_operate_cash_flow,
            indicator.roe,
            indicator.inc_return,
            indicator.eps,
            indicator.operating_profit,
            income.operating_revenue,
            income.total_operating_revenue,
            indicator.inc_operation_profit_year_on_year,
            indicator.inc_total_revenue_year_on_year,
            indicator.inc_net_profit_to_shareholders_year_on_year
    ).filter(cash_flow.code.in_(list_stock))
    df = get_fundamentals(q, statDate=str(year))
    if year == 2005:
        df_out = df
    else:
        df_out = pandas.concat([df_out,df])
    print(shape(df_out))
#df_out.columns = ['symbol','date','date_repo','other_receivableA','advance_paymentA','total_assetsA']

df_out.to_csv('test.csv',index=False)
print("ACC")