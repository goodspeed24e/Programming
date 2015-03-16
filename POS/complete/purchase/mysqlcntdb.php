<?php
$mysql_db = "webdb";
$mysql_user = "root";
$mysql_pass = "設定您的密碼內容";
$mysql_link = mysql_connect("localhost", $mysql_user, $mysql_pass);
mysql_select_db($mysql_db, $mysql_link);
?>