<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");
    //-------------- �s�W��������-------------   
		for ($i=0;$i<8;$i++)
	     {
		 if ($quwkprod[$i]!='')
		     {
			 //-----------��product ��ƪ���X,���~�W��,���,��������--------------- 		 
		     $SQLStr1 = "SELECT * FROM product  WHERE prodno='$quwkprod[$i]'";
			 $res1 = mysql_query($SQLStr1);
			 if ($res1)
	         {
			 $row1 = mysql_fetch_array($res1);	
			 }
			 $quwkprodname[$i]=$row1['prodname'];
		     $quwkunit[$i]=$row1['produnit'];
		     $quwkpric[$i]=$row1['prodspric'];
			 //--------------------------�q�Ȥ��ƪ���o�Ȥ�W�ٸ��-----------------------
			 $SQLStr2 = "SELECT * FROM cust  WHERE custno='$quwkcust'";
			 $res2 = mysql_query($SQLStr2);
			 if ($res2)
	         {
			 $row2 = mysql_fetch_array($res2);	
			 }
			 $quwkcustname=$row2['custname'];			  
             //------------�s�W�������,�[�J��Ʈw��------------------------------------------				  
		     $SQLStr  ="INSERT INTO quotationwork (  quwkno,         quwkprod,        quwkcust,      quwktype,        quwkpric,       quwkqty, quwksdate,        quwkunit,        quwkprodname,         quwkcustname)";
             $SQLStr .= "VALUES                  ('$quwkno',  '$quwkprod[$i]',     '$quwkcust',   '$quwktype', '$quwkpric[$i]','$quwkqty[$i]',     '$dt', '$quwkunit[$i]', '$quwkprodname[$i]',      '$quwkcustname')";
             mysql_query($SQLStr);
	         $msg = "�s�W�����槹��!!";	
			 }			 	  
	    }    
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
