<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
	include("mysqlcntdb.php");	
	//$vendclosdate=date("vendclosdate");
// ---------����ˬd,�P�_ vendno �O�_����------------------------------	
    if ($vendno == '') 
	  $msg = "����s����t�Ӹ�T�I";
	else
	{
//-----------------��s�t�ӱb�ڸ��, �s����ƪ�-------------------		
       $SQLStr = "UPDATE vend SET    vendclosdate='$vendclosdate',   vendprictype='$vendprictype', vendpricper='$vendpricper' WHERE vendno='$vendno'";
   	   $msg = "�w��s�@���t�Ӹ��!!";
	   mysql_query($SQLStr);
	 }
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
