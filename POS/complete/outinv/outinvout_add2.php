<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");	
	    //------------------ 執行新增銷貨的動作-----------------
		for ($i=0;$i<8;$i++)
	     {
             //--------------------------從產品資料表取得產品相關資料--------------------------------		 
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
			 //----------------建立銷貨資料-------------------------------	  
			 $SQLStr ="INSERT INTO outinv ( outicode ,    outino,       outiprodno ,   outidate ,     outicustno ,       outiprodname ,       outiprodqty ,       outiunit ,     outipric ,outiamt,outiquno)"; 
             $SQLStr .="                  VALUES ('o', '$outino', '$outiprodno[$i]',       '$dt',   '$outicustno', '$outiprodname[$i]',   $outiprodqty[$i], '$outiunit[$i]', $outipric[$i],   $amt,'$outiquno')";
		     mysql_query($SQLStr);
			 //---------------更新相關關連資料,同步更新---------------------------
			  $SQLStr="UPDATE cust    SET  custsaleamt = custsaleamt + $amt  WHERE custno = '$outicustno'";			 
	         mysql_query($SQLStr);
			  //------------修改產品庫存資料,更新資料庫------------------------------------------ 
			 $SQLStr="UPDATE product SET  prodnqty = prodnqty - $outiprodqty[$i] WHERE prodno = '$outiprodno[$i]'";	
	         mysql_query($SQLStr);	
			 //------------修改報價資料,更新資料庫------------------------------------------ 			
	         $SQLStr="UPDATE quotationwork    SET  quwksqty = quwksqty + $outiprodqty[$i]  WHERE quwkno = '$outiquno' AND quwkprod = '$outiprodno[$i]' AND quwkcust = '$outicustno'";			 
          	 mysql_query($SQLStr);	
	      $msg = "已新增銷貨資料!!";		
	    }    
?>
<?php include("gohomepage.php"); ?> 
</body>
</html>
