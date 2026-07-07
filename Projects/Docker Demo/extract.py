import requests
import requests_cache
import openmeteo_requests
import sys
import pandas as pd
from retry_requests import retry
from config import Config
from utils import setup_logger
from pathlib import Path

dir = str(Path(__file__).parent)

# Initialize logger
logger = setup_logger(__name__)

def setup_meteo():
    # Setup the Open-Meteo API client with cache and retry on error
    cache_session = requests_cache.CachedSession('.cache', expire_after = 3600)
    retry_session = retry(cache_session, retries = 5, backoff_factor = 0.2)
    openmeteo = openmeteo_requests.Client(session = retry_session)
    
    return openmeteo

def fetch_weather_data(openmeteo: openmeteo_requests.Client, params):
    # API request URL
    url = f"https://historical-forecast-api.open-meteo.com/v1/forecast"

    final_params = {
        "latitude": params.get('latitude', Config.DEFAULT_LATITUDE),
        "longitude": params.get('longitude', Config.DEFAULT_LONGITUDE),
        "start_date": params.get('start_date', Config.DEFAULT_START),
        "end_date": params.get('end_date', Config.DEFAULT_END),
        "daily": params.get('daily', Config.DEFAULT_WEATHER_CONDITIONS)
    }

    try:
        # Make the API request
        responses = openmeteo.weather_api(url, params = final_params)
        response = responses[0]
        
        # Convert To JSON
        daily = response.Daily()
        daily_data = {
            "date": pd.date_range(
                start = pd.to_datetime(daily.Time(), unit = "s", utc = True),
                end =  pd.to_datetime(daily.TimeEnd(), unit = "s", utc = True),
                freq = pd.Timedelta(seconds = daily.Interval()),
                inclusive = "left"
                ),
            "temperature_c": daily.Variables(0).ValuesAsNumpy(),
            "humidity": daily.Variables(1).ValuesAsNumpy(),
            "wind_speed_kph": daily.Variables(2).ValuesAsNumpy(),
            "rel_temperature_c": daily.Variables(3).ValuesAsNumpy(),
            "precipitation_mm": daily.Variables(4).ValuesAsNumpy()
        }
        
        df = pd.DataFrame(data = daily_data)
        df.to_json(f"{dir}\\weather_data.json", indent=4)
        logger.info("Weather data saved to weather_data.json")

    except requests.exceptions.HTTPError as http_err:
        logger.error(f"HTTP error occurred: {http_err}")
        sys.exit(1)

    except Exception as err:
        logger.error(f"An error occurred: {err}")
        sys.exit(1)

def fetch_air_data(openmeteo: openmeteo_requests.Client, params):
    # API request URLh
    url = f"https://air-quality-api.open-meteo.com/v1/air-quality"

    final_params = {
        "latitude": params.get('latitude', Config.DEFAULT_LATITUDE),
        "longitude": params.get('longitude', Config.DEFAULT_LONGITUDE),
        "start_date": params.get('start_date', Config.DEFAULT_START),
        "end_date": params.get('end_date', Config.DEFAULT_END),
        "hourly": params.get('hourly', Config.DEFAULT_AIR_CONDITIONS),
    }

    try:
        # Make the API request
        responses = openmeteo.weather_api(url, params = final_params)
        response = responses[0]
        
        # Convert To JSON
        hourly = response.Hourly()
        hourly_data = {
            "date": pd.date_range(
                start = pd.to_datetime(hourly.Time(), unit = "s", utc = True),
                end =  pd.to_datetime(hourly.TimeEnd(), unit = "s", utc = True),
                freq = pd.Timedelta(seconds = hourly.Interval()),
                inclusive = "left"
            ),
            "pm10": hourly.Variables(0).ValuesAsNumpy(),
            "carbon_monoxide": hourly.Variables(1).ValuesAsNumpy(),
            "carbon_dioxide": hourly.Variables(2).ValuesAsNumpy(),
            "nitrogen_dioxide": hourly.Variables(3).ValuesAsNumpy(),
            "sulphur_dioxide": hourly.Variables(4).ValuesAsNumpy(),
            "dust": hourly.Variables(5).ValuesAsNumpy()
        }
        
        hourly_dataframe = pd.DataFrame(data = hourly_data)
        hourly_dataframe.to_json(f"{dir}\\air_quality_data.json", indent=4)
        logger.info("Air Quality data saved to air_quality_data.json")

    except requests.exceptions.HTTPError as http_err:
        logger.error(f"HTTP error occurred: {http_err}")
        sys.exit(1)

    except Exception as err:
        logger.error(f"An error occurred: {err}")
        sys.exit(1)

def main():
    meteo = setup_meteo()
    fetch_weather_data(meteo, {})
    fetch_air_data(meteo, {})
     
if __name__ == "__main__":
    main()