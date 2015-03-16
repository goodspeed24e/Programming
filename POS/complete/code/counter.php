<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
include("mysqlcntdb.php");
$SQLStr = "SELECT * FROM counter WHERE counterid='1'";
$res = mysql_query($SQLStr);
if (mysql_num_rows($res)>0) // 判斷查詢結果是否有值
	{
	$row = mysql_fetch_array($res);
	if ($cntid=="cust") {
	 	$custcnt=$row['custcnt']+1;
		$SQLStr="UPDATE counter SET  custcnt=$custcnt WHERE counterid='1'";			
	} elseif ($cntid=="vend") {  
        $vendcnt=$row['vendcnt']+1;
		$SQLStr="UPDATE counter SET  vendcnt=$vendcnt WHERE counterid='1'";		
	} elseif ($cntid=="quot") {  
        $quotcnt=$row['quotcnt']+1;
		$SQLStr="UPDATE counter SET  quotcnt=$quotcnt WHERE counterid='1'";		
	} elseif ($cntid=="purc") {  
        $purccnt=$row['purccnt']+1;
		$SQLStr="UPDATE counter SET  purccnt=$purccnt WHERE counterid='1'";		
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
	 $msg="無計數器";
	 include("windowsclose.php");
	}	
?>
</body>
</html>
