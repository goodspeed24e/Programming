<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
// -------------取出所有廠商及連接廠商類別的資料---------------
    include("mysqlcntdb.php");	
	$SQLStr = "SELECT vend.*, vety.* FROM vend AS vend ";
	$SQLStr .= "LEFT JOIN vety AS vety ON vend.vendtype = vety.vetyno WHERE vendno='$vendno'";
	$res = mysql_query($SQLStr);	
	$SQLStr2 = "SELECT * FROM vety";
	$res2 = mysql_query($SQLStr2);	
//----------------- 判斷查詢結果是否有值----------------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!----刪除廠商資料,進入vendbasic_del3.php,連接資料庫  ----->
<form name="form1" method="post" action="vendbasic_del3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">廠商詳細資訊</font>
            </td>
            <td align="center"> 
              <input type="submit" name="submit" value="刪除廠商資料">
            </td>
	  </tr>
        </table>
<!---//---------------	修改項目----------------------->            	
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		  <tr> 
            <td width="86" align="center">廠商編號</td>
            <td width="209" align="left" colspan="3"><?=$row[vendno]?>
                <input  type="hidden" name="vendno" size="10" value="<?=$row[vendno]?>">
            </td>          
          </tr>
          <tr>           
            <td width="86" align="center">廠商類別</td>
            <td width="209" align="left"><?=$row[vendtype]?>
            </td>
            <td width="85" align="center">廠商簡稱</td>
            <td width="201" align="left"><?=$row['vendsname']?>              
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">廠商名稱</td>
            <td width="209" align="left"><?=$row['vendname']?>              
            </td>
            <td width="85" align="center">負責人</td>
            <td width="201" align="left"><?=$row['vendleader']?>              
            </td>
          </tr>
          <tr>
            <td width="86" align="center">統一編號</td>
            <td width="209" align="left"><?=$row['vendinvoice']?>              
            </td>
            <td width="85" align="center">聯絡人</td>
            <td width="201" align="left"><?=$row['vendcontact']?>             
            </td>
          </tr>
          <tr>
            <td width="86" height="22" align="center">聯絡電話</td>
            <td width="209" height="22" align="left"><?=$row['vendtel']?>              
            </td>
            <td width="85" height="22" align="center">聯絡手機</td>
            <td width="201" height="22" align="left"><?=$row['vendmobil']?>              
            </td>
          </tr>
          <tr>            
            <td width="86" height="22" align="center">傳真機</td>
            <td width="209" height="22" align="left"><?=$row['vendfax']?>              
            </td>
			<td width="85" height="22" align="center">業務員</td>
            <td width="201" height="22" align="left"><?=$row['vendsales']?>                
            </td>           
          </tr>
		 <tr>
			<td width="103" height="22" align="center">公司地址</td>
            <td width="187" height="22"><?=$row['vendadr']?>              
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">送貨地址</td>
            <td width="187" height="22"><?=$row['vendpradr']?>              
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">發票地址</td>
            <td width="187" height="22"><?=$row['vendinadr']?>             
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">電子信箱</td>
            <td width="187"><?=$row['vendemail']?>              
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">網址</td>
            <td width="351"><?=$row['vendhttp']?>             
            </td>
          </tr>    
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
