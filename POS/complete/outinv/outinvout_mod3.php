<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
	//-------------- �ק�P�f���,�ñN������ƪ�������,�@�վ�-------------		
	include("mysqlcntdb.php");
	$amt=$outiprodqty * $outipric;
	 //------------�ק�P�f���,��s��Ʈw------------------------------------------ 
	$SQLStr="UPDATE outinv SET outino = '$outino', outiprodno = '$outiprodno', outiprodname = '$outiprodname', ";
   	$SQLStr .="outidate = '$outidate', outicustno = '$outicustno',  outiprodqty='$outiprodqty', outiunit = '$outiunit',";
    $SQLStr .="outipric = '$outipric' WHERE outino = '$outino' AND outiprodno = '$outiprodno'";
	mysql_query($SQLStr);
	//-------------- �ק�ñN������ƪ�������,�@�վ�-------------
	$SQLStr="UPDATE product SET  prodnqty = prodnqty + $outiprodqty - $oqty WHERE prodno = '$outiprodno'";			
	mysql_query($SQLStr);	
	$oamt=$oqty * $opric;
	//------------�ק�Ȥ���,��s��Ʈw------------------------------------------ 
    $SQLStr="UPDATE cust    SET  custsaleamt = custsaleamt + $amt - $oamt WHERE custno = '$outicustno'";			 
    mysql_query($SQLStr);
	//------------�ק�������,��s��Ʈw------------------------------------------ 
	$SQLStr="UPDATE quotationwork    SET  quwksqty = $outiprodqty  WHERE quwkno = '$outiquno' AND quwkprodno = '$outiprodno'";			 
    mysql_query($SQLStr);
	$msg = "�w��s�@���P�f����!!";
	
?>
<?php include("gohomepage.php"); ?> 
</body>
</html>
