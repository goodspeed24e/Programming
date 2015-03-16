<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
	include("mysqlcntdb.php");
	$SQLStr="UPDATE product SET prodpqty = $prodpqty, prodnqty = $prodnqty WHERE prodno = '$prodno'";	
	$msg = "已更新一筆產品資料!!";
	mysql_query($SQLStr);	
?>
<!----執行完成,回首頁------------------------->
<?php include("gohomepage.php"); ?>
</body>
</html>