<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>

<?php
	
	include("mysqlcntdb.php");	
	if ($purcmtranno == '') 
    //---------- �P�_ purcmtranno �O�_����----------
	  $msg = "���R��������ʥD��ƪ��ơI";
	else
	{
	//------------�R�����ʥD��ƪ�ŦX�s������,��s��Ʈw------------------------------------------ 
	  $SQLStr = "DELETE FROM purchmst WHERE  purcmtranno = '$purcmtranno'";
	  $msg = "�R�����ʥD��ƪ��Ƨ��� !!";	
	  mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
