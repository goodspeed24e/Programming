<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>

<?php
	 //-------------- 修改採購明細資料,並將相關資料表中之欄位值,作調整-------------	
	include("mysqlcntdb.php");
	//--------------- 判斷 purchprodno 是否有值---------------
	if ($purchprodno == '') 
	  $msg = "未更新任何採購明細資訊！";
	else
	{
	//------------修改採購明細資料表,更新資料庫------------------------------------------ 
	$SQLStr="UPDATE purchase SET purchtranno = '$purchtranno', purchprodno = '$purchprodno', purchprodqty = '$purchprodqty', ";
    $SQLStr .="purchpric = '$purchpric' WHERE purchtranno = '$purchtranno' AND purchprodno = '$purchprodno'";
	$msg = "已更新一筆採購明細資料!!";
	mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
