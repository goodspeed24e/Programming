<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//---------- 將 product 及 saty 結合----------
	$SQLStr = "SELECT cust.*, saty.*  FROM cust AS cust ";	
	$SQLStr .= "LEFT JOIN saty AS saty ON cust.custprictype = saty.satyno WHERE custno='$custno'";	
	$res = mysql_query($SQLStr);
	
//---------- 取出 saty 資料表中的欄位值----------
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);
	
//---------- 判斷查詢結果是否有值----------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>


<!------ 傳給 index.php 檔案 ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" bgcolor="#FFFFFF" >
    <tr bgcolor="#FFFFFF"> 
      <td >  
        <table width="400" border="0" align="center" >
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">客戶銷售設定</font>
            </td>            
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="搜尋客戶銷售設定完成,回首頁">
            </td>
	  </tr>
  </table>
  
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="152" align="center">客戶序號</td>
            <td align="left" colspan="3"><?=$row[custno]?>		        
            </td>
		  </tr>	
          <tr>           
            <td width="152" align="center">客戶類別</td>
            <td width="233" align="left"><?=$row['custtype']?>
		        
            </td>
            <td width="120" align="center">客戶簡稱</td>
            <td width="252" align="left"><?=$row['custsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="152" align="center">客戶名稱</td>
            <td width="233" align="left"><?=$row['custname']?>               
            </td>
            <td width="120" align="center">負責人</td>
            <td width="252" align="left"><?=$row['custleader']?>             
          </tr>
          <tr>
            <td width="152" align="center">統一編號</td>
            <td width="233" align="left"><?=$row['custinvoice']?>               
            </td>
            <td width="120" align="center">聯絡人</td>
            <td width="252" align="left"><?=$row['custcontact']?>               
            </td>
          </tr>		  
		 <tr>
			<td width="152" height="22" align="center">公司地址</td>
            <td width="233" height="22"><?=$row['custadr']?>                
            </td>           
          </tr>
		  <tr>
			<td width="152" height="22" align="center">結帳日</td>
            <td width="233" height="22"> 
			   <?=substr($row['custclosdate'],0,10)?>
            </td>           
          </tr>
		  <tr>
			<td width="152" height="22" align="center">銷售類別</td>
            <td width="233" height="22"><?=$row['custprictype']?><?=$row['satyname']?>  
            </td>           
          </tr>
		  <tr> 
            <td width="152" align="center">實收折數</td>
            <td width="233"><?=$row['custpricper']?></td>
		  </tr>
  </table>
</form>
<?
}
else
	{
	 $msg="無此客戶";
	 include("windowsclose.php");		
	}
?>
</body>
</html>