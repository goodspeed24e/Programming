<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
       //-------------- 刪除進貨資料,並將相關資料表中之欄位值,作調整-------------	
	   include("mysqlcntdb.php");		            
	   $SQLStr="UPDATE product SET  prodnqty = prodnqty - $tranprodqty  WHERE prodno = '$tranprodno'";			
	   mysql_query($SQLStr);	  
	   $amt=$tranprodqty * $tranpric;	 
       $SQLStr="UPDATE vend    SET  vendapamt = vendapamt - $amt  WHERE vendno = '$tranvendno'";			 
       mysql_query($SQLStr);
       //------------刪除進貨資料,自資料庫中剔除------------------------------------------
	   $SQLStr = "DELETE FROM transaction WHERE tranno = '$tranno' AND tranpono = '$tranpono' AND tranprodno = '$tranprodno'";
	   mysql_query($SQLStr);
	   $SQLStr="UPDATE purchase  SET purchinqty = purchinqty - $tranprodqty WHERE purchtranno =  '$tranpono'  AND purchprodno = '$tranprodno'"
	   mysql_query($SQLStr);
	   $msg = "已刪除進貨資料 !!";
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
