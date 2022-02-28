import json
import requests
import unittest
from common.TestHelper import genUrl

class PostTextParameterTest(unittest.TestCase):
    '''
    text 转各种内容
    '''
    
    def test_to_QString(self):
        url = genUrl("/postText1")
        payload = "hello world"
        headers = {
        'Content-Type': 'text/plain'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(response.text, payload)
        
        
        
    def test_to_int(self):
        url = genUrl("/postText2")
        payload = "1234"
        headers = {
        'Content-Type': 'text/plain'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(response.text, payload)
        
        
        
    def test_to_double(self):
        url = genUrl("/postText3")
        payload = "3.1415926"
        headers = {
        'Content-Type': 'text/plain'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(response.text, payload)
        
    def test_to_jsonObject(self):
        url = genUrl("/postText4")
        payload = json.dumps({"hello":"world"})
        headers = {
        'Content-Type': 'text/plain'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(json.loads(response.text), {"hello":"world"})
        
    def test_to_jsonValue(self):
        url = genUrl("/postText5")
        payload = "false"
        headers = {
            'Content-Type': 'text/plain'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        
        print(response.text)
        
        self.assertEqual(response.text, payload)
        
    def test_to_longlong(self):
        url = genUrl("/postText6")
        payload = "3242434523224234"
        headers = {
        'Content-Type': 'text/plain'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        print(response.text)
        self.assertEqual(response.text, payload)
        
        
        
        