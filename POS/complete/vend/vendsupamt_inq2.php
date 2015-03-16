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

//----------------------- 取出 vetys 欄位值-----------------------------------------------
	$SQLStr2 = "SELECT * FROM vety";
	$res2 = mysql_query($SQLStr2);
//------------------------ 判斷搜尋結果是否有值--------------------------------------------	
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!---執行完成,回首頁----->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">應付帳款設定</font>
            </td>          
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="搜尋應付帳款設定">
            </td>
	  </tr>
  </table>
<!--//------------搜尋資料內容呈現,廠商應付帳款資料明細-------------------------------------------->	  
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="201" align="center">廠商序號</td>
            <td align="left" colspan="3"><?=$row[vendno]?>	
				 <input  type="hidden" name="vendpricper" size="3" value="<?=$row['vendno']?>">        
            </td>
		 </tr>	
          <tr>           
            <td width="201" align="center">廠商類別</td>
            <td width="204" align="left"><?=$row['vendtype']?>		        
            </td>
            <td width="100" align="center">廠商簡稱</td>
            <td width="252" align="left"><?=$row['vendsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="201" align="center">廠商名稱</td>
            <td width="204" align="left"><?=$row['vendname']?>               
            </td>
            <td width="100" align="center">負責人</td>
            <td width="252" align="left"><?=$row['vendleader']?>             
          </tr>
          <tr>
            <td width="201" align="center">統一編號</td>
            <td width="204" align="left"><?=$row['vendinvoice']?>               
            </td>
            <td width="100" align="center">聯絡人</td>
            <td width="252" align="left"><?=$row['vendcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="201" height="22" align="center">公司地址</td>
            <td width="204" height="22"><?=$row['vendadr']?>                
            </td>           
          </tr>
		  <tr>
			<td width="201" height="22" align="center">應付金額</td>
            <td width="204" height="22"> 
			   <input type="text" name="vendapamt" size="8"  value="<?=$row[vendapamt]?>">
            </td>           
          </tr>
		  <tr>
			<td width="201" height="22" align="center">預付金額</td>
            <td width="204" height="22">
			 <input type="text" name="vendprepamt" size="8" value="<?=$row[vendprepamt]?>">
			</td>           
          </tr>
		  <tr> 
            <td width="201" align="center">應付帳會計科目</td>
            <td width="204"> 
                <input type="text" name="vendapdc" size="10" value="<?=$row['vendapdc']?>">
            </td>
		  </tr>
		  <tr> 
            <td width="201" align="center">預付款會計科目</td>
            <td width="204"> 
                <input type="text" name="vendprepdc" size="10" value="<?=$row['vendprepdc']?>">
            </td>
		  </tr>
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
