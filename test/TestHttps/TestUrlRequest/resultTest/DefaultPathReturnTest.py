import requests
import unittest
from common.TestHelper import genUrl

class DefaultPathReturnTest(unittest.TestCase):
    '''
    使用默认path 返回
    '''
    
    def test_get(self):
        url = genUrl("/defaultPath")
        resp = requests.get(url)
        self.assertEqual(resp.text, "hello world get")
        


    def test_put(self):
        url = genUrl("/defaultPath")
        resp = requests.put(url)
        self.assertEqual(resp.text, "hello world put")
        
        
        
    def test_post(self):
        url = genUrl("/defaultPath")
        resp = requests.post(url)
        self.assertEqual(resp.text, "hello world post")
        
        
    def test_delete(self):
        url = genUrl("/defaultPath")
        resp = requests.delete(url)
        self.assertEqual(resp.text, "hello world delete")
        