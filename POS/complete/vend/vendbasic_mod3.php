<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
	include("mysqlcntdb.php");
//-----------------��s�t�Ӹ��, �s����ƪ�-------------------				
	$SQLStr="UPDATE vend SET vendno = '$vendno', vendtype = '$vendtype', vendsname = '$vendsname', ";
   	$SQLStr .="vendname = '$vendname', vendleader = '$vendleader',  vendinvoice='$vendinvoice', vendcontact = '$vendcontact',";
	$SQLStr .="vendtel = '$vendtel', vendmobil = '$vendmobil',  vendfax='$vendfax', vendsales = '$vendsales',";
	$SQLStr .="vendadr = '$vendadr', vendpradr = '$vendpradr',  vendinadr='$vendinadr', vendemail = '$vendemail',";
    $SQLStr .="vendhttp = '$vendhttp' WHERE vendno = '$vendno'";
	$message = "�w��s�@���t�Ӹ��!!";
	mysql_query($SQLStr);	
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
