<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php 
	include("mysqlcntdb.php");	
	if (vendno=='') {	
	   $msg = "�L�k�R��,�t�ӽs���ť� !!";
	} elseif {
       $SQLStr = "DELETE FROM vend WHERE vendno = '$vendno'";
	   $msg = "�R���@���t�Ӹ�� !!";
	   mysql_query($SQLStr);
	 }
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
