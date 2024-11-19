

baseUrl = "http://127.0.0.1:8088"
# baseUrl = "http://39.103.171.192:80"
def genUrl(url):
    return baseUrl + url

def genHeader(type = "text/plain"):
    return { 'Content-Type': type }

