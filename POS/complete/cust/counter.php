<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
include("mysqlcntdb.php");
$SQLStr = "SELECT * FROM counter WHERE counterid='1'";
$res = mysql_query($SQLStr);
//---------- �P�_�d�ߵ��G�O�_����----------
if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
	if ($cntid=="cust") {
	 	$custcnt=$row['custcnt']+1;
		$SQLStr="UPDATE counter SET  custcnt=$custcnt WHERE counterid='1'";			
	} elseif ($cntid=="vend") {  
        $vendcnt=$row['vendcnt']+1;
		$SQLStr="UPDATE counter SET  vendcnt=$vendcnt WHERE counterid='1'";			
    } elseif ($cntid=="prod") {  
        $prodcnt=$row['prodcnt']+1;	
		$SQLStr="UPDATE counter SET  prodcnt=$prodcnt WHERE counterid='1'";			
	} elseif ($cntid=="outi") {  
        $outicnt=$row['outicnt']+1;
		$SQLStr="UPDATE counter SET  outicnt=$outicnt WHERE counterid='1'";			
	} elseif ($cntid=="tran") {  
        $trancnt=$row['trancnt']+1;
		$SQLStr="UPDATE counter SET  trancnt=$trancnt WHERE counterid='1'";			
    }	
	mysql_query($SQLStr);	
	}
else
	{
	 $msg="�L�p�ƾ�";
	 include("windowsclose.php");
	}	
?>
</body>
</html>
