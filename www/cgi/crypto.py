import sys
import os
import json
import random as r

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

try:
    content_length = int(os.environ.get('CONTENT_LENGTH', 0))
    line = sys.stdin.read(content_length)
    data = json.loads(line)
    amount_bought = float(data.get('amount_bought', 0))
    value_paid = float(data.get('value_paid', 0))
    amount_sold = float(data.get('amount_sold', 0))
    value_received = r.random()*1000
except Exception as e:
    print(e)
    exit()

if amount_sold > amount_bought:
    print("Error: You cannot sell more than you have")
    exit()

"""
the cgi must work as single command. so the user inputs the amount bought, the value paid per crypto and the amount to be sold.
then the script prints the difference between received and paid, if positive: BENEFIT
"""

profit = (value_received - value_paid) * amount_sold
if profit < 0:
    outcome = "LOSS"
elif profit > 0:
    outcome = "PROFIT"
else:
    outcome + "No loss, no profit"

print(f"{outcome} {profit} Stock Left: {amount_bought - amount_sold}")