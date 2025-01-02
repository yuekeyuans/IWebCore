from ServerConfig import *
import requests

def test_hello():
    val = requests.get(serverAddress + "/UrlController/helloWorld")
    print(val.status_code)
    print(val.text)
    print(val.headers)
    print(val.elapsed.total_seconds())
    print(val.elapsed.microseconds)
    assert val.status_code == 200 
    assert val.text == "hello"
