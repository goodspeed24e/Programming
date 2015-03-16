<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
	include("mysqlcntdb.php");
//---------------------------- 判斷 custno 是否有內容----------------------------
	if ($custno == '') 
	  $msg = "未更新任何客戶銷售設定資訊！";
	else
	{
	 $SQLStr = "UPDATE cust SET    custclosdate='$custclosdate',   custprictype='$custprictype', custpricper='$custpricper' WHERE custno='$custno'";
	 $msg = "已更新一筆客戶銷售設定資料!!";
     mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
