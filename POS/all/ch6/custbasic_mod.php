<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
    include("mysqlcntdb.php");
//---------- 將 cust 及 cuty 結合起來---------- 
	$SQLStr = "SELECT cust.*, cuty.* FROM cust AS cust ";
	$SQLStr .= "LEFT JOIN cuty AS cuty ON cust.custtype = cuty.cutyno WHERE custno='$custno'";
	$res = mysql_query($SQLStr);	
	
//---------- 取出 cuty 資料表中的欄位值---------- 
	$SQLStr2 = "SELECT * FROM cuty";
	$res2 = mysql_query($SQLStr2);	
	
//---------- 判斷查詢結果是否有值----------------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!------ 傳給 custbasic_act.php 檔案  ------>
<form name="form1" method="post" action="custbasic_act.php?func=mod">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">客戶詳細資訊</font>
            <td align="center"> 
              <input type="submit" name="submit" value="修改客戶資料">
            </td>
	  </tr>
        </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		  <tr> 
            <td width="86" align="center">客戶序號</td>
            <td width="209" align="left">
                <input type="text" name="custno" size="10" value="<?=$row[custno]?>">
            </td>
            <td width="85" align="center">統一編號</td>
            <td width="201" align="left">
              <input type="text" name="custinvoice" size="10" value="<?=$row['custinvoice']?>">  
            </td>
          </tr>
          <tr>           
            <td width="86" align="center">客戶類別</td>
            <td width="209" align="left"> 
<?php
 		$num = mysql_num_rows($res2);
//---------- 呈現客戶類別名稱---------- 
        echo "<select name='custtype'>";
		echo "<option value='" . $row['cutyno'] . "'>" . $row['cutyname'] . "</option>";
		for ($i=0;$i<$num;$i++)
		{
		  $row2 = mysql_fetch_array($res2);
	          echo "<option value='" . $row2['cutyno'] . "'>" . $row2['cutyname'] . "</option>";
		}
                echo "</select>";
?>
		<input type="hidden" name="custno" size="10" value="<?=$row['custno']?>">
            </td>
            <td width="85" align="center">客戶簡稱</td>
            <td width="201" align="left">
                <input type="text" name="custsname" size="30" value="<?=$row['custsname']?>">
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">客戶名稱</td>
            <td width="209" align="left">
                <input type="text" name="custname" size="40" value="<?=$row['custname']?>">
            </td>
            <td width="85" align="center">負責人</td>
            <td width="201" align="left">
                <input type="text" name="custleader" size="10" value="<?=$row['custleader']?>">
            </td>
          </tr>
          <tr>
            <td width="86" align="center">業務員</td>
            <td width="209" align="left">
               <input type="text" name="custsales" size="10" value="<?=$row['custsales']?>">  
            </td>
            <td width="85" align="center">聯絡人</td>
            <td width="201" align="left">
                <input type="text" name="custcontact" size="10" value="<?=$row['custcontact']?>">
            </td>
          </tr>
          <tr>
            <td width="86" height="22" align="center">聯絡電話</td>
            <td width="209" height="22" align="left">
                <input type="text" name="custtel" size="10" value="<?=$row['custtel']?>">
            </td>
            <td width="85" height="22" align="center">聯絡手機</td>
            <td width="201" height="22" align="left">
                <input type="text" name="custmobil" size="10" value="<?=$row['custmobil']?>">
            </td>
          </tr>
          <tr>            
            <td width="86" height="22" align="center">傳真機</td>
            <td width="209" height="22" align="left">
                <input type="text" name="custfax" size="10" value="<?=$row['custfax']?>">
            </td>			     
          </tr>
		 <tr>
			<td width="103" height="22" align="center">公司地址</td>
            <td width="187" height="22"> 
                <input type="text" name="custadr" size="40" value="<?=$row['custadr']?>">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">送貨地址</td>
            <td width="187" height="22"> 
                <input type="text" name="custpradr" size="40" value="<?=$row['custpradr']?>">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">發票地址</td>
            <td width="187" height="22"> 
                <input type="text" name="custinadr" size="40" value="<?=$row['custinadr']?>">
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">電子信箱</td>
            <td width="187"> 
                <input type="text" name="custemail" size="40" value="<?=$row['custemail']?>">
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">網址</td>
            <td width="351"> 
                <input type="text" name="custhttp" size="40" value="<?=$row['custhttp']?>">
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
// <!--------呈現訊息,回首頁 ---------->
	 $msg="無此客戶資料";
	 include("windowsclose.php");		
	}
?>
</body>
</html>
