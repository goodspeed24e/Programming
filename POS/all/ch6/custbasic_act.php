<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$d1=date("Y-m-d");
//---------- 判斷custno 是否有值----------		
	if ($custno == '') 
	  $msg = "未更新任何產品資訊！";
	else
	{
//---------- func 參數值為 insert, 所以執行新增客戶的動作----------
	    if ($func==insert)	    {
		   $SQLStr =  "INSERT INTO cust ( custno ,       custname ,   custsname ,   custleader ,   custinvoice ,   custcontact ,   custtel ,   custmobil ,   custfax ,   custtype ,   custsales ,   custadr ,   custpradr ,    custinadr ,   custemail ,   custhttp ,   custdate,";
           $SQLStr .=  "custclosdate,    custprictype,    custpricper,  custprepamt,  custsaleamt,   custchkamt,    custprepdc,  custsaledc,     custchkdc)"; 
   		   $SQLStr .="           VALUES ('$custno', '$custname', '$custsname', '$custleader', '$custinvoice', '$custcontact', '$custtel', '$custmobil', '$custfax', '$custtype', '$custsales', '$custadr', '$custpradr', '$custinadr', '$custemail', '$custhttp', '$custdate',";
           $SQLStr .= "          '',               '',            100,            0,           0,             0,            '',          '',            '')";
           $msg = "已新增一筆客戶資料!!";
	    }
//---------- func 參數值為 mod, 所以執行更新客戶資料的動作----------
	    if ($func==mod)
	    {
		    $SQLStr = "UPDATE cust SET    custname='$custname',   custsname='$custsname', custleader='$custleader', custinvoice='$custinvoice', custcontact='$custcontact', ";
		    $SQLStr .= "custtel='$custtel', custmobil='$custmobil', custfax='$custfax', custtype='$custtype', custsales='$custsales', custadr='$custadr', custpradr='$custpradr', custinadr='$custinadr', custemail='$custemail', custhttp='$custhttp', custdate='$d1' WHERE custno='$custno'";
		    $msg = "已更新一筆客戶資料!!";
	    }
//---------- func 參數值為 del, 所以執行刪除客戶資料的動作-----------
	    if  ($func==del)
    	{	    
	         $SQLStr = "DELETE FROM cust WHERE custno='$custno'";
	         $msg = "已刪除一筆筆客戶資料 !!";
	    }
	     mysql_query($SQLStr);
	 }
?>
<!--------呈現訊息,回首頁 ---------->
<?php include("gohomepage.php"); ?>
</body>
</html> 