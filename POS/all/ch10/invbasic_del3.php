<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php 
	include("mysqlcntdb.php");	
	if (prodnqty >0) {	
	   $message = "�L�k�R��,���~�|���w�s�q��� !!";
	} elseif {
//-------------- �B�z���~��ƧR��------------- 		
       $SQLStr = "DELETE FROM product WHERE prodno = '$prodno'";
	   $message = "�R���@�����~��� !!";
	   mysql_query($SQLStr);
	 }
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
