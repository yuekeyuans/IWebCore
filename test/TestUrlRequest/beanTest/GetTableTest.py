
import unittest
import requests
from common.TestHelper import genUrl

class GetTableTest(unittest.TestCase):
    
    def test_bean_param_get(self):
        url = genUrl("/tableController/getTable?name=yuekeyuan&birthDate=2017-01-11")
        resp = requests.get(url);
        print(resp.text)
        # self.assertEqual(resp.json(),  {"age":13,"birthDate":"2017-01-11","home":"oo", "id":0, "name":"h"})
    