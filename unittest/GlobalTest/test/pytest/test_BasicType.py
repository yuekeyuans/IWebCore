from ServerConfig import *
import requests

def test_QString():
    val = requests.get(serverAddress + "/BasicArgument/irequest")
    print(val.status_code)
    print(val.text)
    print(val.headers)
    assert val.status_code == 200 
    assert val.text == "/BasicArgument/irequest"