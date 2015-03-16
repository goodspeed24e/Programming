<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//---------- 將 vend 及 vety 結合起來---------- 		
	$SQLStr = "SELECT vend.*, vety.* FROM vend AS vend ";
	$SQLStr .= "LEFT JOIN vety AS vety ON vend.vendtype = vety.vetyno WHERE vendno='$vendno'";
	$res = mysql_query($SQLStr);
	$SQLStr2 = "SELECT * FROM vety";
	$res2 = mysql_query($SQLStr2);
 //--------------------------- 判斷查詢結果是否有值---------------------------		
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<!----修改廠商資料,進入vendbasic_mod3.php,連接資料庫  ----->
<form name="form1" method="post" action="vendbasic_mod3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td bgcolor="#FFFFff">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">廠商詳細資訊</font>
            </td>          
            <td align="center"> 
              <input type="submit" name="submit" value="修改廠商資料">
            </td>
	  </tr>
        </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr> 
            <td width="86" align="center">廠商編號</td>
            <td width="209" align="left" colspan="3"><?=$row[vendno]?>
                <input  type="hidden" name="vendno" size="10" value="<?=$row[vendno]?>">
            </td>
          
          </tr>
          <tr>           
            <td width="86" align="center">廠商類別</td>
            <td width="209" align="left"> 
<?
 		$num = mysql_num_rows($res2);

//------------------------------呈現廠商類別的名稱------------------------------- 
                echo "<select name='vendtype'>";
		echo "<option value='" . $row['vetyno'] . "'>" . $row['vetyname'] . "</option>";
		for ($i=0;$i<$num;$i++)
		{
		  $row2 = mysql_fetch_array($res2);
	          echo "<option value='" . $row2['vetyno'] . "'>" . $row2['vetyname'] . "</option>";
		}
                echo "</select>";
		
?>
		<input type="hidden" name="vendno" size="10" value="<?=$row['vendno']?>">
            </td>
            <td width="85" align="center">廠商簡稱</td>
            <td width="201" align="left">
                <input type="text" name="vendsname" size="30" value="<?=$row['vendsname']?>">
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">廠商名稱</td>
            <td width="209" align="left">
                <input type="text" name="vendname" size="40" value="<?=$row['vendname']?>">
            </td>
            <td width="85" align="center">負責人</td>
            <td width="201" align="left">
                <input type="text" name="vendleader" size="10" value="<?=$row['vendleader']?>">
            </td>
          </tr>
          <tr>
            <td width="86" align="center">統一編號</td>
            <td width="209" align="left">
                <input type="text" name="vendinvoice" size="10" value="<?=$row['vendinvoice']?>">
            </td>
            <td width="85" align="center">聯絡人</td>
            <td width="201" align="left">
                <input type="text" name="vendcontact" size="10" value="<?=$row['vendcontact']?>">
            </td>
          </tr>
          <tr>
            <td width="86" height="22" align="center">聯絡電話</td>
            <td width="209" height="22" align="left">
                <input type="text" name="vendtel" size="10" value="<?=$row['vendtel']?>">
            </td>
            <td width="85" height="22" align="center">聯絡手機</td>
            <td width="201" height="22" align="left">
                <input type="text" name="vendmobil" size="10" value="<?=$row['vendmobil']?>">
            </td>
          </tr>
          <tr>            
            <td width="86" height="22" align="center">傳真機</td>
            <td width="209" height="22" align="left">
                <input type="text" name="vendfax" size="10" value="<?=$row['vendfax']?>">
            </td>
			<td width="85" height="22" align="center">業務員</td>
            <td width="201" height="22" align="left">
                <input type="text" name="vendsales" size="10" value="<?=$row['vendsales']?>">
            </td>           
          </tr>
		 <tr>
			<td width="103" height="22" align="center">公司地址</td>
            <td width="187" height="22"> 
                <input type="text" name="vendadr" size="40" value="<?=$row['vendadr']?>">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">送貨地址</td>
            <td width="187" height="22"> 
                <input type="text" name="vendpradr" size="40" value="<?=$row['vendpradr']?>">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">發票地址</td>
            <td width="187" height="22"> 
                <input type="text" name="vendinadr" size="40" value="<?=$row['vendinadr']?>">
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">電子信箱</td>
            <td width="187"> 
                <input type="text" name="vendemail" size="40" value="<?=$row['vendemail']?>">
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">網址</td>
            <td width="351"> 
                <input type="text" name="vendhttp" size="40" value="<?=$row['vendhttp']?>">
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
