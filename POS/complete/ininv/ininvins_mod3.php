<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	//-------------- 修改進貨資料,並將相關資料表中之欄位值,作調整-------------	
	include("mysqlcntdb.php");	
	if ($tranno == '')
	 //--------------------- 判斷 tranno 是否有值--------------
	  $msg = "未更新任何進貨單資訊！";
	else
	{
	$amt=$tranprodqty * $tranpric;
	 //------------修改進貨資料,更新資料庫------------------------------------------ 
	$SQLStr="UPDATE transaction SET trancode = 'i', tranno = '$tranno', tranpono = '$tranpono', trandate='$trandate',";
   	$SQLStr .="tranvendno = '$tranvendno', tranprodno = '$tranprodno',  tranprodname='$tranprodname', tranprodqty = '$tranprodqty',";
    $SQLStr .="tranunit = '$tranunit', tranpric = '$tranpric', tranamt = $amt WHERE tranno = '$tranno' AND tranpono = '$tranpono' AND tranprodno = '$tranprodno'";
	mysql_query($SQLStr);	
	//-------------- 修改並將相關資料表中之欄位值,作調整-------------
	$SQLStr="UPDATE product SET  prodnqty = prodnqty + $tranprodqty - $oqty WHERE prodno = '$tranprodno'";			
	mysql_query($SQLStr);	
	$oamt=$oqty * $opric;
    $SQLStr="UPDATE vend    SET  vendapamt = vendapamt + $amt - $oamt WHERE vendno = '$tranvendno'";			 
    mysql_query($SQLStr);
	$SQLStr="UPDATE purchase  SET purchinqty = '$tranprodqty'  WHERE purchtranno =  '$tranpono'  AND purchprodno = '$tranprodno[$i]'";
	mysql_query($SQLStr);
	$msg = "已更新一筆並改變廠商進貨單資料!!";
    }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
