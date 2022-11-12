import pytest
from util import wrapUrl
import requests
import os

class TestMultiPartController:
    
    def test_testFileMultiPartJar(self):
        url = wrapUrl("multipart/testFileMultiPartJar")

        data = {}
        data["test_multiPartJarController.py"] = os.path.getsize("./test_multiPartJarController.py")
        data["main.py"] =  os.path.getsize("./main.py")
        files = [
            ('file_1', open('./test_multiPartJarController.py', 'rb')),
            ('file_2', open('./main.py', 'rb')),
        ]

        res = requests.post(url, files=files, data= data)
        assert res.text == "2"

    def test_testFileMultiPart(self):
        url = wrapUrl("multipart/testFileMultiPart")

        files = [
            ('file_1', open('./test_multiPartJarController.py', 'rb')),
            ('file_2', open('./main.py', 'rb')),
        ]

        res = requests.post(url, files=files)
        assert res.text == str(os.path.getsize("./test_multiPartJarController.py"))

        files = [
            ('file_3', open('./test_multiPartJarController.py', 'rb')),
            ('file_2', open('./main.py', 'rb')),
        ]

        res = requests.post(url, files=files)
        assert res.text != str(os.path.getsize("./test_multiPartJarController.py"))

    def test_testFileMultiPartJarNotExist(self):
        url = wrapUrl("multipart/testFileMultiPartJarNotExist")

        files = [
            ('file_1', open('./test_multiPartJarController.py', 'rb')),
            ('file_2', open('./main.py', 'rb')),
        ]

        res = requests.post(url, files=files)
        assert res.text == "error"

        files = [
            ('hello', open('./test_multiPartJarController.py', 'rb')),
            ('file_2', open('./main.py', 'rb')),
        ]

        res = requests.post(url, files=files)
        assert res.text == "success"

    def testFileMultiPartNames(self):
        url = wrapUrl("multipart/testFileMultiPartNames")

        files = [
            ('file_1', open('./test_multiPartJarController.py', 'rb')),
            ('file_2', open('./main.py', 'rb')),
        ]

        res = requests.post(url, files=files)
        print(res.text)
        assert res.text == '["file_1", "file_2"]'
