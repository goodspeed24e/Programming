<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");	
    //-------------- �ۼt�Ӹ�ƪ���X�t�ӦW��------------- 
	$SQLStra = "SELECT * FROM vend  WHERE vendno='$purcmvend'";
	 $resa = mysql_query($SQLStra);
	 if ($resa)
     {
	 $rowa = mysql_fetch_array($resa);	
	 }
	 $purcmvendname=$rowa['vendname'];
	//------------�s�W���ʥD�ɸ��,�[�J��Ʈw��------------------------------------------		
    $SQLStr0  ="INSERT INTO purchmst ( purcmtranno ,   purcmvend ,   purcmdate ,  purcmtype,     purcmvendname)"; 
    $SQLStr0 .="VALUES              ('$purcmtranno', '$purcmvend', '$purcmdate', '$purcmtype', '$purcmvendname')";
    mysql_query($SQLStr0);

		for ($i=0;$i<8;$i++)
	     {
		 if ($purchprodno[$i]!='')
		     {
			 //-----------��product ��ƪ���X,���~�W��,���,��������--------------- 		 
		     $SQLStr1 = "SELECT * FROM product  WHERE prodno='$purchprodno[$i]'";
			 $res1 = mysql_query($SQLStr1);
			 if ($res1)
	         {
			 $row1 = mysql_fetch_array($res1);	
			 }
			 $purchprodname[$i]=$row1['prodname'];
		     $purchunit[$i]=$row1['produnit'];
		     $purchpric[$i]=$row1['prodipric'];
			 //------------�s�W���ʩ��Ӹ��,�[�J��Ʈw��------------------------------------------	  
		     $SQLStr  ="INSERT INTO purchase (  purchtranno,         purchprodno,        purchprodqty,    purchinqty,        purchpric,        purchunit,        purchprodname)";
             $SQLStr .= "VALUES              ('$purcmtranno', '$purchprodno[$i]', '$purchprodqty[$i]',             0, '$purchpric[$i]', '$purchunit[$i]', '$purchprodname[$i]')";
             mysql_query($SQLStr);
	         $msg = "�s�W���ʳ槹��!!";	
			 }			 	  
	    } 
        //-------------- �s�W���ʳ���--------------	   
?>
<?php  include("gohomepage.php"); ?>
</body>
</html>
