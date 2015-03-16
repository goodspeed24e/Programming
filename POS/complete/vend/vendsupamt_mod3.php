<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
	include("mysqlcntdb.php");	
	//$vendclosdate=date("vendclosdate");
// ---------資料檢查,判斷 vendno 是否有值------------------------------	
    if ($vendno == '') 
	  $msg = "未更新任何廠商資訊！";
	else
	{
//-----------------更新廠商帳款資料, 連接資料表-------------------		
       $SQLStr = "UPDATE vend SET    vendclosdate='$vendclosdate',   vendprictype='$vendprictype', vendpricper='$vendpricper' WHERE vendno='$vendno'";
   	   $msg = "已更新一筆廠商資料!!";
	   mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
