<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$d1=date("Y-m-d");
//---------- �P�_custno �O�_����----------		
	if ($custno == '') 
	  $msg = "����s���󲣫~��T�I";
	else
	{
//---------- func �ѼƭȬ� insert, �ҥH����s�W�Ȥ᪺�ʧ@----------
	    if ($func==insert)	    {
		   $SQLStr =  "INSERT INTO cust ( custno ,       custname ,   custsname ,   custleader ,   custinvoice ,   custcontact ,   custtel ,   custmobil ,   custfax ,   custtype ,   custsales ,   custadr ,   custpradr ,    custinadr ,   custemail ,   custhttp ,   custdate,";
           $SQLStr .=  "custclosdate,    custprictype,    custpricper,  custprepamt,  custsaleamt,   custchkamt,    custprepdc,  custsaledc,     custchkdc)"; 
   		   $SQLStr .="           VALUES ('$custno', '$custname', '$custsname', '$custleader', '$custinvoice', '$custcontact', '$custtel', '$custmobil', '$custfax', '$custtype', '$custsales', '$custadr', '$custpradr', '$custinadr', '$custemail', '$custhttp', '$custdate',";
           $SQLStr .= "          '',               '',            100,            0,           0,             0,            '',          '',            '')";
           $msg = "�w�s�W�@���Ȥ���!!";
	    }
//---------- func �ѼƭȬ� mod, �ҥH�����s�Ȥ��ƪ��ʧ@----------
	    if ($func==mod)
	    {
		    $SQLStr = "UPDATE cust SET    custname='$custname',   custsname='$custsname', custleader='$custleader', custinvoice='$custinvoice', custcontact='$custcontact', ";
		    $SQLStr .= "custtel='$custtel', custmobil='$custmobil', custfax='$custfax', custtype='$custtype', custsales='$custsales', custadr='$custadr', custpradr='$custpradr', custinadr='$custinadr', custemail='$custemail', custhttp='$custhttp', custdate='$d1' WHERE custno='$custno'";
		    $msg = "�w��s�@���Ȥ���!!";
	    }
//---------- func �ѼƭȬ� del, �ҥH����R���Ȥ��ƪ��ʧ@-----------
	    if  ($func==del)
    	{	    
	         $SQLStr = "DELETE FROM cust WHERE custno='$custno'";
	         $msg = "�w�R���@�����Ȥ��� !!";
	    }
	     mysql_query($SQLStr);
	 }
?>
<!--------�e�{�T��,�^���� ---------->
<?php include("gohomepage.php"); ?>
</body>
</html> 