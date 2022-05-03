from unittest import SkipTest, result
import requests
import unittest
from common.TestHelper import genUrl


class InterceptTest(unittest.TestCase):
    
    @unittest.skip
    def test_404_status(self):
        url = genUrl("/404")        # any address is ok
        resp = requests.get(url)
        self.assertEqual(resp.status_code, 404)
        self.assertEqual(resp.text, "not found")
        