import logging
from ServerConfig import *
import requests
import http.client as httplib
import pytest
from requests.exceptions import RequestException

logging.basicConfig(level=logging.DEBUG)
httplib.HTTPConnection.debuglevel = 1

def test_QString():
    val = requests.get(serverAddress + "/BasicArgument/irequest")
    print(val.status_code)
    print(val.text)
    print(val.headers)
    assert val.status_code == 200 
    assert val.text == "/BasicArgument/irequest"

def test_mulitpart():
    val = requests.post(serverAddress + "/BasicArgument/multipart", data={"name": "test"}, files={"file": open("ServerConfig.py", "rb")})
    assert val.status_code == 200
    assert val.text == open("ServerConfig.py").read()
    print(val.text)
    print(val.status_code)

def test_cookiePart():
    val = requests.get(serverAddress + "/BasicArgument/cookiePart", cookies={"name": "cookie"})
    assert val.status_code == 200
    assert val.text == "cookie"
    print(val.text)
    print(val.status_code)  

def test_cookieString():
    val = requests.get(serverAddress + "/BasicArgument/cookieString", cookies={"name": "cookie"})
    assert val.status_code == 200
    assert val.text == "cookie"
    print(val.text)
    print(val.status_code)

def test_cookiesStrings():
    session = requests.Session()

    # Set cookies in the session
    session.cookies.set('names', 'cookie_value1')
    session.cookies.set('names', 'cookie_value2')
    val = session.get(serverAddress + "/BasicArgument/cookiesString")
    assert val.status_code == 200
    # assert val.text == "cookie; name1=cookie1"
    print(val.text)
    print(val.status_code)

def test_cookiePartEmpty():
    val = requests.get(serverAddress + "/BasicArgument/cookiePart", cookies={"name1": "cookie"})
    assert val.status_code == 500
    # assert val.text != "cookie"
    print(val.text)
    print(val.status_code)  

def test_headerType():
    val = requests.get(serverAddress + "/BasicArgument/headerType", headers={"MyHeader": "Yuekeyuan"})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.text == "Yuekeyuan"


def test_headerTypeInt():
    val = requests.get(serverAddress + "/BasicArgument/headerTypeInt", headers={"MyInt": "123"})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.text == "123"

def test_BodyType():
    val = requests.post(serverAddress + "/BasicArgument/bodyType", data={"name": "test"})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.text == "name=test"


def test_bodyJson():
    val = requests.post(serverAddress + "/BasicArgument/bodyJson", json={"name": "test"})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.json()["name"] == "test"


def test_payloadJson():
    val = requests.post(serverAddress + "/BasicArgument/payloadJson", json={"name": "test"})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.json()["name"] == "test"

def test_innerJson():
    val = requests.post(serverAddress + "/BasicArgument/innerJson", json={"name": "test", "data": {"name": "inner"}})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.text == '{"name":"inner"}'
    
def test_formData():
    val = requests.post(serverAddress + "/BasicArgument/formData", data={"name": "test", "data": "inner"})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.text == "test"

def test_formData2():
    val = requests.post(serverAddress + "/BasicArgument/formData", data={"name": "中文", "data": "inner"})
    print(val.text)
    print(val.status_code)  
    assert val.status_code == 200
    assert val.text == "中文"


def test_beanData():
    val = requests.post(serverAddress + "/BasicArgument/beanData", json={"index": 102, "name": "yueqichu"})
    print(val.text)
    print(val.status_code)
    assert val.text == '{"index":102,"name":"yueqichu"}'
    assert val.status_code == 200

def test_beanData2():
    val = requests.post(serverAddress + "/BasicArgument/beanData", json=[{"index": 102, "name": "yueqichu"},{"index": 103, "name": "yuekeyuan"}])
    print(val.text)
    print(val.status_code)
    # assert val.text == '{"index":102,"name":"yueqichu"}'
    assert val.status_code == 500

def test_beanDataQList():
    val = requests.post(serverAddress + "/BasicArgument/beanDatas", json=[{"index": 102, "name": "yueqichu"},{"index": 103, "name": "yuekeyuan"}])
    print(val.text)
    print(val.status_code)
    assert val.json() == [{"index": 102, "name": "yueqichu"}, {"index": 103, "name": "yuekeyuan"}]
    assert val.status_code == 200

def test_beanDataStdList():
    val = requests.post(serverAddress + "/BasicArgument/beanDataStdList", json=[{"index": 102, "name": "yueqichu"},{"index": 103, "name": "yuekeyuan"}])
    print(val.text)
    print(val.status_code)
    assert val.json() == [{"index": 102, "name": "yueqichu"}, {"index": 103, "name": "yuekeyuan"}]
    assert val.status_code == 200

def test_beanDataQMap():
    val = requests.post(serverAddress + "/BasicArgument/beanDataQMap", json={
        "fei" :{"index": 102, "name": "yueqichu"}, "yue": {"index": 103, "name": "yuekeyuan"}})
    print(val.text)
    print(val.status_code)
    assert val.json() == {"fei":{"index":102,"name":"yueqichu"},"yue":{"index":103,"name":"yuekeyuan"}}
    assert val.status_code == 200

def test_beanDataQMapQString():
    val = requests.post(serverAddress + "/BasicArgument/beanDataQMapQString", json={
        "fei" :{"index": 102, "name": "yueqichu"}, "yue": {"index": 103, "name": "yuekeyuan"}})
    print(val.text)
    print(val.status_code)
    assert val.json() == {"fei":{"index":102,"name":"yueqichu"},"yue":{"index":103,"name":"yuekeyuan"}}
    assert val.status_code == 200

def test_beanDataQMapStdString():
    val = requests.post(serverAddress + "/BasicArgument/beanDataQMapStdString", json={
        "fei" :{"index": 102, "name": "yueqichu"}, "yue": {"index": 103, "name": "yuekeyuan"}})
    print(val.text)
    print(val.status_code)
    assert val.json() == {"fei":{"index":102,"name":"yueqichu"},"yue":{"index":103,"name":"yuekeyuan"}}
    assert val.status_code == 200

def test_beanDataStdMap():
    val = requests.post(serverAddress + "/BasicArgument/beanDataStdMap", json={
        "fei" :{"index": 102, "name": "yueqichu"}, "yue": {"index": 103, "name": "yuekeyuan"}})
    print(val.text)
    print(val.status_code)
    assert val.json() == {"fei":{"index":102,"name":"yueqichu"},"yue":{"index":103,"name":"yuekeyuan"}}
    assert val.status_code == 200

def test_beanDataStdMapQString():
    val = requests.post(serverAddress + "/BasicArgument/beanDataStdMapQString", json={
        "fei" :{"index": 102, "name": "yueqichu"}, "yue": {"index": 103, "name": "yuekeyuan"}})
    print(val.text)
    print(val.status_code)
    assert val.json() == {"fei":{"index":102,"name":"yueqichu"},"yue":{"index":103,"name":"yuekeyuan"}}
    assert val.status_code == 200

def test_beanDataStdMapStdString():
    val = requests.post(serverAddress + "/BasicArgument/beanDataStdMapStdString", json={
        "fei" :{"index": 102, "name": "yueqichu"}, "yue": {"index": 103, "name": "yuekeyuan"}})
    print(val.text)
    print(val.status_code)
    assert val.json() == {"fei":{"index":102,"name":"yueqichu"},"yue":{"index":103,"name":"yuekeyuan"}}
    assert val.status_code == 200