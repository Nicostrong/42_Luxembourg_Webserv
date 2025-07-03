import sys
import os
import json
import random as r

line = input("").split(' ')
amount_bought = float(line[0])
value_paid = float(line[1])
amount_sold = float(line[2])
value_received = -1000 + r.random()*2000

if amount_sold > amount_bought:
    print("Error: You cannot sell more than you have")
    exit

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