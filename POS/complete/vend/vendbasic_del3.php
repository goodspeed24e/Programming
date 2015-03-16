<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php 
	include("mysqlcntdb.php");	
	if (vendno=='') {	
	   $msg = "無法刪除,廠商編號空白 !!";
	} elseif {
       $SQLStr = "DELETE FROM vend WHERE vendno = '$vendno'";
	   $msg = "刪除一筆廠商資料 !!";
	   mysql_query($SQLStr);
	 }
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
