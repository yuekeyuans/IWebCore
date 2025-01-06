from ServerConfig import *
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
    assert response.text == "Chunk 1\nChunk 2\nChunk 3\nChunk 4\nChunk 5\n"