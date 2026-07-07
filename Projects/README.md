
## Overview ##

This portfolio contains a handful of random projects I have worked on over the past year (2025-2026) after getting laid off from my 5 year remote SWE position at a Fintech company. Most of these are incomplete, and are more of a "get-an-idea" type of demonstration. I've spent the past year trying to learn whatever I can to try to expand my options for possible programming-related jobs without spending money. This includes things like back-end development, front-end development, CI/CD, and Data Engineering.

## Game Scraper ##

Made in Python, this tool reads a json that contains a list of games, their platform, and URLs for Best Buy / Gamestop / Amazon and scrapes those sites for their prices so I can determine which website I can get the best deal (for physical copies). The results are stored in a csv file. This is incomplete as there are issues with Anti-Bot protections that eventually stop the program from getting data.

## Stock Scraper ##

Same as above, this tool is made in Python. It reads a json file to get a list of stock codes and uses stockanalysis.com/etf/{name}/dividend/ to get the stock price and most recent dividend payout, and saves it to a csv.

## Docker Demo ##

A simple Docker demonstration where I have a python file do ETL work on a weather API and saves it to a postgres database, where both run in separate docker containers.

## Analysis Demo 1 - Python ##

Data engineering is my most recent self-training subject. This one uses python's pandas and matplotlib libraries to analyze AirBnB data, such as price analysis based on location, minimum nights stayed, or room type.

## Analysis Demo 2 - PowerBI ##

Same as above, but I use PowerBI to analyze data about medical insurance claims.

## Databricks Demo ##

A much bigger Data Engineering project than the previous 2 where I do the full ETL and Data Analysis process on Auto Insurance claims. This includes:
    1) uploading data
    2) transforming data using the Medallion Bronze/Silver/Gold process
    3) converting that to a pipeline and creating a job that automates updating if more data is added
        a) the transformation part of the pipeline is complete, but data ingestion is incomplete as I don't have a cloud storage (such as Azure or AWS S3) to practice pulling data from. The data is just manually uploaded csv files that get turned into database tables.
    4) created a ML algorithm to classify the severity of damages based on an image provided, and see if it matches what the customer classified it as (Minor vs Major vs Total Loss)
    5) A dashboard to analyze the data and provide insights such as accident types, money paid out, and customer demographics.

## Full Stack Practice ##

One of my first big projects during the past year where I try to teach myself Full-Stack Development, where I use Best Buy's website as a model of what kind of website and API to design. Here is the tech stack I messed with in this project, with bold being my preferred choices:

    () Database: **PostgreSql**
    () Server: **.Net C#**, **Java Springboot**, Django, ExpressJs, NestJs
    () Client: **Angular**, Next React, Vue

## Microservice Demo ##

As the name suggets, this is a demo project where I learn to create microservices. It is created using Java Spring Boot, and features components such as Eureka, API Gateway, KeyCloak, Kafka, Prometheus, Grafana, and Docker. I used Postman to test API calls and PostGreSql as the database.