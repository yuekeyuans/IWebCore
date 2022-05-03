import requests
import unittest
import json
from common.TestHelper import genUrl, genHeader

class JsonReturTest(unittest.TestCase):
    
    def test_json1(self):
        url = genUrl("/json1")
        resp = requests.get(url)
        self.assertEqual(eval(resp.text), ["hello", "world"])
        
    def test_json2(self):
        url = genUrl("/json2")
        resp = requests.get(url)
        self.assertEqual(eval(resp.text) , {"hello": "world"})

    def test_json3(self):
        url = genUrl("/json3")
        resp = requests.get(url)
        self.assertEqual(eval(resp.text), {"hello" : "world"})
                
    # TODO: 这一系列的要被更改
    def test_json4(self):
        url = genUrl("/json4")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(eval(resp.text), {"age" : 100, "name" : "yuekeyuan"})
    
    
    @unittest.skip("这一个实例需要重新定义代码并测试")
    def test_json5(self):
        url = genUrl("/json5")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(eval(resp.text), [{"hello": {"name" : 1}},{"hello": {"name" : 1}}])
        
    def test_json6(self):
        url = genUrl("/json6")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(eval(resp.text), {"hello" : "world"})
    
    def test_json7(self):
        url = genUrl("/json7")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(eval(resp.text), ["hello", "world"])
    
    def test_json8(self):
        url = genUrl("/json8")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(eval(resp.text),  ["hello", "world"])
    
    
    def test_json9(self):
        url = genUrl("/json9")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(eval(resp.text),  {"hello": "world"})
    
    def test_json9(self):
        url = genUrl("/json9")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(eval(resp.text),  {"hello": "world"})
    