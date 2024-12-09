from ServerConfig import *
import requests

def test_QString():
    val = requests.get(serverAddress + "/ReturnTypeController/qstring")
    print(val.status_code)
    print(val.text)
    print(val.headers)
    print(val.elapsed.total_seconds())
    print(val.elapsed.microseconds)
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
    assert val.headers["Content-Type"]  == "application/json; charset=UTF-8"
    print(val.text)
    print(val.headers)

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


def test_testInvalid():
    val = requests.get(serverAddress + "/ReturnTypeController/testInvalid")
    assert val.status_code == 400
    print(val.status_code)
    print(val.text)
    print(val.headers)

def test_bean():
    val = requests.get(serverAddress + "/ReturnTypeController/getBean")
    assert val.status_code == 200
    assert val.json() == {"index":100,"name":"yuekeyuan"}
    assert val.headers["Content-Type"]  == "application/json; charset=UTF-8"
    print(val.text)
    print(val.headers)

def test_getBeanList():
    val = requests.get(serverAddress + "/ReturnTypeController/getBeanList")
    assert val.status_code == 200
    assert val.json() == [{"index":100,"name":"yuekeyuan"},{"index":100,"name":"yuekeyuan"}]
    assert val.headers["Content-Type"]  == "application/json; charset=UTF-8"
    print(val.text)
    print(val.headers)


def test_fileResponse():
    val = requests.get(serverAddress + "/ReturnTypeController/fileResponse")
    assert val.text.__contains__("http")
    print(val.text)
    print(val.headers)
    print(val.status_code)

def test_redirectResponse():
    val = requests.get(serverAddress + "/ReturnTypeController/redirectResponse", allow_redirects=False)
    assert val.status_code == 302
    assert val.headers["Location"] == "https://www.baidu.com"
    print(val.text)
    print(val.headers)
    print(val.status_code)

def test_cookieTest():
    val = requests.get(serverAddress + "/ReturnTypeController/cookieTest")
    assert val.status_code == 200
    assert val.text == "hello world"
    assert val.headers["Content-Type"]  == "text/plain; charset=UTF-8"
    assert val.cookies["name"] == "yuekeyuan"
    assert val.headers["hello"] == "world"
    print(val.text)
    print(val.headers)
    print(val.cookies)