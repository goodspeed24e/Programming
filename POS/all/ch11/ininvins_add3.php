<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");
//-------------- �s�W�i�f���------------- 
		for ($i=0;$i<8;$i++)
	     {
//-----------��product ��ƪ���X,���~�W��,���,��������--------------- 		 
		     $SQLStr = "SELECT * FROM product  WHERE prodno='$tranprodno[$i]'";
			 $res = mysql_query($SQLStr);
			 if ($res)
	         {
			 $row = mysql_fetch_array($res);	
			 }
			 $tranprodname[$i]=$row['prodname'];
		     $tranunit[$i]=$row['produnit'];
		     $tranpric[$i]=$row['prodipric'];  	        
		     $amt=$tranprodqty[$i] * $tranpric[$i];
//------------�s�W�i�f���,�[�J��Ʈw��------------------------------------------			 
			 $SQLStr =  "INSERT INTO transaction ( trancode , trandate ,      tranno ,  tranpono ,       tranremark ,       tranvendno ,       tranprodno ,       tranprodname ,       tranprodqty ,       tranunit ,       tranpric , tranamt )"; 
             $SQLStr .= "VALUES                  ('i',            '$dt',    '$tranno',         '',                '',     '$tranvendno', '$tranprodno[$i]', '$tranprodname[$i]',   $tranprodqty[$i], '$tranunit[$i]',   $tranpric[$i],     $amt)";
	         mysql_query($SQLStr);			 
			 $SQLStr="UPDATE vend    SET  vendapamt = vendapamt + $amt  WHERE vendno = '$tranvendno'";			 
	         mysql_query($SQLStr);
			 $SQLStr="UPDATE product SET  prodnqty = prodnqty + $tranprodqty[$i] WHERE prodno = '$tranprodno[$i]'";			
	         mysql_query($SQLStr);
			 $SQLStr="UPDATE purchase SET purchinqty = purchinqty + $tranprodqty[$i] WHERE purchtranno =  '$tranpono'  AND purchprodno = '$tranprodno[$i]'";			 
			 mysql_query($SQLStr);
			 $msg = "�s�W�i�f��Ƨ���!!";			  			  
	    } 
//-------------- �s�W�i�f��Ƨ���--------------	   
?>
<?php include("gohomepage.php"); ?>
</body>
</html>