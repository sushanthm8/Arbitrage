import requests
import json

url = 'https://v6.exchangerate-api.com/v6/ef9e0244cfb336c2abb59114/latest/USD'
response = requests.get(url)
data = response.json()


with open('data.json','w') as outfile:
    json.dump(data,outfile, indent=4)

f=open("data.txt","a")
for ticker in data["conversion_rates"]:
    f.write(ticker)
    f.write(":")
    f.write(str(data["conversion_rates"][ticker]))
    f.write("\n")
f.close()

