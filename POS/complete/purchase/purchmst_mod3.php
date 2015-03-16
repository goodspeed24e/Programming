<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>

<?php
	//-------------- 修改採購主資料表-------------	
	include("mysqlcntdb.php");	
	//--------------- 判斷 purcmprodno 是否有值---------------
	if ($purcmtranno == '') 
	  $msg = "未更新任何採購主資料表資訊！";
	else
	{
	//------------修改採購主資料表,更新資料庫------------------------------------------ 
	$SQLStr="UPDATE purchmst SET purcmvend ='$purcmvend', purcmdate='$purcmdate', purcmtype='$purcmtype' WHERE purcmtranno = '$purcmtranno'";
  	$msg = "已更新一筆採購主資料表!!";
	mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
