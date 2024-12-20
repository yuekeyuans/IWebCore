import logging
from ServerConfig import *
import requests
import http.client as httplib
import pytest
from requests.exceptions import RequestException

# logging.basicConfig(level=logging.DEBUG)
# httplib.HTTPConnection.debuglevel = 1

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
