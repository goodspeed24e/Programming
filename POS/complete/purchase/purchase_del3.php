<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>

<?php
	
	include("mysqlcntdb.php");	
	//-------------- �P�_ purchprodno �O�_����---------------
	if ($purchprodno == '') 
	  $msg = "����s������ʳ��T�I";
	else
	{
	//------------�R�����ʸ��,��s��Ʈw------------------------------------------ 
	  $SQLStr = "DELETE FROM purchase WHERE  purchtranno = '$purchtranno' AND purchprodno = '$purchprodno'";
	  $msg = "�R�����ʸ�Ƨ��� !!";	
	  mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
