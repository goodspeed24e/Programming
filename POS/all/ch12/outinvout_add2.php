<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");	
	    //------------------ ����s�W�P�f���ʧ@-----------------
		for ($i=0;$i<8;$i++)
	     {
             //--------------------------�q���~��ƪ���o���~�������--------------------------------		 
		     $SQLStr = "SELECT * FROM product  WHERE prodno='$outiprodno[$i]'";
			 $res = mysql_query($SQLStr);
			 if ($res)
	         {
			 $row = mysql_fetch_array($res);	
			 }
			 $outiprodname[$i]=$row['prodname'];
		     $outiunit[$i]=$row['produnit'];
		     $outipric[$i]=$row['prodipric'];  	        
		     $amt=$outiprodqty[$i] * $outipric[$i];	
			 //----------------�إ߾P�f���-------------------------------	  
			 $SQLStr ="INSERT INTO outinv ( outicode ,    outino,       outiprodno ,   outidate ,     outicustno ,       outiprodname ,       outiprodqty ,       outiunit ,     outipric ,outiamt,outiquno)"; 
             $SQLStr .="                  VALUES ('o', '$outino', '$outiprodno[$i]',       '$dt',   '$outicustno', '$outiprodname[$i]',   $outiprodqty[$i], '$outiunit[$i]', $outipric[$i],   $amt,'$outiquno')";
		     mysql_query($SQLStr);
			 //---------------��s�������s���,�P�B��s---------------------------
			  $SQLStr="UPDATE cust    SET  custsaleamt = custsaleamt + $amt  WHERE custno = '$outicustno'";			 
	         mysql_query($SQLStr);
			  //------------�קﲣ�~�w�s���,��s��Ʈw------------------------------------------ 
			 $SQLStr="UPDATE product SET  prodnqty = prodnqty - $outiprodqty[$i] WHERE prodno = '$outiprodno[$i]'";	
	         mysql_query($SQLStr);	
			 //------------�ק�������,��s��Ʈw------------------------------------------ 			
	         $SQLStr="UPDATE quotationwork    SET  quwksqty = quwksqty + $outiprodqty[$i]  WHERE quwkno = '$outiquno' AND quwkprod = '$outiprodno[$i]' AND quwkcust = '$outicustno'";			 
          	 mysql_query($SQLStr);	
	      $msg = "�w�s�W�P�f���!!";		
	    }    
?>
<?php include("gohomepage.php"); ?> 
</body>
</html>
