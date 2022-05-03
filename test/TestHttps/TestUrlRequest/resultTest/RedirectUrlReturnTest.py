# coding=utf-8
import unittest
import requests
from urllib.parse import urlencode
from common.TestHelper import genUrl

class RedirectUrlReturnTest(unittest.TestCase):
    
    def test_redirect1(self):
        url = genUrl("/redirect1")
        resp = requests.get(url, allow_redirects=False)
        self.assertTrue(resp.headers["Location"] == "http://www.baidu.com")
        
    def test_redirect2(self):
        url = genUrl("/redirect2")
        resp = requests.get(url, allow_redirects=False)
        self.assertTrue(resp.headers["Location"] == "http://www.baidu.com")
        
    def test_redirect3(self):
        url = genUrl("/redirect3")
        resp = requests.get(url, allow_redirects=False)
        location = "http://www.baidu.com/s?" + urlencode({"word" : "约为"}, encoding="UTF-8")
        self.assertTrue(resp.headers["Location"] == location)
        
    def test_redirect4(self):
        url = genUrl("/redirect4")
        resp = requests.get(url, allow_redirects=False)
        self.assertTrue(resp.headers["Location"] == "http://www.baidu.com")
        
    def test_redirect5(self):
        url = genUrl("/redirect5")
        resp = requests.get(url, allow_redirects=False)
        self.assertTrue(resp.headers["Location"] == "http://www.baidu.com")
        