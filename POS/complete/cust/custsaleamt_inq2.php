<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
    include("mysqlcntdb.php");
//--------------- 將 cust 及 saty 結合---------------
	$SQLStr = "SELECT cust.*, saty.*  FROM cust AS cust ";
	$SQLStr .= "LEFT JOIN saty AS saty ON cust.custprictype = saty.satyno WHERE custno='$custno'";	
	$res = mysql_query($SQLStr);	

//--------------- 取出 saty 中的欄位值---------------
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);
	
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);                            
?>
<!---搜救完成,回首頁 ------>
<form name="form1" method="post" action="../index.php?Select=10">
 <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" bgcolor="#FFFFFF" >
    <tr > 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="50%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">客戶帳款設定</font>
            </td>    
            <td align="center"> 
              <input type="submit" name="submit" value="搜尋客戶帳款設定完成,回首頁">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		 <tr>           
            <td width="177" align="center">客戶序號</td>
            <td width="201" align="left"><?=$row[custno]?>		        
            </td>
		 </tr>	
          <tr>           
            <td width="177" align="center">客戶類別</td>
            <td width="201" align="left"><?=$row['custtype']?>
		        
            </td>
            <td width="127" align="center">客戶簡稱</td>
            <td width="252" align="left"><?=$row['custsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="177" align="center">客戶名稱</td>
            <td width="201" align="left"><?=$row['custname']?>               
            </td>
            <td width="127" align="center">負責人</td>
            <td width="252" align="left"><?=$row['custleader']?>             
          </tr>
          <tr>
            <td width="177" align="center">統一編號</td>
            <td width="201" align="left"><?=$row['custinvoice']?>               
            </td>
            <td width="127" align="center">聯絡人</td>
            <td width="252" align="left"><?=$row['custcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="177" height="22" align="center">公司地址</td>
            <td width="201" height="22"><?=$row['custadr']?>                
            </td>           
          </tr>
		  <tr>
			<td width="177" height="22" align="center">應收金額</td>
            <td width="201" height="22"><?=$row['custsaleamt']?>			  
            </td>           
          </tr>
		  <tr>
			<td width="177" height="22" align="center">預收金額</td>
            <td width="201" height="22"><?=$row['custprepamt']?>			
			</td>           
          </tr>
		  <tr> 
            <td width="177" align="center">應收帳會計科目</td>
            <td width="201"> <?=$row['custsaledc']?>             
            </td>
		  </tr>
		  <tr> 
            <td width="177" align="center">預收帳會計科目</td>
            <td width="201"><?=$row['custprepdc']?>             
            </td>
		  </tr>
		
  </table>
</form>
<?
}
else
	{
//----------顯示訊息,回首頁----------------------------	
	 $msg="無此客戶";
	 include("windowsclose.php");		
	}
?>
</body>
</html>
