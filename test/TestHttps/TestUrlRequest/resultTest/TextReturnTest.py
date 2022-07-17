import requests
import unittest
from common.TestHelper import genUrl


class TextReturnTest(unittest.TestCase):
    
    def test_1(self):
        url = genUrl("/text1")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world")
        self.assertEqual(resp.headers["Content-Type"], "text/plain; charset=UTF-8")
        
        
    def test__1(self):
        url = genUrl("/text_1")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world")
        self.assertEqual(resp.headers["Content-Type"], "text/plain; charset=UTF-8")
        
    def test_2(self):
        url = genUrl("/text2")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world")
        self.assertEqual(resp.headers["Content-Type"], "text/plain; charset=UTF-8")
        
    def test_3(self):
        url = genUrl("/text3")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world")
        self.assertEqual(resp.headers["Content-Type"], "text/plain; charset=UTF-8")
    
    def test_4(self):
        url = genUrl("/text4")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world")
        self.assertEqual(resp.headers["Content-Type"], "text/plain; charset=UTF-8")
    
        
        