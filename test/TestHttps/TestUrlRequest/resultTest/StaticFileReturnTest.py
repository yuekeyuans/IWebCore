
import unittest
import requests
from common.TestHelper import genUrl

class StaticFileReturnTest(unittest.TestCase):
    
    def testGetImage(self):
        url = genUrl("/staticFile/getFile2")
        resp = requests.get(url)
        # print(len(resp.content))
        self.assertEqual(len(resp.content), 17451212)
        # self.assertEqual(eval(resp.text), ["hello", "world"])