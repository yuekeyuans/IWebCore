
import pytest
from util import wrapUrl
import requests

class TestClass:
    
    # request
    def test_requestCookies(self):
        url = wrapUrl("cookie/requestCookies");
        res = requests.get(url, cookies={"hello" : "world"})
        assert res.json() == [{"hello" : "world"}]
        
        res2 = requests.get(url, cookies = {"hello" : "world", "a":"b"});
        assert res2.json() == [{"a":"b"}, {"hello" : "world"}];
    
    def test_hasRequestCookie(self):
        url = wrapUrl("cookie/hasRequestCookie")
        res = requests.get(url, cookies= {"hello": "world"});
        assert res.text == "exist"
        
        res2 = requests.get(url, cookies={"world":"12"})
        assert res2.text == "not exist"    
    
    def test_getRequestCookie(self):
        url = wrapUrl("cookie/getRequestCookieValues")
        res = requests.get(url, cookies= {"hello" : "world"})
        assert res.text == "hello world"
        
        res2 = requests.get(url, cookies = {"a": "n"})
        assert res2.text == "not exist"
    
    def test_addResponseCookie1(self):
        url = wrapUrl("cookie/addResponseCookie1")
        res = requests.get(url)
        assert res.cookies["hello"] == "world"
        assert res.text == "hello world"
        print(res.text)
        print(res.cookies["hello"])
        
