<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>

<?php
	
	include("mysqlcntdb.php");	
	//-------------- 判斷 purchprodno 是否有值---------------
	if ($purchprodno == '') 
	  $msg = "未更新任何採購單資訊！";
	else
	{
	//------------刪除採購資料,更新資料庫------------------------------------------ 
	  $SQLStr = "DELETE FROM purchase WHERE  purchtranno = '$purchtranno' AND purchprodno = '$purchprodno'";
	  $msg = "刪除採購資料完成 !!";	
	  mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
