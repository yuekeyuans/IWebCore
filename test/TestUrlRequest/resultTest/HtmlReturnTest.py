import requests
import unittest
from common.TestHelper import genUrl

class HtmlReturnTest(unittest.TestCase):
    
    def test_1_htmlResponse_suffix(self):
        '''
        使用 _html 后缀返回
        '''
        url = genUrl("/html1")
        resp = requests.get(url)
        self.assertEqual(resp.text, "<h1>hello world</h1>")
        
    def test_2_htmlResponse_QString(self):
        '''
            use QString default
        '''
        url = genUrl("/html2")
        resp = requests.get(url)
        self.assertEqual(resp.text, "<h3>hello world</h3>")
        
    def test_3_QString(self):
        '''
        QString to response
        '''
        url = genUrl("/html3")
        resp = requests.get(url)
        self.assertEqual(resp.text, "<h2>hello world</h2>")
        
    def test_4_QString_prefix(self):
        url = genUrl("/html4")
        resp = requests.get(url)
        self.assertEqual(resp.text, "<h1>hello world</h1>")
    
    def test_5_voidReturn(self):
        url = genUrl("/html5")
        resp = requests.get(url)
        self.assertEqual(resp.text, "<h1>hello world</h1>")
    