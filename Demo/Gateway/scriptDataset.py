from azure.cosmos import exceptions, CosmosClient, PartitionKey

def add_to_db(message):
    # Initialize the Cosmos client
    endpoint = 'https://talkingchalksdb.documents.azure.com:443/'
    key = 'zcru6lLiwUS9599kwZ6PNRd53mwe5QOInfxyoeLYzBq953gFpgeKlqCQNj05Ok408OcSqIwwhzNHSLxeEG0bbQ=='

    #create cosmos client
    client = CosmosClient(endpoint, key)
    try:
        # Create a database
        database_name = 'TCDB'
        database = client.create_database_if_not_exists(id=database_name)
    except exceptions.CosmosResourceExistsError:
        pass

    # Create a container
    # Using a good partition key improves the performance of database operations.
    try:
        container_name = 'TCContainer'
        container = database.create_container_if_not_exists(
            id=container_name,
            partition_key=PartitionKey(path="/messages"),
            offer_throughput=400
        )
    except exceptions.CosmosResourceExistsError:
        pass

    container.create_item(body=message)
