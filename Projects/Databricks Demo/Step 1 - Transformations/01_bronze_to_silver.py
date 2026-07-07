from pyspark.sql.functions import (
    col, to_date, date_format, trim, initcap, split, size, when, concat, lit, abs, to_timestamp, regexp_extract
)

catalog = "car_insurance_demo"
bronze_schema = "01_bronze"
silver_schema = "02_silver"

# --- CLEAN CLAIM ---
@dlt.table(
    name=f"{catalog}.{silver_schema}.claims",
    comment="Cleaned claims",
    table_properties={
        "quality":"silver"
    }
)
@dlt.expect_all_or_drop({
    "valid_claim_number": "claim_no IS NOT NULL",
    "valid_hour": "hour BETWEEN 0 AND 23"
})
def claim():
    df = dlt.readStream(f"{catalog}.{bronze_schema}.claims")
    return df


# --- CLEAN POLICIES ---
@dlt.table(
    name=f"{catalog}.{silver_schema}.policies",
    comment="Cleaned policies",
    table_properties={
        "quality":"silver"
    }
)
@dlt.expect_all_or_drop({
    "valid_policy_no": "policy_no IS NOT NULL"
})
def policy():
    df = dlt.readStream(f"{catalog}.{bronze_schema}.policies")
    return (
        df.withColumn("premium", abs("premium"))
    )


# --- CLEAN CUSTOMERS ---
@dlt.table(
    name=f"{catalog}.{silver_schema}.customers",
    comment="Cleaned customers",
    table_properties={
        "quality":"silver"
    }
)
@dlt.expect_all_or_drop({
    "valid_customer_id": "customer_id IS NOT NULL"
})
def customer():
    df = dlt.readStream(f"{catalog}.{bronze_schema}.customers")

    name_normalized = when(
        size(split(trim(col("name")), ",")) == 2,
        concat(
            initcap(trim(split(col("name"), ",").getItem(1))), lit(" "),
            initcap(trim(split(col("name"), ",").getItem(0)))
        )
    ).otherwise(initcap(trim(col("name"))))

    return (
        df
        .withColumn("date_of_birth", to_date("date_of_birth", "dd-MM-yyyy"))
        .withColumn("firstname", split(name_normalized, " ").getItem(0))
        .withColumn("lastname", split(name_normalized, " ").getItem(1))
        .withColumn("address", concat(col("BOROUGH"), lit(", "), col("ZIP_CODE")))
    )



# --- CLEAN TELEMATICS ---
@dlt.table(
    name=f"{catalog}.{silver_schema}.telematics",
    comment="Cleaned telematics",
    table_properties={
        "quality":"silver"
    }
)
@dlt.expect_all_or_drop({
    "valid_coordinates": "latitude BETWEEN -90 AND 90 AND longitude BETWEEN -180 AND 180"
})
def telematic():
    df = dlt.readStream(f"{catalog}.{bronze_schema}.telematics")

    return (
        df
        .withColumn("event_timestamp", to_timestamp(col("event_timestamp"), "yyyy-MM-dd HH:mm:ss"))
    )


# --- CLEAN CLAIM IMAGES ---
@dlt.table(
    name=f"{catalog}.{silver_schema}.claim_images",
    comment="Enriched claim images",
    table_properties={  "quality": "silver" }
)
def claim_images():
    df = dlt.readStream(f"{catalog}.{bronze_schema}.claim_images")
    return df.withColumn("image_name", regexp_extract(col("path"), r".*/(.*?.jpg)", 1))


# --- CLEAN TRAINING IMAGES ---
@dlt.table(
    name=f"{catalog}.{silver_schema}.training_images",
    comment="Enriched accident training images",
    table_properties={ "quality": "silver" }
)
def training_images():
    df = dlt.readStream(f"{catalog}.{bronze_schema}.training_images")
    return df.withColumn(
        "label",
        regexp_extract("path", r"/(\d+)-([a-zA-Z]+)(?: \(\d+\))?\.png$", 2)
    )

    