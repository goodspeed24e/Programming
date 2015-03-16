<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php 
	include("mysqlcntdb.php");	
	if (prodnqty >0) {	
	   $message = "無法刪除,產品尚有庫存量資料 !!";
	} elseif {
//-------------- 處理產品資料刪除------------- 		
       $SQLStr = "DELETE FROM product WHERE prodno = '$prodno'";
	   $message = "刪除一筆產品資料 !!";
	   mysql_query($SQLStr);
	 }
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
