from ServerConfig import *
import requests

def test_QString():
    val = requests.get(serverAddress + "/ReturnTypeController/qstring")
    assert val.status_code == 200
    assert val.text == "hello world"