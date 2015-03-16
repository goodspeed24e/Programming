<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	if ($custno == '')
	  $msg = "未更新任何產品資訊！";
	else
	{	
//---------------更新資料庫----------------------	  
	  $SQLStr = "UPDATE cust SET    custsaleamt='$custsaleamt',   custprepamt='$custprepamt', custsaledc='$custsaledc', custprepdc='$custprepdc' WHERE custno='$custno'";
	  $msg = "已更新一筆客戶資料!!";
      mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>