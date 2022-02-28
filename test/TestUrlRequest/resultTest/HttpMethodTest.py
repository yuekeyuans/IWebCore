import requests
import unittest
from common.TestHelper import genUrl

class HttpMethodTest(unittest.TestCase):
    
    def test_get(self):
        url = genUrl("/controller/fun")
        resp = requests.get(url)
        # print(resp.headers)
        self.assertEqual(resp.text, "hello world test get")
    
    def test_put(self):
        url = genUrl("/controller/fun")
        resp = requests.put(url)
        self.assertEqual(resp.text, "hello world test put")
    
    def test_Options(self):
        url = genUrl("/controller/fun")
        resp = requests.options(url)
        self.assertEqual(resp.headers["Allow"], "OPTIONS, GET, HEAD, PUT")
    
    def test_head(self):
        url = genUrl("/controller/fun")
        resp = requests.head(url)
        self.assertEqual(resp.text, "")