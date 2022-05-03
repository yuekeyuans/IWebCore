
import json
import unittest
import requests
from common.TestHelper import genUrl

class PostBeanTest(unittest.TestCase):
    
    def test_urlEncoded(self):
        url = genUrl("/beanPost/urlEncoded")
        payload ={"age":13,"birthDate":"2017-01-11","home":"oo", "name":"h"}
        resp = requests.post(url, data=payload)
        print(resp.text)
        self.assertEqual(resp.json(), {"age":13,"birthDate":"2017-01-11","home":"oo","id":0,"name":"h"})
        
        
    def test_jsonformat(self):
        url = genUrl("/beanPost/jsonvalue")
        payload = json.dumps({"age":130,"birthDate":"2017-01-11","home":"oo", "name":"h"})
        headers = {"Content-Type": "application/json"}
        resp = requests.post(url, data=payload, headers=headers)
        print(resp.text)
        self.assertEqual(resp.json(), {"age":130,"birthDate":"2017-01-11","home":"oo","id":0,"name":"h"})
        
    def test_postMultiPart(self):
        url = genUrl("/beanPost/multipart")
        payload = {"age":130,"birthDate":"2017-01-11","home":"oo", "name":"h"};
        resp = requests.post(url, files=payload)
        print(resp.text)
        self.assertEqual(resp.json(), {"age":130,"birthDate":"2017-01-11","home":"oo","id":0,"name":"h"})
    
    def test_post_mixed1(self):
        url = genUrl("/beanPost/mixed1/yuefei")
        payload= {"age":130,"birthDate":"2017-01-11","home":"oo"};
        resp = requests.post(url, files=payload)
        print(resp.text)
        self.assertEqual(resp.json(), {"age":130,"birthDate":"2017-01-11","home":"oo","id":0,"name":"yuefei"})
        
    def test_post_mixed2(self):
        url = genUrl("/beanPost/mixed2/yuefei")
        payload= {"age":130,"birthDate":"2017-01-11","home":"安徽省小乔庄"};
        resp = requests.post(url, files=payload)
        print(resp.text)
        self.assertEqual(resp.json(), {"age":130,"birthDate":"2017-01-11","home":"安徽省小乔庄","id":0,"name":"yuefei"})
        