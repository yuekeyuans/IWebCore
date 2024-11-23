from ServerConfig import *
import requests

def test_QString():
    val = requests.get(serverAddress + "/ReturnTypeController/qstring")
    assert val.status_code == 200
    assert val.text == "QString"

def test_stdString():
    val = requests.get(serverAddress + "/ReturnTypeController/stdString")
    assert val.status_code == 200
    assert val.text == "stdString"

def test_ijson():
    val = requests.get(serverAddress + "/ReturnTypeController/ijson")
    assert val.status_code == 200
    assert val.json() == ["hello","world"]
    print(val.text)