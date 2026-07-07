import pandas as pd
import sys
from sqlalchemy import create_engine
from config import Config
from utils import setup_logger
from pathlib import Path

dir = str(Path(__file__).parent)
weather_file = "transformed_weather_data.csv"
air_file = "transformed_air_data.csv"

# Initialize logger
logger = setup_logger(__name__)

def loadFile(file):
    try:
        df = pd.read_csv(f"{dir}\\{file}")
        
    except FileNotFoundError:
        logger.error(f"Error: {file} not found.")
        sys.exit(1)
        
    except pd.errors.EmptyDataError:
        logger.error(f"Error: {file} is empty.")
        sys.exit(1)
        
    except Exception as e:
        logger.error(f"Error reading file: {e}")
        sys.exit(1)
        
    return df

def create_database_engine():
    try:
        prefix = "postgresql+psycopg2://"
        url = Config.DATABASE_URL
        engine = create_engine(prefix + url)
        return engine
    except Exception as e:
        logger.error(f"Error creating database engine: {e}")
        sys.exit(1)

def load_data_to_postgresql(df, table_name, engine):

    try:
        df.to_sql(table_name, engine, if_exists='replace', index=False)
        logger.info(f"Data loaded into the table {table_name} successfully!")
    
    except Exception as e:
        logger.error(f"Error loading data to PostgreSQL: {e}")
        sys.exit(1)        

def main():
    # Load the transformed data from the CSV file
    weather_df = loadFile(weather_file)
    air_df = loadFile(air_file)

    # Load the data into PostgreSQL
    engine = create_database_engine()
    load_data_to_postgresql(weather_df, "weather", engine)
    load_data_to_postgresql(air_df, "air_quality", engine)

if __name__ == "__main__":
    main()