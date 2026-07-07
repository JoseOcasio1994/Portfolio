FROM python:3.12-slim

# 2. Set the working directory in the container
WORKDIR /app

# 3. Copy the requirements file and install dependencies
# Doing this before copying the rest of the code optimizes builds via layer caching
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
RUN pip install psycopg2-binary

# 4. Copy the rest of the application code
COPY . .

ENV DATABASE_URL=postgres:postgres@localhost:5432/postgres

# 5. Specify the command to run on container start
CMD ["./entry.sh"]