<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>

<?php
	//-------------- �ק���ʥD��ƪ�-------------	
	include("mysqlcntdb.php");	
	//--------------- �P�_ purcmprodno �O�_����---------------
	if ($purcmtranno == '') 
	  $msg = "����s������ʥD��ƪ��T�I";
	else
	{
	//------------�ק���ʥD��ƪ�,��s��Ʈw------------------------------------------ 
	$SQLStr="UPDATE purchmst SET purcmvend ='$purcmvend', purcmdate='$purcmdate', purcmtype='$purcmtype' WHERE purcmtranno = '$purcmtranno'";
  	$msg = "�w��s�@�����ʥD��ƪ�!!";
	mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
