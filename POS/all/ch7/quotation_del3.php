<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>

<?php
	
	include("mysqlcntdb.php");
	//--------------- �P�_ quwkprod �O�_����
	if ($quwkprod == '') 
	  $msg = "����s����������T�I";
	else
	{
	//------------�R���������,��s��Ʈw------------------------------------------ 
	  $SQLStr = "DELETE FROM quotationwork WHERE  quwkno='$quwkno' AND quwkprod='$quwkprod' AND quwkcust='$quwkcust'";
	  $msag = "�R��������� !!";	
	  mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
