<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");
//-------------- 處理廠商資料新增------------- 
		for ($i=0;$i<8;$i++)		
	     {
		 $SQLStr =  "INSERT INTO `vend` (  vendno ,   vendname ,   vendsname ,   vendleader ,   vendinvoice ,   vendcontact ,   vendtel ,   vendmobil ,   vendfax ,   vendtype ,   vendsales ,   vendadr ,   vendpradr ,   vendinadr ,   vendemail ,   vendhttp ,   venddate, "; 
         $SQLStr .=  "vendclosdate,    vendprictype,    vendpricper,  vendprepamt,  vendchkamt, vendapamt,    vendprepdc,    vendapdc,     vendchkdc)"; 
         $SQLStr .= "VALUES             ('$vendno', '$vendname', '$vendsname', '$vendleader', '$vendinvoice', '$vendcontact', '$vendtel', '$vendmobil', '$vendfax', '$vendtype', '$vendsales', '$vendadr', '$vendpradr', '$vendinadr', '$vendemail', '$vendhttp', '$venddate',";
  	     $SQLStr .= "          '',               '',            100,            0,           0,          0,           '',          '',            '')";
		 mysql_query($SQLStr);
	      $msg = "已新增一筆廠商資料!!";		  
	    } 
?>
<?php include("gohomepage.php"); ?>
</body>
</html>
