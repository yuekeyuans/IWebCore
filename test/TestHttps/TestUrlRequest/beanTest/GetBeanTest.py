import unittest
import requests

from common.TestHelper import genUrl

class GetBeanTest(unittest.TestCase):
    
    
    def test_bean_param_get(self):
        url = genUrl("/bean/getBean?name=h&age=13&home=oo&birthDate=2017-01-11")
        resp = requests.get(url);
        print(resp.text)
        self.assertEqual(resp.json(),  {"age":13,"birthDate":"2017-01-11","home":"oo", "id":0, "name":"h"})
    
    
    def test_bean_Url_get(self):
        url = genUrl("/bean/1/2/3/2017-02-21")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(resp.json(),  {"age":3,"birthDate":"2017-02-21","home":"2", "id":0, "name":"1"})
    
    def test_bean_header_get(self):
        url = genUrl("/bean/headerGet")
        headers = {"age":"100", "birthDate":"2017-09-01","home":"home","name":"name1"}
        resp = requests.get(url, headers=headers)
        print(resp.text)
        self.assertEqual(resp.json(), {"age":100,"birthDate":"2017-09-01","home":"home", "id":0, "name":"name1"})
        
    def test_bean_mixed_1(self):
        url = genUrl("/bean/mixed1/yuefei?home=xiaoqiaozhuang")
        headers = {"age": "100", "birthDate":"2017-09-01"}
        resp = requests.get(url, headers=headers)
        print(resp.text)
        self.assertEqual(resp.json(), {"age":100, "id":0, "birthDate":"2017-09-01","home":"xiaoqiaozhuang","name":"yuefei"})
