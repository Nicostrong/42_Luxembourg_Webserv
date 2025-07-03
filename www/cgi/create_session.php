<?php
session_start();
$_SESSION["username"] = "testuser";
echo "Hello " . $_SESSION["username"] . " your session_id = " . session_id();
session_destroy();
?>