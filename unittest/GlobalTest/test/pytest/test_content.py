import http
from ServerConfig import *
from http.client import HTTPConnection
import requests

def generate_chunks():
    for i in range(1, 6):  # 示例：分成5个块
        print(f"Generating chunk {i}")
        yield f"Chunk {i}\n".encode("utf-8")

def test_QString():
    url = serverAddress + "/Content/chunkedData"
    headers = {
        "Transfer-Encoding": "chunked",  # 明确指定分块传输
        "Content-Type": "text/plain",    # 根据需求设置内容类型
    }

    response = requests.post(url, data=generate_chunks(), headers=headers)

    print("Status Code:", response.status_code)
    print("Response Body:", response.text)
    assert response.status_code == 200
    # assert response.text == "Chunk 1\nChunk 2\nChunk 3\nChunk 4\nChunk 5\n"

def test_headMethod():
    url = serverAddress + "/Content/headMethod"
    val = requests.head(url)
    print(val.headers)
    print(val.text)
    assert val.status_code == 200
    assert val.text == ""
    assert val.headers["Content-Length"] == "10"

def test_optionsMethod():
    url = serverAddress + "/BasicArgument/headerType"
    val = requests.options(url) 
    print(val.headers)
    print(val.text)
    assert val.status_code == 200
    assert val.text == ""
    assert val.headers["Allow"] == "GET, HEAD, OPTIONS"

def test_optionsMethod2():
    url = serverAddress + "/BasicArgument/headerType1"
    val = requests.options(url) 
    print(val.headers)
    print(val.text)
    assert val.status_code == 404


# NOTE: install http.client for Python 3.x
def test_optionsAll():
        # 创建与服务器的连接
    conn = http.client.HTTPConnection(ip, port)

    # 发送 OPTIONS * 请求
    conn.request("OPTIONS", "*", headers={})

    # 获取响应
    response = conn.getresponse()
    print(f"Status Code: {response.status}")
    print(f"Headers: {response.getheaders()}")
    print(f"Response Body: {response.read().decode('utf-8')}")

    # 关闭连接
    conn.close()