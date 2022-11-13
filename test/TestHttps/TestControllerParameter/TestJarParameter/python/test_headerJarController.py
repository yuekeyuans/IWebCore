import pytest
from util import wrapUrl
import requests
import os

class test_headerJarController:

    def test_headerJar(self):
        url = wrapUrl("header/getHeaderJar")
        res = requests.get(url)
        