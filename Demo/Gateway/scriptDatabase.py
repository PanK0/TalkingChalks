from azure.cosmos import exceptions, CosmosClient, PartitionKey

def add_to_db(message):
    # Initialize the Cosmos client
    endpoint = 'https://talkingdb.documents.azure.com:443/'
    key = 'nL5f0ZJPKLwxSaKigi2BNlk9eVn5jtZCeoFIg85TeCC73vkBCy2BctEY27YDMCh8B4UXg8Gq1GvrNBeltrNYgg=='

    #create cosmos client
    client = CosmosClient(endpoint, key)
    try:
        # Create a database
        database_name = 'tcdb'
        database = client.create_database_if_not_exists(id=database_name)
    except exceptions.CosmosResourceExistsError:
        pass

    # Create a container
    # Using a good partition key improves the performance of database operations.
    try:
        container_name = 'c1'
        container = database.create_container_if_not_exists(
            id=container_name,
            partition_key=PartitionKey(path="/messages"),
            offer_throughput=400
        )
    except exceptions.CosmosResourceExistsError:
        pass

    container.create_item(body=message)
