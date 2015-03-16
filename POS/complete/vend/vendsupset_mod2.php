<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//-----------------------資料相關結合, 將 vend, vety 結合起來------------------------------		
	$SQLStr = "SELECT vend.*, vety.*  FROM vend AS vend ";
	$SQLStr .= "LEFT JOIN vety AS vety ON vend.vendtype = vety.vetyno WHERE vendno='$vendno'";	
	$res = mysql_query($SQLStr);	
	
//----------------------- 取出 satys 欄位值-----------------------------------------------
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);	

	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!---設定搜尋條件,傳入vendsupset_mod3.php---------------------->	
<form name="form1" method="post" action="vendsupset_mod3.php?vendno='.$vendno.'">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">廠商進貨設定</font>
            </td>
            <td align="center"> 
              <input type="submit" name="submit" value="修改廠商進貨設定">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="86" align="center">廠商序號</td>
            <td width="209" align="left" colspan="3"><?=$row[vendno]?>	
				 <input  type="hidden" name="vendpricper" size="3" value="<?=$row['vendno']?>">        
            </td>
		 </tr>	
          <tr>           
            <td width="86" align="center">廠商類別</td>
            <td width="209" align="left"><?=$row['vendtype']?>		        
            </td>
            <td width="85" align="center">廠商簡稱</td>
            <td width="201" align="left"><?=$row['vendsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">廠商名稱</td>
            <td width="209" align="left"><?=$row['vendname']?>               
            </td>
            <td width="96" align="center">負責人</td>
            <td width="201" align="left"><?=$row['vendleader']?>             
          </tr>
          <tr>
            <td width="86" align="center">統一編號</td>
            <td width="209" align="left"><?=$row['vendinvoice']?>               
            </td>
            <td width="96" align="center">聯絡人</td>
            <td width="201" align="left"><?=$row['vendcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="86" height="22" align="center">公司地址</td>
            <td width="187" height="22"><?=$row['vendadr']?>                
            </td>           
          </tr>
		  <tr>
			<td width="100" height="22" align="center">結帳日</td>
            <td width="187" height="22"> 
			   <input type="text" name="vendclosdate" size="10" maxlength="8" value="<?=substr($row['vendclosdate'],0,10)?>">
            </td>           
          </tr>
		  <tr>
			<td width="86" height="22" align="center">進貨類別</td>
            <td width="187" height="22"> 
<?
 		$num = mysql_num_rows($res2);

//--------------------------------呈現廠商類別的名稱,供選擇---------------------------------------------
                echo "<select name='vendprictype'>";
		echo "<option value='" . $row['vetyno'] . "'>" . $row['vetyname'] . "</option>";
		for ($i=0;$i<$num;$i++)
		{
		  $row2 = mysql_fetch_array($res2);
	          echo "<option value='" . $row2['satyno'] . "'>" . $row2['satyname'] . "</option>";
		}
                echo "</select>";		
?>
<?=$row2['vendprictype']?>
</td>           
          </tr>
		  <tr> 
            <td width="86" align="center">實收折數</td>
            <td width="187"> 
                <input type="text" name="vendpricper" size="3" value="<?=$row[vendpricper]?>">
            </td>
		  </tr>
		    
		<!--</td>
    </tr> -->
  </table>
</form>
<?
}
else
	{
	 $msg="無此廠商";
	 include("windowsclose.php");		
	}
?>
</body>
</html>
