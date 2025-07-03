<?php

session_start();
if (!isset($_SESSION['PHPSESSID']))
{
    $_SESSION['PHPSESSID'] = session_id();
}
http_response_code(200);
header("Content-Type: text/html; charset=utf-8");

?>