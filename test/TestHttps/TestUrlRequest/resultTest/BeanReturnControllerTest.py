import requests
import unittest
from common.TestHelper import genUrl

class BeanReturnControllerTest(unittest.TestCase):
    '''
    测试 bean 返回值
    '''
    
    def test_getBean(self):
        url = genUrl("/getBean")
        resp = requests.get(url)
        print(resp.json())
        print("hello world")
        self.assertEqual(resp.json(),   {
            "age": 100,
            "name": "yuekeyuan"
        })
        
        
    def test_getBeans_1(self):
        url = genUrl("/getBeans")
        resp = requests.get(url)
        print(resp.json())
        self.assertEqual(resp.json(), [
            {
                "age": 100,
                "name": "hello world"
            },
            {
                "age": 100,
                "name": "yuekeyuan"
            }
        ])
        
    def test_getBeans_2(self):
        url = genUrl("/getBeans_1")
        resp = requests.get(url)
        print(resp.json())
        self.assertEqual(resp.json(), [
            {
                "age": 100,
                "name": "hello world"
            },
            {
                "age": 100,
                "name": "yuekeyuan"
            }
        ])
        
    def test_getBeans_vector(self):
        url = genUrl("/getVectorBeans")
        resp = requests.get(url);
        self.assertEqual(resp.json(), [
            {
                "age": 100,
                "name": "yuekeyuan"
            },
            {
                "age": 100,
                "name": "yuekeyuan"
            }
        ])
        
    def test_ListString(self):
        url = genUrl("/getListString")
        resp = requests.get(url)
        self.assertEqual(resp.json(),[
            "hello",
            "world"
        ])
        
        
    def test_ListInt(self):
        url = genUrl("/getListInt")
        resp = requests.get(url)
        self.assertEqual(resp.json(),[
            1,2,3
        ])
        
    def test_ListBool(self):
        url = genUrl("/getListBool")
        response = requests.get(url)
        self.assertEqual(response.json(), [
            True, False, True
        ])      
        
    def test_BeanMap(self):
        url = genUrl("/getBeansMap")
        response = requests.get(url)
        self.assertEqual(response.json(),{
            "hello": {
                "age": 100,
                "name": "yuekeyuan"
            },
            "world": {
                "age": 100,
                "name": "yuekeyuan"
            }
        })  
        
    def test_beansListMap(self):
        url = genUrl("/getBeansListMap")
        response = requests.get(url)
        self.assertEqual(response.json(),[
            {
                "hello": {
                "age": 100,
                "name": "yuekeyuan"
                }
            }
        ])
    
    def test_getPlainTextBean(self):
        url = genUrl("/getPlainTextBean")
        response = requests.get(url)
        self.assertEqual(response.text, '[{"hello":{"age":100,"name":"yuekeyuan"}}]')
        
        