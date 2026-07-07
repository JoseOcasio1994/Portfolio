import pandas as pd
import random
from time import sleep
from pathlib import Path
from scrapers import BestBuyScraper, GameStopScraper, AmazonScraper, buildDriver
from utils import setup_logger

logger = setup_logger(__name__)
dir = str(Path(__file__).parent)
in_file = dir + '\\games.json'
out_file = dir + '\\game_prices.csv'

scrapersDict = {}

def getCompany(url):
    
    if (url is None or url == ""):
        return "NONE"
    
    elif ("bestbuy" in url):
        return "Best Buy"
    
    elif ("gamestop" in url):
        return "Game Stop"
    
    elif ("amazon" in url):
        return "Amazon"
    
    return "Other"

def get_price(url, company):
    
    scraper = scrapersDict[company]
    price = scraper.getPrice(url)
    logger.info(f"Price = {price}")
    
    return price

def save(results):
    try:
        logger.info(f"Saving To {out_file}")
        
        columns= ["Name", "System", "Website", "Price"]
        results_df = pd.DataFrame(results, columns=columns)
        sorted = results_df.sort_values(by=['System', 'Name', 'Price'], ascending=[True, True, False])
        
        sorted.to_csv(out_file)
        
    except Exception as e:
        logger.error(e)

if __name__ == "__main__":
    
    # Initialize Web Driver
    driver = buildDriver()
    scrapersDict["Best Buy"] = BestBuyScraper(driver)
    scrapersDict["Game Stop"] = GameStopScraper(driver)
    scrapersDict["Amazon"] = AmazonScraper(driver)
    
    # Get List Of Games
    df = pd.read_json(in_file)
    
    games = df.columns.tolist()
    platforms = df.loc['platform']
    links = df.loc['links']

    results = []

    # Loop Through Games And Get Price
    # Currently Only Best Buy, Gamestop, and Amazon
    for index, game in enumerate(games):
        system = platforms.iloc[index]
        
        for link in links.iloc[index]:
            company = getCompany(link)
            
            if (company in scrapersDict.keys()):
                logger.info(f"Getting Price For {system} - {game} ({company}) ...")
                
                price = get_price(link, company)
                row = [game, system, company, price]
                results.append(row)
                
                sleep(random.uniform(1, 3)) # To Try And Get Past Bot Detection
    
    # Quit Driver And Save Results
    driver.quit()
    save(results)
        