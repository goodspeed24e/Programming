<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
    //-------------- �R���P�f���,�ñN������ƪ�������,�@�վ�-------------		
	include("mysqlcntdb.php");
	//-------------- �P�_ outino �O�_����
	if ($outino == '') 
	  $msg = "���R������P�f��T�I";
	else
	{
	   $SQLStr="UPDATE product SET  prodnqty = prodnqty - $outiprodqty  WHERE prodno = '$outiprodno'";			
	   mysql_query($SQLStr);	
	   $amt=$outiprodqty * $outipric;	  
       $SQLStr="UPDATE cust    SET  custsaleamt = custsaleamt - $amt  WHERE custno = '$outicustno'";			 
       mysql_query($SQLStr);	
	    //------------�R���P�f���,�۸�Ʈw���簣------------------------------------------ 
       $SQLStr = "DELETE outinv FROM outinv WHERE outino = '$outino' AND outiprodno = '$outiprodno'";
	   mysql_query($SQLStr);	
	   $SQLStr="UPDATE quotationwork  SET quwksqty = quwksqty - $outiprodqty[$i] WHERE quwkno = '$outiquno'  AND quwkprodno = '$outiprodno'";
       mysql_query($SQLStr);   
	   $msg = "�R���P�f��� !!";
	 }
?>
<?php include("gohomepage.php"); ?> 
</body>
</html>
