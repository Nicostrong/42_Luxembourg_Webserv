# in order to be able to run these tests on school computers, install python3: brew install python3
# install pytest: pip3 install pytest
# install dependencies: pip3 install requests bs4
# create venv: python3 -m venv env
# activate it: source env/bin/activate
# to run: pytest testing.py

import unittest
import requests
import os
from bs4 import BeautifulSoup

url = "http://localhost:8080/index"
error4 = "http://localhost:8080/bad"
"""
def remove_html_tags(html):
	soup = BeautifulSoup(html, 'html.parser')
	text = soup.get_text()
	return text

def test_root_url():
	response = requests.get(url)
	assert response.status_code == 200
	with open("../website/html/index.html") as file:
		expected_content = file.read()
	assert response.text == expected_content

def test_nonexistent_page():
	response = requests.get(error4)
	with open("../website/html/error_pages/404.html") as file:
		expected_content = file.read()
	assert response.status_code == 404
	assert response.text == expected_content

def test_invalid_method():
	with open("../website/html/error_pages/405.html") as file:
		expected_content = file.read()
	response = requests.request("TTT", url)
	assert response.status_code == 405
	assert response.text == expected_content

def test_several_ports():
	url2 = "http://localhost:8080/index"
	response = requests.get(url)
	assert response.status_code == 200
	with open("../website/html/index.html") as file:
		expected_content = file.read()
	assert response.text == expected_content
	
	response = requests.get(url2)
	assert response.status_code == 200
	with open("../website/html/index.html") as file:
		expected_content = file.read()
	assert response.text == expected_content

def test_several_servers():
	url2 = "http://127.0.0.1:8080/index"
	response = requests.get(url)
	assert response.status_code == 200
	with open("../website/html/index.html") as file:
		expected_content = file.read()
	assert response.text == expected_content
	
	response = requests.get(url2)
	assert response.status_code == 200
	with open("../website/html/index.html") as file:
		expected_content = file.read()
	assert response.text == expected_content

def test_autoindex():
	url2 = "http://localhost:8080/autoindex"
	expected_file_path = "../website/html/autoindex"
	expected_files = os.listdir(expected_file_path)

	response = requests.get(url2)
	clean_text = remove_html_tags(response.text)
	assert response.status_code == 200
	for file in expected_files:
		assert file in clean_text

def test_autoindex_off():
	url2 = "http://localhost:8080/test"
	with open("../website/html/test/index.html") as file:
		expected_content = file.read()

	response = requests.get(url2)
	clean_text = remove_html_tags(response.text)
	assert response.status_code == 200
	assert response.text == expected_content
"""
def	test_cgi_calculator_plus():
	url2 = "http://localhost:8080/cgi/calculator.py"
	input_data = {
		"num1": "10",
		"num2": "5",
		"operator": "+"
	}
	expected_output = "10.0 + 5.0 = 15.0"
	response = requests.post(url2, json=input_data)
	lines = response.text.splitlines()
	print(lines)
	assert response.status_code == 200
	assert lines[1] == expected_output

def	test_cgi_calculator_minus():
	url2 = "http://localhost:8080/cgi/calculator.py"
	input_data = {
		"num1": "10",
		"num2": "5",
		"operator": "-"
	}
	expected_output = "10.0 - 5.0 = 5.0"
	response = requests.post(url2, json=input_data)
	lines = response.text.splitlines()
	print(lines)
	assert response.status_code == 200
	assert lines[1] == expected_output

def	test_cgi_calculator_multiply():
	url2 = "http://localhost:8080/cgi/calculator.py"
	input_data = {
		"num1": "10",
		"num2": "5",
		"operator": "*"
	}
	expected_output = "10.0 * 5.0 = 50.0"
	response = requests.post(url2, json=input_data)
	lines = response.text.splitlines()
	print(lines)
	assert response.status_code == 200
	assert lines[1] == expected_output

def	test_cgi_calculator_division():
	url2 = "http://localhost:8080/cgi/calculator.py"
	input_data = {
		"num1": "10",
		"num2": "5",
		"operator": "/"
	}
	expected_output = "10.0 / 5.0 = 2.0"
	response = requests.post(url2, json=input_data)
	lines = response.text.splitlines()
	print(lines)
	assert response.status_code == 200
	assert lines[1] == expected_output

def	test_cgi_crypto():
	url2 = "http://localhost:8080/cgi/crypto.py"
	input_data = {
		"amount_bought": "10",
		"value_paid": "5",
		"amount_sold": "5"
	}
	#expected_output = "10.0 / 5.0 = 2.0"
	response = requests.post(url2, json=input_data)
	lines = response.text.splitlines()
	print(lines)
	assert response.status_code == 200
	#assert lines[1] == expected_output
