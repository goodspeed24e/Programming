<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
// -------------取出選擇之產品的資料---------------
	$SQLStr = "SELECT *  FROM product  WHERE prodno='$prodno'";	
	$res = mysql_query($SQLStr);
// -------------取出產品類別的資料---------------
	$SQLStr2 = "SELECT * FROM prty";
	$res2 = mysql_query($SQLStr2);	

	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!----執行修改頁面呈現,傳入搜尋條件給invqty_mod3.php------------------------->
<form name="form1" method="post" action="invqty_mod3.php">
<table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">修改產品庫存資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="修改產品庫存資料">
            </td>                 
          </tr>
        </table>
        <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"    align="center">
          <tr> 
            <td width="103" align="center">產品編號</td>
            <td width="187"><?=$row['prodno']?> 
                <input  type="hidden" name="prodno" size="10" value="<?=$row['prodno']?>">
            </td>
            <td width="96" align="center">產品名稱</td>
            <td width="351"><?=$row['prodname']?>
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">規格說明</td>
            <td width="187"><?=$row['prodsdesp']?>                
            </td>
            <td width="96" align="center">產品類別</td>
            <td width="351"><?=$row['prodtype']?>              
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">供應廠商</td>
            <td width="187"><?=$row['prodvend']?>
            </td>
            <td width="96" align="center">單位</td>
            <td width="351"><?=$row['produnit']?>
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">成本價格</td>
            <td width="187"><?=$prodipric ?>
            </td>
            <td width="96" align="center">售價</td>
            <td width="351"><?=$row['prodspric']?>
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">安全存量</td>
            <td width="187" height="22"><?=$row['prodsave']?>             
            </td>
            <td width="96" height="22" align="center">最近進貨日</td>              
            <td width="187" height="22"><?=$row['prodidate']?>
            </td>
          </tr>         
         <tr>
			<td width="103" height="22" align="center">最近出貨日</td>
            <td width="187" height="22"><?=$row['prododate']?>			               
            </td>           
          </tr>		     
        </table>
        <br> 
		<table width="780" border="1" cellpadding="0" cellspacing="0"   bgcolor="#FFCC00"  bordercolor="#FFFFFF" align="center">
		 <tr> 
            <td width="103" height="22" align="center">期初庫存量</td>
            <td width="187" height="22">
              <input type="text" name="prodpqty" size="6" value="<?=$row[prodpqty]?>">
            </td>
            <td width="96" height="22" align="center">現有庫存量</td>              
            <td width="351" height="22">			   
              <input type="text" name="prodnqty"  size="6" value="<?=$row[prodnqty]?>">
            </td>
          </tr>
		  </table>          
      </td>
    </tr>
  </table>
</form>
<?
}
else
	{
	 $msg="無此產品";
	 include("windowsclose.php");		
	} 
?>
</body>
</html>

