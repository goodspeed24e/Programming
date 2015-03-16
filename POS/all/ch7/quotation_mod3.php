<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
    //-------------- 修改報價資料,並將相關資料表中之欄位值,作調整-------------	
	include("mysqlcntdb.php");	
	$dt=date("Y-m-d");	
	//------------- 判斷 quwkprod 是否有值-----------------------------
	if ($quwkprod == '') 
	  $msg = "未更新任何報價單資訊！";
	else
	{
	//------------修改報價資料,更新資料庫------------------------------------------ 
	$SQLStr="UPDATE quotationwork SET quwktype = '$quwktype', quwkpric = '$quwkpric', quwkqty = '$quwkqty', ";
    $SQLStr .="quwksdate= '$dt' WHERE quwkno = '$quwkno' AND quwkprod = '$quwkprod' AND quwkcust = '$quwkcust'";
	$msg = "已更新一筆報價單資料!!";
	mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>