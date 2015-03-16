<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
	//-------------- 修改銷貨資料,並將相關資料表中之欄位值,作調整-------------		
	include("mysqlcntdb.php");
	$amt=$outiprodqty * $outipric;
	 //------------修改銷貨資料,更新資料庫------------------------------------------ 
	$SQLStr="UPDATE outinv SET outino = '$outino', outiprodno = '$outiprodno', outiprodname = '$outiprodname', ";
   	$SQLStr .="outidate = '$outidate', outicustno = '$outicustno',  outiprodqty='$outiprodqty', outiunit = '$outiunit',";
    $SQLStr .="outipric = '$outipric' WHERE outino = '$outino' AND outiprodno = '$outiprodno'";
	mysql_query($SQLStr);
	//-------------- 修改並將相關資料表中之欄位值,作調整-------------
	$SQLStr="UPDATE product SET  prodnqty = prodnqty + $outiprodqty - $oqty WHERE prodno = '$outiprodno'";			
	mysql_query($SQLStr);	
	$oamt=$oqty * $opric;
	//------------修改客戶資料,更新資料庫------------------------------------------ 
    $SQLStr="UPDATE cust    SET  custsaleamt = custsaleamt + $amt - $oamt WHERE custno = '$outicustno'";			 
    mysql_query($SQLStr);
	//------------修改報價資料,更新資料庫------------------------------------------ 
	$SQLStr="UPDATE quotationwork    SET  quwksqty = $outiprodqty  WHERE quwkno = '$outiquno' AND quwkprodno = '$outiprodno'";			 
    mysql_query($SQLStr);
	$msg = "已更新一筆銷貨單資料!!";
	
?>
<?php include("gohomepage.php"); ?> 
</body>
</html>
