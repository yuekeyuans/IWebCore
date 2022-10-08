
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
        
    def test_getReqestCookieValues(self):
        url = wrapUrl("cookie/getRequestCookieValues")
        res = requests.get(url, cookies= {"hello" : "world"})
        assert res.text == "hello world"
        
        res2 = requests.get(url, cookies = {"a": "n"})
        assert res2.text == "not exist"
    
    def test_getRequestCookie(self):
        url = wrapUrl("cookie/getRequestCookie")
        headers = {"Cookie" : "hello=world; hello=world"}
        res = requests.get(url, headers=headers)
        assert res.text == "exist error"
        
        headers = {"Cookie": "hello=world"}
        res=requests.get(url, headers=headers)
        assert res.text == "Set-Cookie: hello=world"
    
    def test_getRequestCookies(self):
        url = wrapUrl("cookie/getRequestCookies")
        headers = {"Cookie" : "hello=world; hello=yuekeyuan"}
        res = requests.get(url, headers=headers)
        assert res.text == "Set-Cookie: hello=world, Set-Cookie: hello=yuekeyuan"
    
    def test_getRequestCookieValue(self):
        url = wrapUrl("cookie/getRequestCookieValue")
        headers = {"Cookie" : "hello=world; hello=yuekeyuan"}
        res = requests.get(url, headers=headers)
        assert res.text == "cookie error"
        
        res = requests.get(url, cookies= {"hello" : "world"})
        assert res.text == "world"
        
    def test_getRequestCookieValues(self):
        pass
    
    def test_addResponseCookie1(self):
        url = wrapUrl("cookie/addResponseCookie1")
        res = requests.get(url)
        assert res.cookies["hello"] == "world"
        assert res.text == "hello world"
        print(res.text)
        print(res.cookies["hello"])
        
#-----------------------------------------------------------------
# response
#-----------------------------------------------------------------


