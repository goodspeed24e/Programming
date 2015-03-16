<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
	
	include("mysqlcntdb.php");	
//-------------- 處理產品資料新增------------- 
   	$SQLStr =  "INSERT INTO product (prodno,       prodname,   prodtype,     prodvend,    produnit,    prodipric,    prodspric,    prodsave, prodpqty,  prodnqty, prodgrap,    prodsdesp, proddesp,    prodidate,      prododate)"; 
    $SQLStr .= "VALUES           ('$prodno',    '$prodname', '$prodtype',  '$prodvend', '$produnit',   $prodipric,   $prodspric,   $prodsave,        0,         0,       '', '$prodsdesp',       '', '$prodidate',   '$prododate')";
	mysql_query($SQLStr);
	$msg = "已新增一筆產品基本資料!!";	
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
