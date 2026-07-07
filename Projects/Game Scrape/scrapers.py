from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from math import ceil
from time import sleep
from utils import setup_logger

logger = setup_logger(__name__)

def buildDriver():
    options = Options()
    options.add_experimental_option("excludeSwitches", ["enable-automation"])
    options.add_experimental_option("useAutomationExtension", False)
    options.add_argument('--no-sandbox')
    options.add_argument('--disable-blink-features=AutomationControlled')
    options.add_argument("user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/140.0.0.0 Safari/537.36")
    options.add_argument("--headless=new") 
    options.add_argument("--disable-gpu")
    options.add_argument("--incognito")
    
    driver = webdriver.Chrome(options=options)
    driver.implicitly_wait(2)
    
    return driver

class BaseScraper:
    
    def __init__(self, driver):
        self._driver = driver
    
    def getPrice(self, url):
        
        try:
            price = self._getPrice(url)
                
        except Exception as e:
            logger.error(f"ERROR: {str(e)}")
            price = None
            
        return price
    
    def _getPrice(self, url):
        return None
    
class BestBuyScraper(BaseScraper):
    
    def _getPrice(self, url):
        price = 0
        self._driver.get(url)
        
        selector1 = "[data-component-name='LargePrice']"
        el1 = self._driver.find_elements(By.CSS_SELECTOR, selector1)
        el1 = el1[0] if len(el1) > 0 else None
        
        if (el1 is None): return None
        
        selector2 = "[elementtiming='price_et']"
        el2 = el1.find_elements(By.CSS_SELECTOR, selector2)
        el2 = el2[0] if len(el2) > 0 else None
        
        price = el2.text.replace("$", "") if el2 is not None else 0
            
        return ceil(float(price))
    
class GameStopScraper(BaseScraper):
    
    def _getPrice(self, url):
        price = 0
        self._driver.get(url)
        
        selector_new = "[class*='condition-label new']"
        selector_pro = "[class*='condition-label pre-owned']"
        selector_pre = "[class*='actual-price']"
        
        price_new_el = self._driver.find_elements(By.CSS_SELECTOR, selector_new)
        price_pro_el = self._driver.find_elements(By.CSS_SELECTOR, selector_pro)
        price_pre_el = self._driver.find_elements(By.CSS_SELECTOR, selector_pre)
        
        price_new_el = price_new_el[0] if len(price_new_el) > 0 else None
        price_pro_el = price_pro_el[0] if len(price_pro_el) > 0 else None
        price_pre_el = price_pre_el[0] if len(price_pre_el) > 0 else None
        
        price_new = price_new_el.text[4:].replace("$", "") if price_new_el is not None else '0'
        price_pro = price_pro_el.text[10:].replace("$", "") if price_pro_el is not None else '0'
        price_pre = price_pre_el.text.replace("$", "") if price_pre_el is not None else '0'
        
        if(price_new[0] == '+'): # Pre Owned (With Pro Price) Selected When New Exists
            price = float(price_new[1:]) + float(price_pro)
            
        elif(price_new != "0"): # New Selected
            price = float(price_new)
            
        else: # Pre Owned Only Choice (Without Pro Price)
            price = float(price_pre)
            
        return ceil(price)
    
class AmazonScraper(BaseScraper):
    
    def _getPrice(self, url):
        price = 0
        self._driver.get(url)
        
        submit_selector = "[class*='a-button-text']"
        submit = self._driver.find_elements(By.CSS_SELECTOR, submit_selector)
        
        # Check For "Continue Shopping" Pop Up
        if (len(submit) > 0 and submit[0].text == "Continue shopping"):
            logger.info("Clicking 'Continue shopping' ")
            submit[0].click()
            sleep(1)
            
        selector = "[class*='apex-core-price-identifier']"
        price_el = self._driver.find_elements(By.CSS_SELECTOR, selector)
        price_el = price_el[0] if len(price_el) > 0 else None
        
        price = price_el.text.replace("$", "") if price_el is not None else 0
        price = price.replace("\n", ".") if price is not None else 0
        
        return ceil(float(price))