from ServerConfig import *
import requests
import pytest
from requests.exceptions import RequestException


def test_QString():
    val = requests.get(serverAddress + "/BasicArgument/irequest")
    print(val.status_code)
    print(val.text)
    print(val.headers)
    assert val.status_code == 200 
    assert val.text == "/BasicArgument/irequest"


def test_mulitpart():
    val = requests.post(serverAddress + "/BasicArgument/multipart", data={"name": "test"}, files={"file": open("ServerConfig.py", "rb")})
    print(val.text)
    print(val.status_code)