<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
    //-------------- �ק�������,�ñN������ƪ�������,�@�վ�-------------	
	include("mysqlcntdb.php");	
	$dt=date("Y-m-d");	
	//------------- �P�_ quwkprod �O�_����-----------------------------
	if ($quwkprod == '') 
	  $msg = "����s����������T�I";
	else
	{
	//------------�ק�������,��s��Ʈw------------------------------------------ 
	$SQLStr="UPDATE quotationwork SET quwktype = '$quwktype', quwkpric = '$quwkpric', quwkqty = '$quwkqty', ";
    $SQLStr .="quwksdate= '$dt' WHERE quwkno = '$quwkno' AND quwkprod = '$quwkprod' AND quwkcust = '$quwkcust'";
	$msg = "�w��s�@����������!!";
	mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>