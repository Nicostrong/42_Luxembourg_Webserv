#!/usr/bin/env php
<?php
header("Content-Type: text/html; charset=utf-8");

echo "<h1>CGI Debug Info</h1>";
echo "<h2>Environment Variables:</h2>";
echo "<pre>";
foreach ($_ENV as $key => $value) {
    echo "$key = $value\n";
}
echo "</pre>";

echo "<h2>Server Variables:</h2>";
echo "<pre>";
foreach ($_SERVER as $key => $value) {
    echo "$key = $value\n";
}
echo "</pre>";
?>