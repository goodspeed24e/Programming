<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
	include("mysqlcntdb.php");
//---------------------------- �P�_ custno �O�_�����e----------------------------
	if ($custno == '') 
	  $msg = "����s����Ȥ�P��]�w��T�I";
	else
	{
	 $SQLStr = "UPDATE cust SET    custclosdate='$custclosdate',   custprictype='$custprictype', custpricper='$custpricper' WHERE custno='$custno'";
	 $msg = "�w��s�@���Ȥ�P��]�w���!!";
     mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
