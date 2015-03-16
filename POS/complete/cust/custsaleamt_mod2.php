<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
    include("mysqlcntdb.php");
	
	// 將 cust 及 saty 結合
	$SQLStr = "SELECT cust.*, saty.*  FROM cust AS cust ";
	$SQLStr .= "LEFT JOIN saty AS saty ON cust.custprictype = saty.satyno WHERE custno='$custno'";	
	$res = mysql_query($SQLStr);	

	// 取出 saty 中的欄位值
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);	

	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);                            
?>
<!------ 傳給 mod3.php 檔案,更新資料庫  ------>
<form name="form1" method="post" action="custsaleamt_mod3.php?custno='.$custno.'">
 <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" bgcolor="#FFFFFF" >
    <tr > 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0"   align="center">
          <tr> 
            <td width="50%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">客戶帳款設定</font>
            </td>
       
            <td align="center"> 
              <input type="submit" name="submit" value="修改客戶帳款設定">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		 <tr>           
            <td width="145" align="center">客戶序號</td>
            <td width="231" align="left"><?=$row[custno]?>
			<input  type="hidden" name="custno" size="10" value="<?=$row[custno]?>">        
            </td>
		 </tr>	
          <tr>           
            <td width="145" align="center">客戶類別</td>
            <td width="231" align="left"><?=$row['custtype']?>
		        
            </td>
            <td width="148" align="center">客戶簡稱</td>
            <td width="233" align="left"><?=$row['custsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="145" align="center">客戶名稱</td>
            <td width="231" align="left"><?=$row['custname']?>               
            </td>
            <td width="148" align="center">負責人</td>
            <td width="233" align="left"><?=$row['custleader']?>             
          </tr>
          <tr>
            <td width="145" align="center">統一編號</td>
            <td width="231" align="left"><?=$row['custinvoice']?>               
            </td>
            <td width="148" align="center">聯絡人</td>
            <td width="233" align="left"><?=$row['custcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="145" height="22" align="center">公司地址</td>
            <td width="231" height="22"><?=$row['custadr']?>                
            </td>           
          </tr>
		 </table>
		 <br>
		 <table   bgcolor="#FFCC00" cellpadding="0" cellspacing="0" width="770">
		  <tr>
			<td width="142" height="22" align="center">應收金額</td>
            <td width="228" height="22"> 
			   <input type="text" name="custsaleamt" size="8"  value="<?=$row['custsaleamt']?>">
            </td>           
        
			<td width="153" height="22" align="center">預收金額</td>
            <td width="226" height="22">
			<input type="text" name="custprepamt" size="8" value="<?=$row['custprepamt']?>">
			</td>           
          </tr>
		  <tr> 
            <td width="142" align="center"><font size="-1">應收帳會計科目</font></td>
            <td width="228"> 
                <input type="text" name="custsaledc" size="10" value="<?=$row['custsaledc']?>">
            </td>
		
            <td width="153" align="center"><font size="-1">預收帳會計科目</font></td>
            <td width="226"> 
                <input type="text" name="custprepdc" size="10" value="<?=$row['custprepdc']?>">
            </td>
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
