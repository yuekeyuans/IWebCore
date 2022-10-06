
import pytest
from util import wrapUrl
import requests

class TestClass:
    
    def test_addResponseCookie1(self):
        url = wrapUrl("cookie/addResponseCookie1")
        res = requests.get(url)
        assert res.cookies["hello"] == "world"
        assert res.text == "hello world"
        print(res.text)
        print(res.cookies["hello"])
        
    def test_hasResponseCookie(self):
        pass
    
    