<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
	include("mysqlcntdb.php");
	$SQLStr="UPDATE product SET prodpqty = $prodpqty, prodnqty = $prodnqty WHERE prodno = '$prodno'";	
	$msg = "�w��s�@�����~���!!";
	mysql_query($SQLStr);	
?>
<!----���槹��,�^����------------------------->
<?php include("gohomepage.php"); ?>
</body>
</html>