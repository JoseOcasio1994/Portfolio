import logging
from pathlib import Path

dir = str(Path(__file__).parent)
logFile = f'{dir}\\log.log'

# Configure logging settings
logging.basicConfig(
    level = logging.INFO
)

def setup_logger(name):
    logger = logging.getLogger(name)
    logger.propagate = False
    
    f_handler = logging.FileHandler(logFile, mode='w')  # For file
    c_handler = logging.StreamHandler() # For console
    
    formatter = logging.Formatter(
        fmt='%(asctime)s - %(levelname)s - %(message)s',
        datefmt='%H:%M:%S'
    )
    
    f_handler.setFormatter(formatter)
    c_handler.setFormatter(formatter)
    
    logger.addHandler(f_handler)
    logger.addHandler(c_handler)
    
    return logger
