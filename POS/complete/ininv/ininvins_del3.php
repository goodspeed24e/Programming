<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
       //-------------- �R���i�f���,�ñN������ƪ�������,�@�վ�-------------	
	   include("mysqlcntdb.php");		            
	   $SQLStr="UPDATE product SET  prodnqty = prodnqty - $tranprodqty  WHERE prodno = '$tranprodno'";			
	   mysql_query($SQLStr);	  
	   $amt=$tranprodqty * $tranpric;	 
       $SQLStr="UPDATE vend    SET  vendapamt = vendapamt - $amt  WHERE vendno = '$tranvendno'";			 
       mysql_query($SQLStr);
       //------------�R���i�f���,�۸�Ʈw���簣------------------------------------------
	   $SQLStr = "DELETE FROM transaction WHERE tranno = '$tranno' AND tranpono = '$tranpono' AND tranprodno = '$tranprodno'";
	   mysql_query($SQLStr);
	   $SQLStr="UPDATE purchase  SET purchinqty = purchinqty - $tranprodqty WHERE purchtranno =  '$tranpono'  AND purchprodno = '$tranprodno'"
	   mysql_query($SQLStr);
	   $msg = "�w�R���i�f��� !!";
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
