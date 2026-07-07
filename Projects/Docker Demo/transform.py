import pandas as pd
import json
import sys
from utils import setup_logger, clean_column_names
from pathlib import Path

dir = str(Path(__file__).parent)
weather_file = f"{dir}\\weather_data.json"
air_file = f"{dir}\\air_quality_data.json"

# Initialize logger
logger = setup_logger(__name__)

def load_data(file_name=weather_file):
    try:
        data = pd.read_json(file_name)
        return data
    
    except FileNotFoundError:
        logger.error(f"File {file_name} not found.")
        sys.exit(1)
        
    except json.JSONDecodeError:
        logger.error("Error decoding JSON from the file.")
        sys.exit(1)

def transform_weather_data(df: pd.DataFrame):
    try:
        # Select and rename columns as needed
        df = df[["date", "temperature_c", "rel_temperature_c", "humidity", "precipitation_mm", "wind_speed_kph"]]
        df.columns = ["date", "temperature_f", "feels_like_f", "humidity", "precipitation_in", "wind_speed_mph"]
        
        # Clean column names
        df = clean_column_names(df)
        
        # Convert data types
        df["date"] = pd.to_datetime(df["date"])
        df["temperature_f"] = pd.to_numeric(df["temperature_f"], errors='coerce')
        df["feels_like_f"] = pd.to_numeric(df["feels_like_f"], errors='coerce')
        df["humidity"] = pd.to_numeric(df["humidity"], errors='coerce')
        df["precipitation_in"] = pd.to_numeric(df["precipitation_in"], errors='coerce')
        df["wind_speed_mph"] = pd.to_numeric(df["wind_speed_mph"], errors='coerce')

        # Handle missing values
        df.fillna(df.mean(), inplace=True)  
        df.dropna(inplace=True)  # Drop any remaining missing values

        # Convert Metric Type
        df['temperature_f'] = df['temperature_f'].apply(lambda x: x * (9/5) + 32)
        df['feels_like_f'] = df['feels_like_f'].apply(lambda x: x * (9/5) + 32)
        df['precipitation_in'] = df['precipitation_in'].apply(lambda x: x / 25.4)
        df['wind_speed_mph'] = df['wind_speed_mph'].apply(lambda x: x / 1.609)
        
        return df.round(3)

    except KeyError as e:
        logger.error(f"Missing expected key in data: {e}")
        sys.exit(1)
        
    except Exception as e:
        logger.error(f"An error occurred during data transformation: {e}")
        sys.exit(1)

def transform_air_data(df: pd.DataFrame):
    try:
        # Select and rename columns as needed
        df = df[["date", "pm10", "carbon_monoxide", "carbon_dioxide", "nitrogen_dioxide", "sulphur_dioxide", "dust"]]
        
        # Clean column names
        df = clean_column_names(df)
        
        # Convert data types
        df["date"] = pd.to_datetime(df["date"])
        df["pm10"] = pd.to_numeric(df["pm10"], errors='coerce')
        df["carbon_monoxide"] = pd.to_numeric(df["carbon_monoxide"], errors='coerce')
        df["carbon_dioxide"] = pd.to_numeric(df["carbon_dioxide"], errors='coerce')
        df["nitrogen_dioxide"] = pd.to_numeric(df["nitrogen_dioxide"], errors='coerce')
        df["sulphur_dioxide"] = pd.to_numeric(df["sulphur_dioxide"], errors='coerce')
        df["dust"] = pd.to_numeric(df["dust"], errors='coerce')

        # Handle missing values
        df.fillna(df.mean(), inplace=True)  
        df.dropna(inplace=True)  # Drop any remaining missing values

        # Group By Day
        df = df.groupby(pd.Grouper(key='date', freq='D')).mean()
        
        return df.round(2)

    except KeyError as e:
        logger.error(f"Missing expected key in data: {e}")
        sys.exit(1)
        
    except Exception as e:
        logger.error(f"An error occurred during data transformation: {e}")
        sys.exit(1)

def save_data(df, file_name, index=False):
    try:
        df.to_csv(f"{dir}\\{file_name}", index=index)
        logger.info(f"Saved transformed data to {file_name}")
        
    except:
        logger.info(f"Failed to save toa to {dir}\\{file_name}")

def main():
    weather_data = load_data(weather_file)
    transformed_data = transform_weather_data(weather_data)
    save_data(transformed_data, "transformed_weather_data.csv")
    
    air_data = load_data(air_file)
    transformed_data = transform_air_data(air_data)
    save_data(transformed_data, "transformed_air_data.csv", True)

if __name__ == "__main__":
    main()