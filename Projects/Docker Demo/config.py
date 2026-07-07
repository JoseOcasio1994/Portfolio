import os
from dotenv import load_dotenv

# Load environment variables from .env file
load_dotenv()

class Config:
    DATABASE_URL = os.getenv("DATABASE_URL")

    DEFAULT_LATITUDE = 29.1872
    DEFAULT_LONGITUDE = -82.1401
    DEFAULT_START =  "2025-04-23"
    DEFAULT_END = "2025-05-07"
    DEFAULT_WEATHER_CONDITIONS = ["temperature_2m_mean", "relative_humidity_2m_mean", "wind_speed_10m_mean", "apparent_temperature_mean", "precipitation_sum"]
    DEFAULT_AIR_CONDITIONS = ["pm10", "carbon_monoxide", "carbon_dioxide", "nitrogen_dioxide", "sulphur_dioxide", "dust"]