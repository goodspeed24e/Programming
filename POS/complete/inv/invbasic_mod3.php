<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
	include("mysqlcntdb.php");
//-------------- �B�z���~��Ƨ�s------------- 
	$SQLStr="UPDATE product SET prodno = '$prodno', prodname = '$prodname', prodtype = '$prodtype', ";
   	$SQLStr .="prodvend = '$prodvend', produnit = '$produnit',  prodipric='$prodipric', prodspric = '$prodspric',";
	$SQLStr .="prodsave = '$prodsave', prodgrap = '$prodgrap',  prodsdesp='$prodsdesp', prodidate = '$prodidate',";
	$SQLStr .="prododate = '$prododate' WHERE prodno = '$prodno'";	
	$msg = "�w��s�@���i�f����!!";
	mysql_query($SQLStr);	
?>
<?php include("gohomepage.php"); ?>
</body>
</html>