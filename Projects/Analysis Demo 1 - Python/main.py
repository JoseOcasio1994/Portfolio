import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

dir = str(Path(__file__).parent)

def calcBoundaries(df, column):
    
    # Calculate Bounds For Outliers Using Interquartile Range (IQR)
    Q1 = df[column].quantile(0.25)
    Q3 = df[column].quantile(0.75)

    IQR = Q3 - Q1

    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR
    
    return lower_bound, upper_bound

def InitClean():
    
    # Load Listing DF
    df_listings = pd.read_csv(f'{dir}\\listings.csv')

    # Remove Unneccesary Columns
    toDrop = ['neighbourhood_group', 'latitude', 'longitude', 'license', 'last_review']
    df_listings = df_listings.drop(columns=toDrop)

    # Remove Missing Price
    df_listings = df_listings.dropna(subset=['price'])

    # Remove Outliers
    outlierColumns = ['price', 'minimum_nights']
    clean_df = df_listings
    for c in outlierColumns:
        lower, upper = calcBoundaries(clean_df, c)
        clean_df = clean_df[
            (clean_df[c] >= lower) & 
            (clean_df[c] <= upper)
        ]
    
    # Load Reviews DF
    df_reviews = pd.read_csv(f'{dir}\\reviews.csv')
    
    # Merge With Cleaned Listings DF To Get Neighbourhood
    df_reviews = df_reviews.merge(clean_df, on='listing_id', how='inner')
    clean_reviews = df_reviews[['listing_id', 'neighbourhood', 'date']]
    clean_reviews = clean_reviews.rename(columns={"date": "review_date"})
    
    # Remove Reviews Before 2020
    clean_reviews['review_date'] = pd.to_datetime(clean_reviews['review_date'])
    clean_reviews = clean_reviews[clean_reviews['review_date'].dt.year >= 2020]
    
    return clean_df, clean_reviews

def priceAnalysis(df):
    
    # Calculate Price Average And Median
    avgPrice = round(df['price'].mean(), 2)
    medianPrice = df['price'].median()

    print(f'Average Price: {avgPrice}')
    print(f'Median Price: {medianPrice}')
    
    # Group DF By Minimum Nights
    byNights = df.groupby('minimum_nights', as_index=False)\
                    .agg(avgPrice=('price', 'mean'))\
                    .round(2)
    byNights = byNights.sort_values(by='minimum_nights', ascending=False)
    print(byNights)

def roomAnalysis(df):
    # Group DF By Room Types
    byRoom = df.groupby('room_type', as_index=False)\
                .agg(room_count=('room_type', 'count'))
    byRoom = byRoom.sort_values(by='room_count', ascending=False)
    ax = byRoom.plot(kind='bar', x='room_type', y='room_count', title='Listings Per Room Type',
                    legend=False, rot=0, ylabel='Listing Count', xlabel='Room Type')

    # Add Label Above Bars
    for container in ax.containers:
        ax.bar_label(container, padding=3)

    plt.tight_layout()
    plt.show()

def locationAnalysis(df):
    # Group DF By Neighbourhood
    byHood = df.groupby('neighbourhood', as_index=False)\
                    .agg(hood_count=('neighbourhood', 'count'),
                         avgPrice=('price', 'mean')).round(2)
    byHood = byHood.sort_values(by='hood_count', ascending=False)
    byPrice = byHood.sort_values(by='avgPrice', ascending=False)
    
    # Graph 1 - Listings Per Area
    ax1 = byHood.plot(kind='bar', title='Listings Per Area', x='neighbourhood', y='hood_count', 
                        legend=False, rot=0, ylabel='Listing Count', xlabel='Neighbourhood Code',
                        ylim=(0, 750))

    # Graph 2 - Average Price Per Area
    ax2 = byPrice.plot(kind='bar', title='Average Price Per Area', x='neighbourhood', y='avgPrice', 
                        legend=False, rot=0, ylabel='Average Price', xlabel='Neighbourhood Code',
                        ylim=(0, 250))

    # Add Label Above Bars
    for container in ax1.containers:
        ax1.bar_label(container, padding=3)
        
    for container in ax2.containers:
        ax2.bar_label(container, padding=3)

    plt.tight_layout()
    plt.show()
 
def reviewAnalysis(reviews):
    # Reviews By Months
    byMonths = reviews.groupby(reviews['review_date'].dt.strftime('%B'))["listing_id"].count()
    month_order = ['January', 'February', 'March', 'April', 'May', 'June', 
               'July', 'August', 'September', 'October', 'November', 'December']
    byMonths = byMonths.reindex(month_order).dropna()
    
    plt.figure(1)
    byMonths.plot(kind="line", marker="o", title="Monthly Review Count", 
                  ylim=(13000,24000), ylabel="Total Reviews", xlabel="Month",)
    
    
    # Reviews By Year
    byYear = reviews.groupby(pd.Grouper(key="review_date", freq="ME"))["listing_id"].count()
    
    plt.figure(2)
    byYear.plot(kind="line", marker="o", title="Yearly Review Count", 
                  ylabel="Total Reviews", xlabel="Month")
    
    
    # Reviews By Neighbourhood
    byHood= reviews.groupby('neighbourhood', as_index=False).agg(reviews=('listing_id','count'))
    byHood = byHood.sort_values(by='reviews', ascending=False)
    
    ax = byHood.plot(kind="bar", title="Review Count Per Neighbourhood", x='neighbourhood',
                  y='reviews',ylabel="Total Reviews", xlabel="Neighbourhood ID",
                  legend=False, ylim=(0,70000))
    
    for container in ax.containers:
        ax.bar_label(container, padding=3)
    
    plt.tight_layout()
    plt.show()
    
def hostAnalysis(df):
    # Listings Per Host
    mostListings = df.groupby(['host_id','host_name'],as_index=False)\
        .agg(listings=('calculated_host_listings_count', 'count'),
             avgPrice=('price','mean'))
    mostListings = mostListings.sort_values(by='avgPrice', ascending=False)
    print(mostListings)
  
df, reviews = InitClean()
priceAnalysis(df)
roomAnalysis(df)
locationAnalysis(df)
reviewAnalysis(reviews)
hostAnalysis(df)