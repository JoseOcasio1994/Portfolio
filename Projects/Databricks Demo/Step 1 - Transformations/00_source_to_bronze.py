from pyspark.sql.functions import regexp_extract

catalog = "car_insurance_demo"
schema = "01_bronze"
base_path = f"/Volumes/{catalog}/{schema}/data_files"

path_training_images = f"{base_path}/training_imgs/"
path_images = f"{base_path}/images/"
path_metadata = f"{base_path}/metadata/"
path_autoloader = f"{base_path}/autoloader_metadata"
path_archive = f"{base_path}/archive"

# --- LOAD TRAINING IMAGES TO BRONZE --- 
@dlt.table(
    name=f"{catalog}.{schema}.training_images",
    comment="Raw accident image training data",
    table_properties={"quality": "bronze"}
)
def raw_training_images():
    return (
        spark.readStream.format("cloudFiles")
        .option("cloudFiles.format", "BINARYFILE")
        .load(path_training_images)
    )


# --- LOAD IMAGE METADATA TO BRONZE --- 
@dlt.table(
    name=f"{catalog}.{schema}.image_metadata",
    comment="Raw metadata for accident claim images",
    table_properties={"quality": "bronze"}
)
def raw_metadata():
    return (
        spark.readStream.format("cloudFiles")
        .option("cloudFiles.format", "csv")
        #.option("cloudFiles.schemaEvolutionMode", "addNewColumns") # DEFAULT
        #.option("cloudFiles.schemaEvolutionMode", "rescue")
        .load(path_metadata)
    )


# --- LOAD ACCIDENT IMAGES TO BRONZE --- 
@dlt.table(
    name=f"{catalog}.{schema}.images",
    comment="Raw data for accident claim images",
    table_properties={"quality": "bronze"}
)
def raw_images():
    archive_config = {
        "cloudFiles.cleanSource": "MOVE", # OR DELETE
        "cloudFiles.cleanSource.retentionDuration": "1 minute", # MOVE AFTER 1 MIN - FOR DELETE MIN. 7 DAYS
        "cloudFiles.cleanSource.moveDestination" : path_archive
    }

    image_df = (
        spark.readStream.format("cloudFiles")
        .option("cloudFiles.format", "BINARYFILE")
        .option("cloudFiles.schemaLocation", f"{path_autoloader}/schema")
        .options(**archive_config)
        .load(f"{path_images}")
    )

    image_df.writeStream.\
        option("checkpointLocation", f"{path_autoloader}/checkpoint")\
        .trigger(availableNow=True)\
        .toTable(f"{catalog}.{schema}.claim_images")

    return image_df