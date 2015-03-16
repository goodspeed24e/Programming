<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//---------- 將 cust 及 saty 結合起來---------- 
	$SQLStr = "SELECT cust.*, saty.*  FROM cust AS cust ";
	$SQLStr .= "LEFT JOIN saty AS saty ON cust.custprictype = saty.satyno WHERE custno='$custno'";	
	$res = mysql_query($SQLStr);

//---------- 取出 saty 資料表中的欄位值---------------------- 
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);
	
//---------- 判斷查詢結果是否有值-----------------------------------
	if (mysql_num_rows($res)>0) 	
	{
	$row = mysql_fetch_array($res);
?>
<!------ 傳給 mod3.php 檔案,更新資料庫  ------>
<form name="form1" method="post" action="custsaleset_mod3.php?custno='$custno'">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="50%" bgcolor="#9933FF"     align="center"><font color="#FFFFFF">客戶銷售設定</font>
            </td>     
            <td align="center"> 
              <input type="submit" name="submit" value="修改客戶銷售設定">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="86" align="center">客戶序號</td>
            <td width="209" align="left" colspan="3"><?=$row[custno]?>
			 <input  type="hidden" name="custno" size="10" value="<?=$row['custno']?>">
          </tr>
          <tr> 
          <tr>           
            <td width="86" align="center">客戶類別</td>
            <td width="209" align="left"><?=$row['custtype']?>
		        
            </td>
            <td width="85" align="center">客戶簡稱</td>
            <td width="201" align="left"><?=$row['custsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">客戶名稱</td>
            <td width="209" align="left"><?=$row['custname']?>               
            </td>
            <td width="96" align="center">負責人</td>
            <td width="201" align="left"><?=$row['custleader']?>             
          </tr>
          <tr>
            <td width="86" align="center">統一編號</td>
            <td width="209" align="left"><?=$row['custinvoice']?>               
            </td>
            <td width="96" align="center">聯絡人</td>
            <td width="201" align="left"><?=$row['custcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="86" height="22" align="center">公司地址</td>
            <td width="187" height="22"><?=$row['custadr']?>                
            </td>           
          </tr>
		</table>
		<br>
		<table bgcolor="#FFCC33" cellpadding="0" cellspacing="0" width="770"> 
		  <tr>
			<td width="111" height="22" align="center">結帳日</td>
            <td width="268" height="22" > 
			   <input type="text" name="custclosdate" size="10"  value="<?=$row['custclosdate']?>">
            </td>
			<td width="131" height="22" align="center">銷售類別</td>
            <td width="258" height="22" > 
<?
 		$num = mysql_num_rows($res2);

//--------------------- 呈現銷售類別的名稱-------------------------------- 
                echo "<select name='custprictype'>";
		echo "<option value='" . $row['satyno'] . "'>" . $row['satyname'] . "</option>";
		for ($i=0;$i<$num;$i++)
		{
		  $row2 = mysql_fetch_array($res2);
	          echo "<option value='" . $row2['satyno'] . "'>" . $row2['satyname'] . "</option>";
		}
                echo "</select>";		
?>
<?=$row2['custprictype']?>
</td>           
          </tr>
		  <tr> 
            <td width="111" align="center">實收折數</td>
            <td width="268" > 
                <input type="text" name="custpricper" size="3" value="<?=$row['custpricper']?>">
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
