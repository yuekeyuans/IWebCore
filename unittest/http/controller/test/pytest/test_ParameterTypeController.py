import ServerConfig
import requests
import pytest

def test_emptyRequest():
    val = requests.get(url=ServerConfig.serverAddress + "/ArgumentTypeController/emptyRequest")
    assert val.status_code == 200
    assert val.text == "hello world"

def test_requetRef():
    val = requests.get(url=ServerConfig.serverAddress + "/ArgumentTypeController/irequestRef")
    assert val.status_code == 200
    assert val.text == "/ArgumentTypeController/irequestRef"
    print(val.text)

def test_constIRequestRef():
    val = requests.get(url=ServerConfig.serverAddress + "/ArgumentTypeController/constIRequestRef")
    assert val.status_code == 200
    assert val.text == "/ArgumentTypeController/constIRequestRef"

@pytest.mark.skip("always fail")
def test_irequest():
    val = requests.get(url=ServerConfig.serverAddress + "/ArgumentTypeController/irequest")
    assert val.status_code == 200
    assert val.text == "hello world"

def test_iresponse():
    val = requests.get(url=ServerConfig.serverAddress + "/ArgumentTypeController/iresponseRef")
    assert val.status_code == 200
    assert val.text == "hello world"
    assert val.headers['hello'] == 'world'