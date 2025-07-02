import sys
import os

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

content_length = int(os.environ.get('CONTENT_LENGTH', 0))
line = sys.stdin.read(content_length).split(' ')

num1 = float(line[0])
operator = line[1]
num2 = float(line[2])

if operator == '+':
    result = num1 + num2
elif operator == '-':
    result = num1 - num2
elif operator == '*':
    result = num1 * num2
elif operator == '/' and num2 != 0:
    result = num1 / num2
else:
    result = "Input Error"

print(f"{num1} {operator} {num2} = {result}")