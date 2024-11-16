import requests
from ServerConfig import *

def test_controller():
    val = requests.get(serverAddress + "/ReturnTypeController/constData")
    print(val.text)

