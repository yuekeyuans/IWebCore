
import unittest
import requests
from common.TestHelper import genUrl

class StaticFileReturnTest(unittest.TestCase):
    
    # 请求 exe 文件
    def testGetImage1(self):
        url = genUrl("/staticFile/getFile1")
        resp = requests.get(url)
        self.assertEqual(resp.headers["Content-Type"], "application/octet-stream")
        self.assertEqual(len(resp.content), 2291200)
    
    # 请求图片文件
    def testGetImage2(self):
        url = genUrl("/staticFile/getFile2")
        resp = requests.get(url)
        self.assertEqual(resp.headers["Content-Type"], "image/png")
        self.assertNotEqual(len(resp.content), 0)
        
    def testGetImage3(self):
        url = genUrl("/staticFile/getFile3")
        resp = requests.get(url)
        self.assertEqual(resp.headers["Content-Type"], "application/octet-stream")
        self.assertEqual(len(resp.content), 0)      # 因为位置不对，所以这里数据为 0
        
        
    def testGetImage4(self):
        url = genUrl("/staticFile/getFile4")
        resp = requests.get(url)
        self.assertEqual(resp.headers["Content-Type"], "application/octet-stream")
        
        print(resp.headers["Content-Disposition"]);
        self.assertEqual(resp.headers["Content-Disposition"], "attachment;filename=TestHttpMapping.exe")
        self.assertNotEqual(len(resp.content), 0)
        
    def testGetImage5(self):
        url = genUrl("/staticFile/getFile5")
        resp = requests.get(url)
        self.assertEqual(resp.headers["Content-Type"], "application/octet-stream") 
        self.assertNotEqual(len(resp.content), 0)