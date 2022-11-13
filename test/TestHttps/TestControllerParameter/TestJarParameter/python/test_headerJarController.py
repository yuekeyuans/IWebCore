import pytest
from util import wrapUrl
import requests
import os
import json

class TestHeaderJarController:

    def test_headerJar(self):
        url = wrapUrl("header/getHeaderJar")
        headers = {"hello": "world"}

        res = requests.get(url, headers=headers)
        assert res.text == "world"

    def test_testRequestHeaderKeys(self):
        url = wrapUrl("header/testRequestHeaderKeys")
        headers = {"hello": "world"}

        res = requests.get(url, headers=headers)
        json1 = eval(res.text)
        assert "hello" in json1;



    def test_testAddResponseHeader(self):
        url = wrapUrl("header/testAddResponseHeader")
        res = requests.get(url)
        assert res.headers[res.text] == "world"