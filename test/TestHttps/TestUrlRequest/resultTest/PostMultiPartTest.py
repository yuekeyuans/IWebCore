import requests
import unittest
import os
from common.TestHelper import genUrl


class PostMultiPartTest(unittest.TestCase):
    
    def test_multipart_parameter(self):
        url = genUrl("/multipart1")
        body = {"name" : "yuekeyuan"}
        resp = requests.post(url, files=body)
        print(resp.text)
        self.assertEqual(resp.text, "name")
        
    def test_multipart_value(self):
        url = genUrl("/multipart2")
        body = {"name" : "yuekeyuan"}
        resp = requests.post(url, files=body)
        print(resp.text)
        self.assertEqual(resp.text, "yuekeyuan")        
        
    def test_multipart_File(self):
        url = genUrl("/multipart3")
        path = './resultTest/image.png'
        body = {'name': open(path, 'rb')}
        length = os.path.getsize(path)
        
        resp = requests.post(url, files=body)
        print(resp.text)
        self.assertEqual(resp.text, str(length))
        
    # 这一个是使用非引用类型的， 即内部改变IMultiPart 不影响整体
    def test_multipart_notRef(self):
        url = genUrl("/multipart4")
        body = {"name" : "yuekeyuan"}
        resp = requests.post(url, files=body)
        print(resp.text)
        self.assertEqual(resp.text, "yuekeyuan")      
    
    # IMultiPart&
    def test_multipart_Ref(self):
        url = genUrl("/multipart5")
        body = {"name" : "yuekeyuan"}
        resp = requests.post(url, files=body)
        print(resp.text)
        self.assertEqual(resp.text, "yuekeyuan")   