<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	//-------------- �ק�i�f���,�ñN������ƪ�������,�@�վ�-------------	
	include("mysqlcntdb.php");	
	if ($tranno == '')
	 //--------------------- �P�_ tranno �O�_����--------------
	  $msg = "����s����i�f���T�I";
	else
	{
	$amt=$tranprodqty * $tranpric;
	 //------------�ק�i�f���,��s��Ʈw------------------------------------------ 
	$SQLStr="UPDATE transaction SET trancode = 'i', tranno = '$tranno', tranpono = '$tranpono', trandate='$trandate',";
   	$SQLStr .="tranvendno = '$tranvendno', tranprodno = '$tranprodno',  tranprodname='$tranprodname', tranprodqty = '$tranprodqty',";
    $SQLStr .="tranunit = '$tranunit', tranpric = '$tranpric', tranamt = $amt WHERE tranno = '$tranno' AND tranpono = '$tranpono' AND tranprodno = '$tranprodno'";
	mysql_query($SQLStr);	
	//-------------- �ק�ñN������ƪ�������,�@�վ�-------------
	$SQLStr="UPDATE product SET  prodnqty = prodnqty + $tranprodqty - $oqty WHERE prodno = '$tranprodno'";			
	mysql_query($SQLStr);	
	$oamt=$oqty * $opric;
    $SQLStr="UPDATE vend    SET  vendapamt = vendapamt + $amt - $oamt WHERE vendno = '$tranvendno'";			 
    mysql_query($SQLStr);
	$SQLStr="UPDATE purchase  SET purchinqty = '$tranprodqty'  WHERE purchtranno =  '$tranpono'  AND purchprodno = '$tranprodno[$i]'";
	mysql_query($SQLStr);
	$msg = "�w��s�@���ç��ܼt�Ӷi�f����!!";
    }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
