# coding=utf-8

import unittest
import requests
import json
from common.TestHelper import genHeader, genUrl

class PostMethodTest(unittest.TestCase):
    '''
        using post and resolve post
    '''
    
    # 
    def test_url(self):
        url = genUrl("/postParam1")
        resp = requests.get(url)
        print(resp.text)
        self.assertEqual(resp.text, "/postParam1")
        self.assertEqual(resp.headers.get("Content-Type"), "text/css")
        self.assertEqual(resp.status_code, 410)
    
    # form url encode
    # 
    def test_param2_form_url_encode(self):
        url = genUrl("/postParam2")
        payload=json.dumps({'岳克远': '也爱吃巧克力', '岳飞': '爱吃巧克力'})
        headers = {'Content-Type': 'application/json'}
        response = requests.post(url, data=payload, headers=headers)
        print(response.request.body);
        print(str(response.content, encoding="utf-8"))
        # self.assertEqual(str(response.content, encoding="utf-8"), "".join(payload))
    

    # multi part 方式请求
    def test_param3_multipart(self):
        url = genUrl("/postParam3")
        payload= {'岳克远': '也爱吃巧克力', '岳飞': '爱吃巧克力'}
        # header = {'Content-Type': 'application/json'}
        response = requests.post(url, files=payload)
        
        print(response);
        print(str(response.content, encoding="utf-8"), "ppppppppppppppppppppp" )
        
        # self.assertEqual(str(response.content, encoding="utf-8"), "".join(payload))

    
    def test_param4_bodyVal(self):
        url = genUrl("/postParam4")
        payload = json.dumps({
            "name": 1
        })
        headers = {
            'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(json.loads(response.text), {"name" : 1})
        
      
      
    def test_param5_jsonObject(self):
        url = genUrl("/postParam5")
        payload = json.dumps({
            "name": 1
        })
        headers = {
            'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(json.loads(response.text), {"name" : 1})
    
       
    def test_param6_jsonArray(self):
        url = genUrl("/postParam6")
        payload = json.dumps([
            "hello",
            "world"
        ])
        headers = {
            'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(json.loads(response.text), ["hello", "world"])

    
    # TODO: to be ajusted
    def test_param7_jsonValue(self):
        url = genUrl("/postParam7")
        payload = json.dumps([
            1,
            2,
            3,
            4,
            5
        ])
        headers = {
            'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(json.loads(response.text), [1,2,3,4,5])

    
    def test_param8_jsonValueRef(self):
        url = genUrl("/postParam8")
        payload = json.dumps({
        "name": 1
        })
        headers = {
        'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(json.loads(response.text), {"name" : 1})
        
    
    def test_param9_BodyVar(self):
        url = genUrl("/postParam9")
        payload = json.dumps({
            "name": 1
        })
        headers = {
        'Content-Type': 'application/json'
        }

        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(response.text, "1")
    
    
    def test_param10_BodyVar_QString_type(self):
        '''
         请求 使用 json 内部对象 $BodyVar QString 类型
        '''
        url = genUrl("/postParam10")
        payload = json.dumps({
        "name": 1
        })
        headers = {
        'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(response.text, "1")
    
    
    def test_param11_BodyVal_bool(self):
        '''
        请求 使用 json 内部对象 $BodyVar bool 类型
        '''
        url = genUrl("/postParam11")
        payload = json.dumps({
        "name": False
        })
        headers = {
        'Content-Type': 'application/json'
        }

        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(response.text, "false")
       
     
    def test_param12_BodyVal_double(self):
        '''
        p12 请求 使用 json 内部对象 $BodyVar double 类型
        '''
        url = genUrl("/postParam12")
        payload = json.dumps({
        "name": 1.234
        })
        headers = {
        'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(response.text, "1.234")
      
    
    def test_param13_bodyVal_QJsonArray(self):
        '''
        p13 请求 使用 json 内部对象 $BodyVar QJSonArray 类型 Copy
        '''
        url = genUrl("/postParam13")
        payload = json.dumps({
        "name": [
            1,
            2
        ]
        })
        headers = {
        'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        self.assertEqual(json.loads(response.text), [1,2])
        
    
    def test_param14_BodyVal_QJsonObject(self):
        '''
        p14 请求 使用 json 内部对象 $BodyVar QJSonObject 类型
        '''
        url = genUrl("/postParam14")
        payload = json.dumps({
        "name": {
            "yue": 1
        }
        })
        headers = {
        'Content-Type': 'application/json'
        }

        response = requests.request("POST", url, headers=headers, data=payload)
        
        self.assertEqual(json.loads(response.text), {"yue" : 1})