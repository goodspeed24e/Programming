<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
	
	include("mysqlcntdb.php");	
//-------------- �B�z���~��Ʒs�W------------- 
   	$SQLStr =  "INSERT INTO product (prodno,       prodname,   prodtype,     prodvend,    produnit,    prodipric,    prodspric,    prodsave, prodpqty,  prodnqty, prodgrap,    prodsdesp, proddesp,    prodidate,      prododate)"; 
    $SQLStr .= "VALUES           ('$prodno',    '$prodname', '$prodtype',  '$prodvend', '$produnit',   $prodipric,   $prodspric,   $prodsave,        0,         0,       '', '$prodsdesp',       '', '$prodidate',   '$prododate')";
	mysql_query($SQLStr);
	$msg = "�w�s�W�@�����~�򥻸��!!";	
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
