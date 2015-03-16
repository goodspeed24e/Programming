<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
    //-------------- 刪除銷貨資料,並將相關資料表中之欄位值,作調整-------------		
	include("mysqlcntdb.php");
	//-------------- 判斷 outino 是否有值
	if ($outino == '') 
	  $msg = "未刪除任何銷貨資訊！";
	else
	{
	   $SQLStr="UPDATE product SET  prodnqty = prodnqty - $outiprodqty  WHERE prodno = '$outiprodno'";			
	   mysql_query($SQLStr);	
	   $amt=$outiprodqty * $outipric;	  
       $SQLStr="UPDATE cust    SET  custsaleamt = custsaleamt - $amt  WHERE custno = '$outicustno'";			 
       mysql_query($SQLStr);	
	    //------------刪除銷貨資料,自資料庫中剔除------------------------------------------ 
       $SQLStr = "DELETE outinv FROM outinv WHERE outino = '$outino' AND outiprodno = '$outiprodno'";
	   mysql_query($SQLStr);	
	   $SQLStr="UPDATE quotationwork  SET quwksqty = quwksqty - $outiprodqty[$i] WHERE quwkno = '$outiquno'  AND quwkprodno = '$outiprodno'";
       mysql_query($SQLStr);   
	   $msg = "刪除銷貨資料 !!";
	 }
?>
<?php include("gohomepage.php"); ?> 
</body>
</html>
