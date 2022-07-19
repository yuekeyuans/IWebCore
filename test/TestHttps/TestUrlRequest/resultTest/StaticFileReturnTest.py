
import unittest
import requests
from common.TestHelper import genUrl

class StaticFileReturnTest(unittest.TestCase):
    
    # 请求 exe 文件
    def testGetImage(self):
        url = genUrl("/staticFile/getFile1")
        resp = requests.get(url)
        self.assertEqual(resp.headers["Content-Type"], "application/octet-stream")
        self.assertEqual(len(resp.content), 17451212)
    
    # 请求图片文件
    def testGetImage(self):
        url = genUrl("/staticFile/getFile2")
        resp = requests.get(url)
        self.assertEqual(resp.headers["Content-Type"], "image/png")
        self.assertNotEqual(len(resp.content), 0)