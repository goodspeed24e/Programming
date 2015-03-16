<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>

<?php
	
	include("mysqlcntdb.php");	
	if ($purcmtranno == '') 
    //---------- 判斷 purcmtranno 是否有值----------
	  $msg = "未刪除任何採購主資料表資料！";
	else
	{
	//------------刪除採購主資料表符合編號條件,更新資料庫------------------------------------------ 
	  $SQLStr = "DELETE FROM purchmst WHERE  purcmtranno = '$purcmtranno'";
	  $msg = "刪除採購主資料表資料完成 !!";	
	  mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
