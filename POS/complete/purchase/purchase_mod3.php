<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>

<?php
	 //-------------- �ק���ʩ��Ӹ��,�ñN������ƪ�������,�@�վ�-------------	
	include("mysqlcntdb.php");
	//--------------- �P�_ purchprodno �O�_����---------------
	if ($purchprodno == '') 
	  $msg = "����s������ʩ��Ӹ�T�I";
	else
	{
	//------------�ק���ʩ��Ӹ�ƪ�,��s��Ʈw------------------------------------------ 
	$SQLStr="UPDATE purchase SET purchtranno = '$purchtranno', purchprodno = '$purchprodno', purchprodqty = '$purchprodqty', ";
    $SQLStr .="purchpric = '$purchpric' WHERE purchtranno = '$purchtranno' AND purchprodno = '$purchprodno'";
	$msg = "�w��s�@�����ʩ��Ӹ��!!";
	mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
