import unittest

import requests
from requests.api import head

from common.TestHelper import genHeader, genUrl

class ByteArrayReturnTest(unittest.TestCase):

    def test_array1(self):
        url = genUrl("/array1")
        response = requests.get(url)
        
        self.assertEqual(response.text, "hello world1")
        self.assertEqual(response.status_code, 404)

    def test_array2(self):
        url = genUrl("/array2")
        response = requests.get(url)
        self.assertEqual(response.text, "hello world2")
        self.assertEqual(response.status_code, 200)

    # 一个文件
    def test_array3(self):
        url = genUrl("/array3")
        response = requests.get(url)
        self.assertEqual(response.text, "hello world3")

    def test_array4(self):
        url = genUrl("/array4")
        response = requests.get(url)
        self.assertEqual(response.text, "hello world4")
