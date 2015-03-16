<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>

<?php
	
	include("mysqlcntdb.php");
	//--------------- 判斷 quwkprod 是否有值
	if ($quwkprod == '') 
	  $msg = "未更新任何報價單資訊！";
	else
	{
	//------------刪除報價資料,更新資料庫------------------------------------------ 
	  $SQLStr = "DELETE FROM quotationwork WHERE  quwkno='$quwkno' AND quwkprod='$quwkprod' AND quwkcust='$quwkcust'";
	  $msag = "刪除報價資料 !!";	
	  mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
