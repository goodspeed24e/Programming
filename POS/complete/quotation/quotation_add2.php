<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");
    //-------------- 新增報價單資料-------------   
		for ($i=0;$i<8;$i++)
	     {
		 if ($quwkprod[$i]!='')
		     {
			 //-----------自product 資料表取出,產品名稱,單位,單價等資料--------------- 		 
		     $SQLStr1 = "SELECT * FROM product  WHERE prodno='$quwkprod[$i]'";
			 $res1 = mysql_query($SQLStr1);
			 if ($res1)
	         {
			 $row1 = mysql_fetch_array($res1);	
			 }
			 $quwkprodname[$i]=$row1['prodname'];
		     $quwkunit[$i]=$row1['produnit'];
		     $quwkpric[$i]=$row1['prodspric'];
			 //--------------------------從客戶資料表取得客戶名稱資料-----------------------
			 $SQLStr2 = "SELECT * FROM cust  WHERE custno='$quwkcust'";
			 $res2 = mysql_query($SQLStr2);
			 if ($res2)
	         {
			 $row2 = mysql_fetch_array($res2);	
			 }
			 $quwkcustname=$row2['custname'];			  
             //------------新增報價資料,加入資料庫中------------------------------------------				  
		     $SQLStr  ="INSERT INTO quotationwork (  quwkno,         quwkprod,        quwkcust,      quwktype,        quwkpric,       quwkqty, quwksdate,        quwkunit,        quwkprodname,         quwkcustname)";
             $SQLStr .= "VALUES                  ('$quwkno',  '$quwkprod[$i]',     '$quwkcust',   '$quwktype', '$quwkpric[$i]','$quwkqty[$i]',     '$dt', '$quwkunit[$i]', '$quwkprodname[$i]',      '$quwkcustname')";
             mysql_query($SQLStr);
	         $msg = "新增報價單完成!!";	
			 }			 	  
	    }    
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
