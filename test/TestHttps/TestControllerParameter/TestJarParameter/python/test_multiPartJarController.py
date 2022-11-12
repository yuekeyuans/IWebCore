import pytest
from util import wrapUrl
import requests

class TestMultiPartController:
    
    def test_one(self):
        url = wrapUrl("multipart/getMultiPartJar")

        data = {'key_1': 'value_1', 'key_2': 'value_2'}
        files = [
            ('file_1', open('./test_multiPartJarController.py', 'rb')),
            ('file_2', open('./main.py', 'rb')),
        ]

        res = requests.post(url, files=files, data= data)
        print(res.text)
