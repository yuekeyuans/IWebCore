
import unittest
import requests

from common.TestHelper import genUrl


class BeanParameterControllerTest(unittest.TestCase):
    
    def test_setTestBean(self):
        url = genUrl("/testParamBean?age=10&name=yuefei")
        resp = requests.get(url)
        print(resp.text)
        
        
    def test_testBeanRef(self):
        url = genUrl("/testBeanRef?age=1&name=yuekeyua")
        resp = requests.get(url)
        print(resp.text)