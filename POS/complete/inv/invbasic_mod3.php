<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
	include("mysqlcntdb.php");
//-------------- 處理產品資料更新------------- 
	$SQLStr="UPDATE product SET prodno = '$prodno', prodname = '$prodname', prodtype = '$prodtype', ";
   	$SQLStr .="prodvend = '$prodvend', produnit = '$produnit',  prodipric='$prodipric', prodspric = '$prodspric',";
	$SQLStr .="prodsave = '$prodsave', prodgrap = '$prodgrap',  prodsdesp='$prodsdesp', prodidate = '$prodidate',";
	$SQLStr .="prododate = '$prododate' WHERE prodno = '$prodno'";	
	$msg = "已更新一筆進貨單資料!!";
	mysql_query($SQLStr);	
?>
<?php include("gohomepage.php"); ?>
</body>
</html>