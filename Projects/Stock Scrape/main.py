import requests
import pandas as pd
import time
from bs4 import BeautifulSoup
from pathlib import Path
from datetime import date

dir = str(Path(__file__).parent)
in_file = dir + "\\stocks.json"
out_file = dir + "\\stock_prices.csv"


def get_price(soup):
    price_class = "text-4xl font-bold transition-colors duration-300 inline-block"
    price_elem = soup.find_all('div', class_ = price_class)
    price = price_elem[0].text if len(price_elem) > 0 else None
    
    return price

def get_dividend(soup):
    div_table_class = "svelte-1swpzu1"
    table_elem = soup.find_all('table', class_ = div_table_class)
    table_elem = table_elem[0] if len(table_elem) > 0 else None
    
    row_elem = table_elem.find_all('tr')
    row_elem = row_elem[1] if len(row_elem) > 0 else None
    
    row_data = row_elem.find_all('td') if row_elem is not None else None
    price = row_data[1].text.replace("$", "") if row_data is not None else None
    date = row_data[3].text if row_data is not None else None
    
    return price, date

def get_stocks_info(stocks):
    results = []

    for stock in stocks:
        print(f"Retrieving {stock} Prices...")
        
        try:
            name = stock.lower()
            link = f"https://stockanalysis.com/etf/{name}/dividend/"
            
            req = requests.get(link)
            soup = BeautifulSoup(req.content, "html.parser")
            
            price = get_price(soup)
            div, pay_date = get_dividend(soup)
            today = date.today()
            
            if (price is not None and div is not None):
                results.append([stock, price, div, pay_date, today])
            else:
                print(f"Issue Retrieving {stock} ...")
                
        except Exception as e:
            print(f"Issue Retrieving {stock}:")
            print(str(e))
            
        finally:
            time.sleep(1)
        
    return results
  
def save(results_df: pd.DataFrame):
    try:
        exists = Path(out_file).is_file()
        if (exists):
            results_df.to_csv(out_file, mode='a',index=False, header=False)
        else:
            print("Creating CSV File ...")
            results_df.to_csv(out_file, index=False)
        print("Data Saved To CSV Successfully")
        
    except Exception as e:
        print(f"Failed To Save Data: {str(e)}")
    

if __name__ == "__main__":

    df = pd.read_json(in_file)
    stocks = df['stocks'].values
    
    results = get_stocks_info(stocks)
    columns = ["Ticker", "Price", "Dividend", "Pay Date", "Date Checked"]

    results_df = pd.DataFrame(results, columns=columns)
    save(results_df)
    
    