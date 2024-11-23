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

def test_qbytearray():
    val = requests.get(serverAddress + "/ReturnTypeController/qbytearray")
    assert val.status_code == 200
    assert val.text == "QByteArray"
    print(val.text)
    print(val.headers)

def test_iByteArarryResponse():
    val = requests.get(serverAddress + "/ReturnTypeController/iByteArarryResponse")
    assert val.status_code == 200
    assert val.content == b"IByteArrayResponse"
    print(val.text)
    print(val.headers)

def test_iByteArrayResponse2():
    val = requests.get(serverAddress + "/ReturnTypeController/iByteArarryResponse2")
    assert val.status_code == 200
    assert val.content == b"iByteArarryResponse2"
    print(val.text)
    print(val.headers)

def test_QStringofByteArraySuffix():
    val = requests.get(serverAddress + "/ReturnTypeController/QStringofByteArraySuffix")
    assert val.status_code == 200
    assert val.text == "QStringofByteArraySuffix"
    print(val.text)
    print(val.headers)