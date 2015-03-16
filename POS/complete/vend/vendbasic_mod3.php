<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
	include("mysqlcntdb.php");
//-----------------更新廠商資料, 連接資料表-------------------				
	$SQLStr="UPDATE vend SET vendno = '$vendno', vendtype = '$vendtype', vendsname = '$vendsname', ";
   	$SQLStr .="vendname = '$vendname', vendleader = '$vendleader',  vendinvoice='$vendinvoice', vendcontact = '$vendcontact',";
	$SQLStr .="vendtel = '$vendtel', vendmobil = '$vendmobil',  vendfax='$vendfax', vendsales = '$vendsales',";
	$SQLStr .="vendadr = '$vendadr', vendpradr = '$vendpradr',  vendinadr='$vendinadr', vendemail = '$vendemail',";
    $SQLStr .="vendhttp = '$vendhttp' WHERE vendno = '$vendno'";
	$message = "已更新一筆廠商資料!!";
	mysql_query($SQLStr);	
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
