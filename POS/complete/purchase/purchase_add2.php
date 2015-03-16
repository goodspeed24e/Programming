<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");	
    //-------------- 自廠商資料表取出廠商名稱------------- 
	$SQLStra = "SELECT * FROM vend  WHERE vendno='$purcmvend'";
	 $resa = mysql_query($SQLStra);
	 if ($resa)
     {
	 $rowa = mysql_fetch_array($resa);	
	 }
	 $purcmvendname=$rowa['vendname'];
	//------------新增採購主檔資料,加入資料庫中------------------------------------------		
    $SQLStr0  ="INSERT INTO purchmst ( purcmtranno ,   purcmvend ,   purcmdate ,  purcmtype,     purcmvendname)"; 
    $SQLStr0 .="VALUES              ('$purcmtranno', '$purcmvend', '$purcmdate', '$purcmtype', '$purcmvendname')";
    mysql_query($SQLStr0);

		for ($i=0;$i<8;$i++)
	     {
		 if ($purchprodno[$i]!='')
		     {
			 //-----------自product 資料表取出,產品名稱,單位,單價等資料--------------- 		 
		     $SQLStr1 = "SELECT * FROM product  WHERE prodno='$purchprodno[$i]'";
			 $res1 = mysql_query($SQLStr1);
			 if ($res1)
	         {
			 $row1 = mysql_fetch_array($res1);	
			 }
			 $purchprodname[$i]=$row1['prodname'];
		     $purchunit[$i]=$row1['produnit'];
		     $purchpric[$i]=$row1['prodipric'];
			 //------------新增採購明細資料,加入資料庫中------------------------------------------	  
		     $SQLStr  ="INSERT INTO purchase (  purchtranno,         purchprodno,        purchprodqty,    purchinqty,        purchpric,        purchunit,        purchprodname)";
             $SQLStr .= "VALUES              ('$purcmtranno', '$purchprodno[$i]', '$purchprodqty[$i]',             0, '$purchpric[$i]', '$purchunit[$i]', '$purchprodname[$i]')";
             mysql_query($SQLStr);
	         $msg = "新增採購單完成!!";	
			 }			 	  
	    } 
        //-------------- 新增採購單資料--------------	   
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
