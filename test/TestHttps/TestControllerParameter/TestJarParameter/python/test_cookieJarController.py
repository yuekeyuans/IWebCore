
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
        url = wrapUrl("cookie/hasRequestCookie")
        res = requests.get(url, cookies= {"hello": "world"});
        assert res.text == "exist"
        
        res2 = requests.get(url, cookies={"world":"12"})
        assert res2.text == "not exist"    
    
    