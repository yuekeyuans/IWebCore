
import unittest
import requests
from common.TestHelper import genUrl

class ReqRespOperatorOverrideControllerTest(unittest.TestCase):
    
    def test_respOverride(self):
        url = genUrl("/testRespOverride")
        resp = requests.get(url)
        self.assertEqual(resp.text, "ginus")
        self.assertEqual(resp.headers["yuekeyuan"], "ginus")
        self.assertEqual(resp.headers["Content-Type"], "text/plain")
        self.assertEqual(resp.status_code, 200)
        
    def test_reqOveride(self):
        url = genUrl("/testReqOverride")
        headers = {"yuekeyuan" : "hello-world"}
        resp = requests.get(url, headers = headers)
        self.assertEqual(resp.text, "hello-world")
        
    def test_respInputOverride(self):
        url = genUrl("/testRespInputOverride")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world")
      
    def test_respInputOverrie(self):
        url = genUrl("/testRespInputRefOverride")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world")  
        