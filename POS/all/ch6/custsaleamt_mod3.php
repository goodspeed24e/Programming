<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	if ($custno == '')
	  $msg = "����s���󲣫~��T�I";
	else
	{	
//---------------��s��Ʈw----------------------	  
	  $SQLStr = "UPDATE cust SET    custsaleamt='$custsaleamt',   custprepamt='$custprepamt', custsaledc='$custsaledc', custprepdc='$custprepdc' WHERE custno='$custno'";
	  $msg = "�w��s�@���Ȥ���!!";
      mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>